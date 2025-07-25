#include "INI.h"

#include <Core/IO/FileResourceManager.h>
#include "inih/cini.h"

namespace GGE::Parse
{
    static String MakeKey(const String& section, const String& name)
    {
        return String(section + "=" + name).tolower();
    }

    INIReader::INIReader(const String& filename)
    {
        _error = ini_parse(filename.c_str(), ValueHandler, this);
    }

    INIReader::INIReader(const char* buffer, size_t buffer_size)
    {
        _error = ini_parse_string_length(buffer, buffer_size, ValueHandler, this);
    }

    INIReader::INIReader(const IO::RawResource& resource)
    {
        // Use the raw resource data as a buffer for parsing
        _error = ini_parse_string_length((const char*)resource.data.data(), resource.data.size(), ValueHandler, this);
        if (_error < 0) {
            // If parsing fails, set error to -1 to indicate failure
            _error = -1;
        }
    }

    int INIReader::ParseError() const
    {
        return _error;
    }

    String INIReader::Get(const String& section, const String& name, const String& default_value) const
    {
        String key = MakeKey(section, name);
        // Use _values.find() here instead of _values.at() to support pre C++11 compilers
        return _values.count(key) ? _values.find(key)->second : default_value;
    }

    String INIReader::GetString(const String& section, const String& name, const String& default_value) const
    {
        const String str = Get(section, name, "");
        return str.empty() ? default_value : str;
    }

    long INIReader::GetInteger(const String& section, const String& name, long default_value) const
    {
        String valstr = Get(section, name, "");
        const char* value = valstr.c_str();
        char* end;
        // This parses "1234" (decimal) and also "0x4D2" (hex)
        long n = strtol(value, &end, 0);
        return end > value ? n : default_value;
    }

    INI_API int64_t INIReader::GetInteger64(const String& section, const String& name, int64_t default_value) const
    {
        String valstr = Get(section, name, "");
        const char* value = valstr.c_str();
        char* end;
        // This parses "1234" (decimal) and also "0x4D2" (hex)
        int64_t n = strtoll(value, &end, 0);
        return end > value ? n : default_value;
    }

    unsigned long INIReader::GetUnsigned(const String& section, const String& name, unsigned long default_value) const
    {
        String valstr = Get(section, name, "");
        const char* value = valstr.c_str();
        char* end;
        // This parses "1234" (decimal) and also "0x4D2" (hex)
        unsigned long n = strtoul(value, &end, 0);
        return end > value ? n : default_value;
    }

    INI_API uint64_t INIReader::GetUnsigned64(const String& section, const String& name, uint64_t default_value) const
    {
        String valstr = Get(section, name, "");
        const char* value = valstr.c_str();
        char* end;
        // This parses "1234" (decimal) and also "0x4D2" (hex)
        uint64_t n = strtoull(value, &end, 0);
        return end > value ? n : default_value;
    }

    double INIReader::GetReal(const String& section, const String& name, double default_value) const
    {
        String valstr = Get(section, name, "");
        const char* value = valstr.c_str();
        char* end;
        double n = strtod(value, &end);
        return end > value ? n : default_value;
    }

    bool INIReader::GetBoolean(const String& section, const String& name, bool default_value) const
    {
        String valstr = Get(section, name, "");
        // Convert to lower case to make String comparisons case-insensitive
        valstr = valstr.tolower();
        if (valstr == "true" || valstr == "yes" || valstr == "on" || valstr == "1")
            return true;
        else if (valstr == "false" || valstr == "no" || valstr == "off" || valstr == "0")
            return false;
        else
            return default_value;
    }

    std::vector<String> INIReader::Sections() const
    {
        std::set<String> sectionSet;
        for (std::map<String, String>::const_iterator it = _values.begin(); it != _values.end(); ++it) {
            size_t pos = it->first.find('=');
            if (pos != String::npos) {
                sectionSet.insert(it->first.substr(0, pos));
            }
        }
        return std::vector<String>(sectionSet.begin(), sectionSet.end());
    }

    std::vector<String> INIReader::Keys(const String& section) const
    {
        std::vector<String> keys;
        String keyPrefix = MakeKey(section, "");
        for (std::map<String, String>::const_iterator it = _values.begin(); it != _values.end(); ++it) {
            if (it->first.compare(0, keyPrefix.length(), keyPrefix) == 0) {
                keys.push_back(it->first.substr(keyPrefix.length()));
            }
        }
        return keys;
    }

    bool INIReader::HasSection(const String& section) const
    {
        const String key = MakeKey(section, "");
        std::map<String, String>::const_iterator pos = _values.lower_bound(key);
        if (pos == _values.end())
            return false;
        // Does the key at the lower_bound pos start with "section"?
        return pos->first.compare(0, key.length(), key) == 0;
    }

    bool INIReader::HasValue(const String& section, const String& name) const
    {
        String key = MakeKey(section, name);
        return _values.count(key) != 0;
    }

    int INIReader::ValueHandler(void* user, const char* section, const char* name,
        const char* value)
    {
        if (!name)  // Happens when INI_CALL_HANDLER_ON_NEW_SECTION enabled
            return 1;
        INIReader* reader = static_cast<INIReader*>(user);
        String key = MakeKey(section, name);
        if (reader->_values[key].size() > 0)
            reader->_values[key] += "\n";
        reader->_values[key] += value ? value : "";
        return 1;
    }


    void INIWriter::Set(const String& section, const String& name, const String& value)
    {
        String key = MakeKey(section, name);
        _values[key] = value;
    }

    String INIWriter::SaveToString() const
    {
        String result;
        for (const auto& pair : _values) {
            const String& key = pair.first;
            const String& value = pair.second;
            size_t pos = key.find('=');
            if (pos != String::npos) {
                String section = key.substr(0, pos);
                String name = key.substr(pos + 1);
                if (!result.empty() && result.back() != '\n') {
                    result += '\n';
                }
                if (!section.empty()) {
                    result += "[" + section + "]\n";
                }
                result += name + "=" + value + "\n";
            }
        }
        return result;
    }

    void INIWriter::SaveToFile(const String& filename) const
    {
        auto stream = IO::FileResourceManager::Get().OpenWrite(filename);
        if (stream && stream->good()) {
            String content = SaveToString();
            *stream << content.std_string_view();
            stream->flush();
        }
    }
}
