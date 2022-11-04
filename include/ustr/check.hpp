/// @file check.hpp

#pragma once

#include <string>

namespace ustr
{

/// @brief Checks if the source string begins with a given string.
/// @param s source string.
/// @param prefix the prefix to check.
/// @param sensitive enable case-sensitive check.
/// @param n the number of characters to check (-1 = all).
/// @return true if the string beings with the given prefix.
/// @return false otherwise.
inline bool begin_with(const std::string &s, const std::string &prefix, bool sensitive = false, int n = -1)
{
    if (&prefix == &s)
        return true;
    if (prefix.length() > s.length())
        return false;
    if (s.empty() || prefix.empty())
        return false;
    std::string::const_iterator it0 = s.begin(), it1 = prefix.begin();
    if (sensitive) {
        while ((it1 != prefix.end()) && ((*it1) == (*it0))) {
            if ((n > 0) && (--n <= 0))
                return true;
            ++it0, ++it1;
        }
    } else {
        while ((it1 != prefix.end()) && (tolower(*it1) == tolower(*it0))) {
            if ((n > 0) && (--n <= 0))
                return true;
            ++it0, ++it1;
        }
    }
    return it1 == prefix.end();
}

/// @brief Check if the source string end with a given string.
/// @param s source string.
/// @param suffix the suffix to check.
/// @param sensitive enable case-sensitive check.
/// @param n the number of characters to check (-1 = all).
/// @return true if the string ends with the given suffix.
/// @return false otherwise.
inline bool end_with(const std::string &s, const std::string &suffix, bool sensitive = false, int n = -1)
{
    if (&suffix == &s)
        return true;
    if (suffix.length() > s.length())
        return false;
    if (s.empty() || suffix.empty())
        return false;
    std::string::const_reverse_iterator it0 = s.rbegin(),
                                        it1 = suffix.rbegin();
    if (sensitive) {
        while ((it1 != suffix.rend()) && ((*it1) == (*it0))) {
            if ((n > 0) && (--n <= 0))
                return true;
            ++it0, ++it1;
        }
    } else {
        while ((it1 != suffix.rend()) && (tolower(*it1) == tolower(*it0))) {
            if ((n > 0) && (--n <= 0))
                return true;
            ++it0, ++it1;
        }
    }
    return it1 == suffix.rend();
}

/// @brief Compares the two strings.
/// @param s0 the first string.
/// @param s1 the second string.
/// @param sensitive enable case-sensitive check.
/// @param n the number of characters to compare (-1 = all).
/// @return true if the strings are equal, based on the given configuration.
/// @return false otherwise.
inline bool compare(const std::string &s0, const std::string &s1, bool sensitive = false, int n = -1)
{
    std::string::const_iterator it0 = s0.begin(), it1 = s1.begin();
    if (sensitive) {
        while ((it0 != s0.end()) && (it1 != s1.end()) && ((*it0) == (*it1))) {
            if ((n > 0) && (--n <= 0))
                return true;
            ++it0, ++it1;
        }
    } else {
        while ((it0 != s0.end()) && (it1 != s1.end()) &&
               (tolower(*it0) == tolower(*it1))) {
            if ((n > 0) && (--n <= 0))
                return true;
            ++it0, ++it1;
        }
    }
    return (it0 == s0.end()) && (it1 == s1.end());
}

/// @brief Counts the occurences of the substring inside the given string.
/// @param s the input string.
/// @param substring the substring to count.
/// @return the number of occurences.
inline std::size_t count(const std::string &s, const std::string &substring)
{
    std::size_t pos = 0, occurrences = 0;
    while ((pos = s.find(substring, pos)) != std::string::npos)
        ++occurrences, pos += substring.length();
    return occurrences;
}

} // namespace ustr
