#pragma once

#include <Core/Primitives.h>

GUARD_EXTERNAL_INCLUDE_BEGIN
#include <SIMD_String/SIMDString.h>
GUARD_EXTERNAL_INCLUDE_END

#include <format>

namespace GGE
{
    template<size_t INTERNAL_SIZE = 64, class Allocator = std::allocator<char>>
    class BaseSimdString : public SIMDString<INTERNAL_SIZE, Allocator>
    {
    public:
        using SIMDString<INTERNAL_SIZE, Allocator>::SIMDString;
        // Additional constructors or methods can be added here if needed

        // std::basic_string constructors
        BaseSimdString(const std::string& str)
            : SIMDString<INTERNAL_SIZE, Allocator>(str.data(), str.size()) {}

        // std::string_view constructors
        BaseSimdString(const std::string_view& sv)
            : SIMDString<INTERNAL_SIZE, Allocator>(sv.data(), sv.size()) {}

        // from SIMDString<N, Allocator>
        template<size_t OTHER_INTERNAL_SIZE, class OtherAllocator>
        BaseSimdString(const SIMDString<OTHER_INTERNAL_SIZE, OtherAllocator>& simdStr)
            : SIMDString<INTERNAL_SIZE, Allocator>(simdStr.data(), simdStr.size()) {}

        // conversion from std::wstring
        BaseSimdString(const std::wstring& wstr)
        {
            size_t len = wstr.size();
            this->resize(len);
            for (size_t i = 0; i < len; ++i)
            {
                this->data()[i] = static_cast<char>(wstr[i]);
            }
            this->data()[len] = '\0'; // Null-terminate
        }

        std::string std_string() const
        {
            return std::string(this->data(), this->size());
        }

        std::string_view std_string_view() const
        {
            return std::string_view(this->data(), this->size());
        }

        template<std::integral T>
        static BaseSimdString hex(T v)
        {
            static constexpr char kHex[] = "0123456789abcdef";
            std::array<char, 16> out{};
            for (int i = 15; i >= 0; --i) 
            { 
                out[i] = kHex[v & 0xF]; 
                v >>= 4; 
            }

            return BaseSimdString(out.begin(), out.end());
        }

        BaseSimdString substr(size_t pos = 0, size_t count = std::string::npos) const
        {
            if (pos > this->size())
                throw std::out_of_range("BaseSimdString::substr: position out of range");
            if (count == std::string::npos || pos + count > this->size())
                count = this->size() - pos;
            return BaseSimdString(this->data() + pos, count);
        }

        BaseSimdString tolower() const
        {
            BaseSimdString result(*this);
            for (size_t i = 0; i < result.size(); ++i)
            {
                result.data()[i] = static_cast<char>(std::tolower(result.data()[i]));
            }
            return result;
        }

        BaseSimdString toupper() const
        {
            BaseSimdString result(*this);
            for (size_t i = 0; i < result.size(); ++i)
            {
                result.data()[i] = static_cast<char>(std::toupper(result.data()[i]));
            }
            return result;
        }

        bool starts_with(const std::string_view& prefix) const
        {
            return this->size() >= prefix.size() && std::equal(this->data(), this->data() + prefix.size(), prefix.begin());
        }

        bool ends_with(const std::string_view& suffix) const
        {
            return this->size() >= suffix.size() && std::equal(this->data() + this->size() - suffix.size(), this->data() + this->size(), suffix.begin());
        }

        bool contains(const std::string_view& substring) const
        {
            return this->find(substring) != std::string::npos;
        }

        // fast formatting
        template<typename... Args>
        void format(const BaseSimdString<>& fmt, Args&&... args)
        {
            // using std::format, as we're on C++23
            if constexpr (std::is_same_v<Allocator, std::allocator<char>>)
            {
                this->assign(std::vformat(fmt.std_string_view(), std::make_format_args(std::forward<Args>(args)...)));
            }
            else
            {
                // For custom allocators, we need to handle the allocation manually
                std::string formatted = std::vformat(fmt.std_string_view(), std::make_format_args(std::forward<Args>(args)...));
                this->assign(formatted.data(), formatted.size());
            }
        }

        template<typename... Args>
        static BaseSimdString<> formatted(const BaseSimdString<>& fmt, Args&&... args)
        {
            BaseSimdString<> result;
            result.format(fmt, std::forward<Args>(args)...);
            return result;
        }
    };

    // binary string operations
    inline BaseSimdString<> operator+(const BaseSimdString<>& lhs, const BaseSimdString<>& rhs)
    {
        BaseSimdString<> result(lhs);
        result.append(rhs.data(), rhs.size());
        return result;
    }

    inline BaseSimdString<> operator+(const BaseSimdString<>& lhs, const std::string& rhs)
    {
        BaseSimdString<> result(lhs);
        result.append(rhs.data(), rhs.size());
        return result;
    }

    inline BaseSimdString<> operator+(const BaseSimdString<>& lhs, const std::string_view& rhs)
    {
        BaseSimdString<> result(lhs);
        result.append(rhs.data(), rhs.size());
        return result;
    }

    inline BaseSimdString<> operator+(const BaseSimdString<>& lhs, const char* rhs)
    {
        BaseSimdString<> result(lhs);
        if (rhs)
        {
            size_t len = std::strlen(rhs);
            result.append(rhs, len);
        }
        return result;
    }

    inline BaseSimdString<> operator+(const BaseSimdString<>& lhs, char rhs)
    {
        BaseSimdString<> result(lhs);
        result.push_back(rhs);
        return result;
    }

    inline BaseSimdString<> operator+(const std::string& lhs, const BaseSimdString<>& rhs)
    {
        BaseSimdString<> result(lhs);
        result.append(rhs.data(), rhs.size());
        return result;
    }

