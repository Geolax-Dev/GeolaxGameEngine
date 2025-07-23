#pragma once

#include <Core/Minimal.h>

#include <atomic>
#include <cassert>
#include <functional>
#include <future>
#include <memory>
#include <thread>
#include <utility>
#include <vector>

namespace GGE
{
    /**
    */
    class ThreadPool
    {
        // A single-producer/multiple-consumer deque (Chase–Lev) for work stealing.
        class TaskDeque {
        public:
            using Task = std::function<void()>;

            TaskDeque(size_t capacity = 1024)
                : capacity_(capacity), mask_(capacity - 1),
                buffer_(new Task[capacity]),
                top_(0), bottom_(0)
            {
                assert((capacity & mask_) == 0 && "capacity must be power of two");
            }

            ~TaskDeque() {
                delete[] buffer_;
            }

            // Owner thread only.
            [[maybe_unused]] void push_bottom(Task const& task) {
                size_t b = bottom_.load(std::memory_order_relaxed);
                buffer_[b & mask_] = task;
                // publish
                bottom_.store(b + 1, std::memory_order_release);
            }

            // Owner thread only.
            [[maybe_unused]] bool pop_bottom(Task& task) {
                // 1) Snapshot both ends
                size_t old_bottom = bottom_.load(std::memory_order_relaxed);
                size_t old_top = top_.load(std::memory_order_acquire);

                // 2) If empty, bail out **before** underflow
                if (old_bottom <= old_top) {
                    return false;
                }

                // 3) There's at least one element: remove it
                size_t new_bottom = old_bottom - 1;
                bottom_.store(new_bottom, std::memory_order_relaxed);
                task = std::move(buffer_[new_bottom & mask_]);

                // 4) If more than one element remains, we’re done
                if (old_bottom - old_top > 1) {
                    return true;
                }

                // 5) Last element: compete with thieves
                if (!top_.compare_exchange_strong(
                    old_top, old_top + 1,
                    std::memory_order_release,
                    std::memory_order_relaxed))
                {
                    // lost the race, restore
                    bottom_.store(old_bottom, std::memory_order_relaxed);
                    return false;
                }

                // claimed the last item—reset bottom to original
                bottom_.store(old_bottom, std::memory_order_relaxed);
                return true;
            }

            // Any stealer thread.
            [[maybe_unused]] bool steal(Task& task) {
                size_t old_top = top_.load(std::memory_order_acquire);
                size_t old_bottom = bottom_.load(std::memory_order_acquire);

                if (old_top >= old_bottom) {
                    return false;
                }

                task = std::move(buffer_[old_top & mask_]);
                if (!top_.compare_exchange_strong(
                    old_top, old_top + 1,
                    std::memory_order_release,
                    std::memory_order_relaxed))
                {
                    return false;
                }
                return true;
            }

        private:
            const size_t      capacity_;
            const size_t      mask_;
            Task* buffer_;
            std::atomic<size_t> top_;
            std::atomic<size_t> bottom_;
        };
    public:
        [[maybe_unused]] ThreadPool(size_t num_threads = std::thread::hardware_concurrency())
            : done_(false),
            num_threads_(num_threads),
            deques_(),
            workers_(),
            next_queue_idx_(0)
        {
            deques_.reserve(num_threads_);
            for (size_t i = 0; i < num_threads_; ++i)
                deques_.emplace_back(std::make_unique<TaskDeque>());

            for (size_t i = 0; i < num_threads_; ++i)
                workers_.emplace_back(&ThreadPool::worker_loop, this, i);
        }

        [[maybe_unused]] ~ThreadPool() {
            done_.store(true, std::memory_order_relaxed);
            // let threads wake up if they’re spinning
            for (auto& t : workers_)
                if (t.joinable())
                    t.join();
        }

        // submit a task and get a future
        template<typename F, typename... Args>
        auto submit(F&& f, Args&&... args)
            -> std::future<std::invoke_result_t<F, Args...>>
        {
            using R = std::invoke_result_t<F, Args...>;
            auto task_ptr = std::make_shared<std::packaged_task<R()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );
            std::future<R> res = task_ptr->get_future();

            // wrap into type-erased Task
            TaskDeque::Task wrapper = [task_ptr]() {
                (*task_ptr)();
                };

            // push to next queue in round-robin
            size_t idx = next_queue_idx_.fetch_add(1, std::memory_order_relaxed)
                % num_threads_;
            deques_[idx]->push_bottom(wrapper);

            return res;
        }
    private:
        void worker_loop(size_t index) {
            TaskDeque& local_deque = *deques_[index];
            while (!done_.load(std::memory_order_relaxed)) {
                TaskDeque::Task task;
                if (local_deque.pop_bottom(task)) {
                    task();
                }
                else {
                    // try to steal
                    bool stolen = false;
                    for (size_t i = 1; i < num_threads_; ++i) {
                        size_t other = (index + i) % num_threads_;
                        if (deques_[other]->steal(task)) {
                            task();
                            stolen = true;
                            break;
                        }
                    }
                    if (!stolen) {
                        std::this_thread::yield();
                    }
                }
            }
        }

        std::atomic<bool>                        done_;
        const size_t                             num_threads_;
        std::vector<std::unique_ptr<TaskDeque>>  deques_;
        std::vector<std::thread>                 workers_;
        std::atomic<size_t>                      next_queue_idx_;
    };
}
