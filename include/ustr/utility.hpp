/// @file utility.hpp

#pragma once

#include <cmath>
#include <cstdlib>
#include <sstream>

namespace ustr
{

/// @brief Transforms a string into an integer value.
/// @param s the string to turn into a number.
/// @return the number.
template <typename T>
T to_number(const std::string &s)
{
    char *pEnd;
    return static_cast<T>(strtol(s.c_str(), &pEnd, 10));
}

/// @brief Transforms a string into a floating point value.
/// @param s the string to turn into a number.
/// @return the number.
template <typename T>
T to_double(const std::string &s)
{
    char *pEnd;
    return static_cast<T>(strtod(s.c_str(), &pEnd));
}

/// @brief Transforms the given value into a string.
/// @param value the value to transform.
/// @return the string representation of the value.
template <typename T>
std::string to_string(const T &value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

/// @brief Transforms the given amount of bytes to a readable string.
/// @param bytes The bytes to turn to string.
/// @return String representing the bytes in human readable form.
const char *to_human_size(unsigned long bytes)
{
    static char output[200];
    const char *suffix[] = { "B", "KB", "MB", "GB", "TB" };
    char length          = sizeof(suffix) / sizeof(suffix[0]);
    int i                = 0;
    double double_bytes  = static_cast<double>(bytes);
    if (bytes > 1024) {
        for (i = 0; (bytes / 1024) > 0 && i < length - 1; i++, bytes /= 1024) {
            double_bytes = static_cast<double>(bytes) / 1024.0;
        }
    }
    sprintf(output, "%.02lf %2s", double_bytes, suffix[i]);
    return output;
}

/// @brief Transforms the given value to a binary string.
/// @param value to print.
/// @param length of the binary output.
/// @return String representing the binary value.
const char *decimal_to_binary_string(unsigned long value, unsigned length)
{
    static char buffer[33];
    for (unsigned i = 0; i < 33; ++i) {
        buffer[i] = 0;
    }
    for (unsigned i = 0, j = 32 - std::min(std::max(0U, length), 32U); j < 32; ++i, ++j) {
        buffer[i] = (value & (1U << (31U - j))) ? '1' : '0';
    }
    return buffer;
}

/// @brief Returns the ordinal that associates with the given number.
/// @param value the input value.
/// @return the ordinal suffix.
template <typename T>
inline const char *get_ordinal(T value)
{
    static const char suffixes[][3] = { "th", "st", "nd", "rd" };
    T ord                           = value % 100;
    if (ord / 10 == 1) {
        ord = 0;
    }
    ord = ord % 10;
    if (ord > 3) {
        ord = 0;
    }
    return suffixes[ord];
}

} // namespace ustr