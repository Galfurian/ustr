/// @file utility.hpp
/// @author Enrico Fraccaroli (enry.frak@gmail.com)
/// @brief List of utility functions.
/// @copyright
/// Copyright (c) 2024-2025. All rights reserved.
/// Licensed under the MIT License. See LICENSE file in the project root for details.

#pragma once

#include <array>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <sstream>

namespace ustr
{

/// @brief Transforms a string into an integer value.
/// @param str the string to turn into a number.
/// @return the number.
template <typename T>
inline auto to_number(const std::string &str) -> T
{
    char *pEnd = nullptr;
    return static_cast<T>(strtol(str.c_str(), &pEnd, 10));
}

/// @brief Transforms a string into a floating point value.
/// @param str the string to turn into a number.
/// @return the number.
template <typename T>
inline auto to_double(const std::string &str) -> T
{
    char *pEnd = nullptr;
    return static_cast<T>(strtod(str.c_str(), &pEnd));
}

/// @brief Transforms the given value into a string.
/// @param value the value to transform.
/// @return the string representation of the value.
template <typename T>
inline auto to_string(const T &value) -> std::string
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

/// @brief Checks if the given string is a number.
/// @param str the string to check.
/// @return true if it is a number.
/// @return false otherwise.
inline auto is_number(const std::string &str) -> bool
{
    if (str.empty()) {
        return false;
    }
    return str.find_first_not_of("+-0123456789") == std::string::npos;
}

/// @brief Transforms the given amount of bytes to a readable string.
/// @param bytes The bytes to turn to string.
/// @return String representing the bytes in human readable form.
inline auto to_human_size(unsigned long bytes) -> std::string
{
    static std::array<const char *, 5> suffix = {"B", "KB", "MB", "GB", "TB"};
    std::size_t index                         = 0;
    auto double_bytes                         = static_cast<double>(bytes);
    while ((bytes >= 1024) && (index < suffix.size() - 1)) {
        double_bytes = static_cast<double>(bytes) / 1024.0;
        bytes /= 1024;
        ++index;
    }
    // Using stringstream to format the result
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << double_bytes << " " << std::setw(2) << std::right << suffix[index];
    // Return the formatted string.
    return oss.str();
}

/// @brief Transforms the given value to a binary string.
/// @param value to print.
/// @param length of the binary output.
/// @return String representing the binary value.
inline auto decimal_to_binary_string(unsigned long value, unsigned length) -> std::string
{
    // Use bitset to handle binary conversion
    std::bitset<64> bits(value);
    // Get the binary string representation, and ensure it matches the requested
    // length.
    std::string binary_str = bits.to_string();
    // Trim the binary string to the specified length.
    return binary_str.substr(64 - length);
}

/// @brief Returns the ordinal that associates with the given number.
/// @param value the input value.
/// @return the ordinal suffix.
template <typename T>
inline auto get_ordinal(T value) -> std::string
{
    // Ordinal suffix array.
    static const std::array<const char *, 4> suffix = {"th", "st", "nd", "rd"};
    T ord                                           = value % 100;
    // Handle special case for 11th, 12th, 13th, etc.
    if (ord / 10 == 1) {
        ord = 0;
    }
    // Get the last digit.
    ord = ord % 10;
    // If the last digit is > 3, return "th" for all cases like 4th, 5th, etc.
    if (ord > 3) {
        ord = 0;
    }
    // Construct the ordinal string.
    return std::to_string(value) + std::string(suffix[static_cast<std::size_t>(ord)]);
}

} // namespace ustr
