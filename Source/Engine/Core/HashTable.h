#pragma once

#include <Core/String.h>

#include <unordered_map>
#include <filesystem>

namespace GGE
{
    template<class Key, class Value, class Allocator = std::allocator<std::pair<const Key, Value>>>
    class HashTable : public std::unordered_map<Key, Value, std::hash<Key>, std::equal_to<Key>, Allocator>
    {
    public:
        using std::unordered_map<Key, Value, std::hash<Key>, std::equal_to<Key>, Allocator>::unordered_map;
    };

    template<class Value, class Allocator = std::allocator<std::pair<const String, Value>>>
    class StringHashTable : public std::unordered_map<String, Value, std::hash<String>, std::equal_to<String>, Allocator>
    {
    public:
        using std::unordered_map<String, Value, std::hash<String>, std::equal_to<String>, Allocator>::unordered_map;
    };

    // path hash table
    template<class Value, class Allocator = std::allocator<std::pair<const std::filesystem::path, Value>>>
    class PathHashTable : public std::unordered_map<std::filesystem::path, Value, std::hash<std::filesystem::path>, std::equal_to<std::filesystem::path>, Allocator>
    {
    public:
        using std::unordered_map<std::filesystem::path, Value, std::hash<std::filesystem::path>, std::equal_to<std::filesystem::path>, Allocator>::unordered_map;
    };
}
