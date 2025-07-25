#pragma once

#include <Core/Minimal.h>

#include <vector>
#include <map>
#include <set>

namespace GGE::IO
{
    struct RawResource; // Forward declaration
}

namespace GGE::Parse
{
    // Read an INI file into easy-to-access name/value pairs. (Note that I've gone
    // for simplicity here rather than speed, but it should be pretty decent.)
    class INIReader
    {
    public:
        // Construct INIReader and parse given filename. See ini.h for more info
        // about the parsing.
        explicit INIReader(const String& filename);

        // Construct INIReader and parse given buffer. See ini.h for more info
        // about the parsing.
        explicit INIReader(const char* buffer, size_t buffer_size);

        // Construct INIReader and parse given IO::RawResource. See ini.h for more info
        explicit INIReader(const IO::RawResource& resource);

        // Return the result of ini_parse(), i.e., 0 on success, line number of
        // first error on parse error, or -1 on file open error.
        int ParseError() const;

        // Get a string value from INI file, returning default_value if not found.
        String Get(const String& section, const String& name,
            const String& default_value) const;

        // Get a string value from INI file, returning default_value if not found,
        // empty, or contains only whitespace.
        String GetString(const String& section, const String& name,
            const String& default_value) const;

        // Get an integer (long) value from INI file, returning default_value if
        // not found or not a valid integer (decimal "1234", "-1234", or hex "0x4d2").
        long GetInteger(const String& section, const String& name, long default_value) const;

        // Get a 64-bit integer (int64_t) value from INI file, returning default_value if
        // not found or not a valid integer (decimal "1234", "-1234", or hex "0x4d2").
        int64_t GetInteger64(const String& section, const String& name, int64_t default_value) const;

        // Get an unsigned integer (unsigned long) value from INI file, returning default_value if
        // not found or not a valid unsigned integer (decimal "1234", or hex "0x4d2").
        unsigned long GetUnsigned(const String& section, const String& name, unsigned long default_value) const;

        // Get an unsigned 64-bit integer (uint64_t) value from INI file, returning default_value if
        // not found or not a valid unsigned integer (decimal "1234", or hex "0x4d2").
        uint64_t GetUnsigned64(const String& section, const String& name, uint64_t default_value) const;

        // Get a real (floating point double) value from INI file, returning
        // default_value if not found or not a valid floating point value
        // according to strtod().
        double GetReal(const String& section, const String& name, double default_value) const;

        // Get a boolean value from INI file, returning default_value if not found or if
        // not a valid true/false value. Valid true values are "true", "yes", "on", "1",
        // and valid false values are "false", "no", "off", "0" (not case sensitive).
        bool GetBoolean(const String& section, const String& name, bool default_value) const;

        // Return a newly-allocated vector of all section names, in alphabetical order.
        std::vector<String> Sections() const;

        // Return a newly-allocated vector of keys in the given section, in alphabetical order.
        std::vector<String> Keys(const String& section) const;

        // Return true if the given section exists (section must contain at least
        // one name=value pair).
        bool HasSection(const String& section) const;

        // Return true if a value exists with the given section and field names.
        bool HasValue(const String& section, const String& name) const;

    protected:
        int _error;
        std::map<String, String> _values;
        static String MakeKey(const String& section, const String& name);
        static int ValueHandler(void* user, const char* section, const char* name,
            const char* value);
    };

    class INIWriter
    {
    public:
        // Write a value to the INI file. If the section does not exist, it will be created.
        void Set(const String& section, const String& name, const String& value);
        
        // Write an integer value to the INI file.
        void SetInteger(const String& section, const String& name, long value)
        {
            Set(section, name, std::to_string(value));
        }
        
        // Write a 64-bit integer value to the INI file.
        void SetInteger64(const String& section, const String& name, int64_t value)
        {
            Set(section, name, std::to_string(value));
        }
        // Write an unsigned integer value to the INI file.
        void SetUnsigned(const String& section, const String& name, unsigned long value)
        {
            Set(section, name, std::to_string(value));
        }
        
        // Write an unsigned 64-bit integer value to the INI file.
        void SetUnsigned64(const String& section, const String& name, uint64_t value)
        {
            Set(section, name, std::to_string(value));
        }
        
        // Write a real (floating point) value to the INI file.
        void SetReal(const String& section, const String& name, double value)
        {
            Set(section, name, std::to_string(value));
        }
        
        // Write a boolean value to the INI file.
        void SetBoolean(const String& section, const String& name, bool value)
        {
            Set(section, name, std::to_string(value));
        }

        // Save the INI data to a file.
        void SaveToFile(const String& filename) const;
        // Save the INI data to a string.   
        String SaveToString() const;
    private:
        std::map<String, String> _values; // section -> (name -> value)

        static String MakeKey(const String& section, const String& name);
    };
}
