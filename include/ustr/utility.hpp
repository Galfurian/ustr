/// @file utility.hpp

#pragma once

#include <sstream>
#include <stdlib.h>

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