    inline BaseSimdString<> operator+(const std::string_view& lhs, const BaseSimdString<>& rhs)
    {
        BaseSimdString<> result(lhs);
        result.append(rhs.data(), rhs.size());
        return result;
    }

    inline BaseSimdString<> operator+(const char* lhs, const BaseSimdString<>& rhs)
    {
        BaseSimdString<> result(lhs);
        result.append(rhs.data(), rhs.size());
        return result;
    }

    inline BaseSimdString<> operator+(char lhs, const BaseSimdString<>& rhs)
    {
        BaseSimdString<> result;
        result.push_back(lhs);
        result.append(rhs.data(), rhs.size());
        return result;
    }

    using String = BaseSimdString<>;
    using SmallString = BaseSimdString<16>;

    class StringView : public std::basic_string_view<char>
    {
    public:
        using std::basic_string_view<char>::basic_string_view;

        template<size_t INTERNAL_SIZE, class Allocator>
        StringView(const BaseSimdString<INTERNAL_SIZE, Allocator>& str)
            : std::basic_string_view<char>(str.data(), str.size()) {}

        //StringView(const std::string& str)
        //    : std::basic_string_view<char>(str.data(), str.size()) {}

        StringView(const std::string_view& sv)
            : std::basic_string_view<char>(sv.data(), sv.size()) {}

        std::string std_string() const
        {
            return std::string(this->data(), this->size());
        }

        std::string_view std_string_view() const
        {
            return std::string_view(this->data(), this->size());
        }
    };

    // concept for containers with begin(), end()
    template<typename T>
    concept BufferedStringContainer = requires(T t) {
        { t.begin() } -> std::input_iterator;
        { t.end() } -> std::input_iterator;
        { t.push_back(std::declval<typename T::value_type>()) };
        { t.clear() };
        { t.size() } -> std::convertible_to<size_t>;
        { t.data() } -> std::convertible_to<typename T::value_type*>;
        { t.empty() } -> std::convertible_to<bool>;
        { t.reserve(std::declval<size_t>()) } -> std::same_as<void>;
        { t.resize(std::declval<size_t>()) } -> std::same_as<void>;
        { t.capacity() } -> std::convertible_to<size_t>;
    };

    // class for loading array of bytes into a container of bytes (string or vector, etc.)
    // using a string-like operations
    template<BufferedStringContainer Container>
    class BufferedStringLoader
    {
        using value_type = typename Container::value_type;
    public:
        BufferedStringLoader(Container& container) : m_container(container) {}

        BufferedStringLoader(const BufferedStringLoader&) = delete;
        BufferedStringLoader(BufferedStringLoader&&) = delete;
        BufferedStringLoader& operator=(const BufferedStringLoader&) = delete;
        BufferedStringLoader& operator=(BufferedStringLoader&&) = delete;

        void clear()
        {
            m_container.clear();
        }

        // append a single character
        void append(value_type c)
        {
            m_container.push_back(c);
        }

        // append a range of characters
        template<typename InputIt>
        void append(InputIt first, InputIt last)
        {
            m_container.reserve(m_container.size() + std::distance(first, last));

            for (auto it = first; it != last; ++it)
            {
                m_container.push_back(value_type(*it));
            }
        }

        // append a string
        void append(const std::string& str)
        {
            m_container.reserve(m_container.size() + str.size());
            for (const auto& c : str)
            {
                m_container.push_back(value_type(c));
            }
        }

        // append a string_view
        void append(const std::string_view& sv)
        {
            m_container.reserve(m_container.size() + sv.size());
            for (const auto& c : sv)
            {
                m_container.push_back(value_type(c));
            }
        }

        // append a C-style string
        void append(const char* str)
        {
            if (str)
            {
                size_t len = std::strlen(str);
                m_container.reserve(m_container.size() + len);
                for (size_t i = 0; i < len; ++i)
                {
                    m_container.push_back(value_type(str[i]));
                }
            }
        }

        // append a range of characters from a C-style string
        void append(const char* str, size_t count)
        {
            if (str && count > 0)
            {
                m_container.reserve(m_container.size() + count);
                for (size_t i = 0; i < count; ++i)
                {
                    m_container.push_back(value_type(str[i]));
                }
            }
        }

        // append a BaseSimdString
        template<size_t INTERNAL_SIZE, class Allocator>
        void append(const BaseSimdString<INTERNAL_SIZE, Allocator>& str)
        {
            m_container.reserve(m_container.size() + str.size());
            for (size_t i = 0; i < str.size(); ++i)
            {
                m_container.push_back(value_type(str.data()[i]));
            }
        }

        // append a StringView
        void append(const StringView& sv)
        {
            m_container.reserve(m_container.size() + sv.size());
            for (const auto& c : sv)
            {
                m_container.push_back(value_type(c));
            }
        }

        // finalize the loading, ensuring the container is null-terminated
        void finalize()
        {
            if (!m_container.empty() && m_container.back() != value_type('\0'))
            {
                m_container.push_back(value_type('\0'));
            }
        }


        // get the underlying container
        Container& get() { return m_container; }
        const Container& get() const { return m_container; }
    private:
        Container& m_container;
    };

}

namespace std
{
    template<size_t INTERNAL_SIZE, class Allocator>
    struct hash<GGE::BaseSimdString<INTERNAL_SIZE, Allocator>>
    {
        size_t operator()(const GGE::BaseSimdString<INTERNAL_SIZE, Allocator>& str) const noexcept
        {
            return std::hash<std::string>()(str.std_string());
        }
    };

    template<>
    struct hash<GGE::StringView>
    {
        size_t operator()(const GGE::StringView& str) const noexcept
        {
            return std::hash<std::string_view>()(str);
        }
    };
} // namespace std
