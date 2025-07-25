#pragma once

#include <Core/Minimal.h>

#include <mutex>
#include <optional>
#include <list>

namespace GGE::IO
{
    template<class Key, class Value>
    class LRUCache
    {
        template<class Key, class MapValue>
        struct MapType
        {
            typedef std::unordered_map<Key, MapValue> type;
        };

        template<class MapValue>
        struct MapType<String, MapValue>
        {
            typedef StringHashTable<MapValue> type;
        };
    public:
        LRUCache(size_t maxSizeBytes) : m_maxSize(maxSizeBytes), m_currentSize(0) {}
        ~LRUCache() = default;

        LRUCache(const LRUCache&) = delete;
        LRUCache(LRUCache&&) = delete;
        LRUCache& operator=(const LRUCache&) = delete;
        LRUCache& operator=(LRUCache&&) = delete;

        void SetMaxSize(size_t bytes) {
            std::unique_lock lock(m_mutex);
            m_maxSize = bytes;
            _EvictIfNeeded();
        }

        std::optional<Value> Get(const Key& key) {
            std::unique_lock lock(m_mutex);
            auto it = m_map.find(key);
            if (it == m_map.end()) return std::nullopt;
            // move used entry to front
            m_order.splice(m_order.begin(), m_order, it->second.iter);
            return it->second.value;
        }

        void Put(const Key& key, const Value& value, size_t sizeBytes) {
            std::unique_lock lock(m_mutex);
            if (m_map.count(key)) return;
            m_order.push_front(key);
            m_map[key] = { value, sizeBytes, m_order.begin() };
            m_currentSize += sizeBytes;
            _EvictIfNeeded();
        }

        bool Remove(const Key& key) {
            std::unique_lock lock(m_mutex);
            auto it = m_map.find(key);
            if (it == m_map.end()) return false;
            m_currentSize -= it->second.size;
            m_order.erase(it->second.iter);
            m_map.erase(it);
            return true;
        }

        void Clear() {
            std::unique_lock lock(m_mutex);
            m_map.clear();
            m_order.clear();
            m_currentSize = 0;
        }

    private:
        struct Entry 
        { 
            Value value; 
            size_t size{};
            typename std::list<Key>::iterator iter; 
        };

        void _EvictIfNeeded() {
            while (m_currentSize > m_maxSize && !m_order.empty()) {
                const auto& key = m_order.back();
                auto it = m_map.find(key);
                m_currentSize -= it->second.size;
                m_order.pop_back();
                m_map.erase(it);
            }
        }

        size_t m_maxSize;
        size_t m_currentSize;
        std::list<Key> m_order;
        typename MapType<Key, Entry>::type m_map;
        std::mutex m_mutex;
    };
}
