/// @file check.hpp

#pragma once

#include <string>
#include <vector>
#include <algorithm>

namespace ustr
{

/// @brief Checks if the source string begins with a given string.
/// @param s source string.
/// @param prefix the prefix to check.
/// @param sensitive enable case-sensitive check.
/// @param n the number of characters to check (0 = all).
/// @return true if the string beings with the given prefix.
/// @return false otherwise.
inline bool begin_with(const std::string &s, const std::string &prefix, bool sensitive, unsigned n)
{
    auto __compare_char = [&sensitive](char c0, char c1) {
        return sensitive ? (c0 == c1) : (tolower(c0) == tolower(c1));
    };
    if (&prefix == &s) {
        return true;
    }
    if (prefix.length() > s.length()) {
        return false;
    }
    if (s.empty() || prefix.empty()) {
        return false;
    }
    typename std::string::const_iterator it0 = s.begin(), it1 = prefix.begin();
    while ((it1 != prefix.end()) && __compare_char(*it0, *it1)) {
        if ((n > 0) && (--n <= 0)) {
            return true;
        }
        ++it0, ++it1;
    }
    return it1 == prefix.end();
}

/// @brief Check if the source string end with a given string.
/// @param s source string.
/// @param suffix the suffix to check.
/// @param sensitive enable case-sensitive check.
/// @param n the number of characters to check (0 = all).
/// @return true if the string ends with the given suffix.
/// @return false otherwise.
inline bool end_with(const std::string &s, const std::string &suffix, bool sensitive, unsigned n)
{
    auto __compare_char = [&sensitive](char c0, char c1) {
        return sensitive ? (c0 == c1) : (tolower(c0) == tolower(c1));
    };
    if (&suffix == &s) {
        return true;
    }
    if (suffix.length() > s.length()) {
        return false;
    }
    if (s.empty() || suffix.empty()) {
        return false;
    }
    typename std::string::const_reverse_iterator it0 = s.rbegin(), it1 = suffix.rbegin();
    while ((it1 != suffix.rend()) && __compare_char(*it0, *it1)) {
        if ((n > 0) && (--n <= 0)) {
            return true;
        }
        ++it0, ++it1;
    }
    return it1 == suffix.rend();
}

/// @brief Compares the two strings.
/// @param s0 the first string.
/// @param s1 the second string.
/// @param sensitive enable case-sensitive check.
/// @param n the number of characters to compare (0 = all).
/// @return true if the strings are equal, based on the given configuration.
/// @return false otherwise.
inline bool compare(const std::string &s0, const std::string &s1, bool sensitive, unsigned n)
{
    auto __compare_char = [&sensitive](char c0, char c1) {
        return sensitive ? (c0 == c1) : (tolower(c0) == tolower(c1));
    };
    typename std::string::const_iterator it0 = s0.begin(), it1 = s1.begin();
    while ((it0 != s0.end()) && (it1 != s1.end()) && __compare_char(*it0, *it1)) {
        if ((n > 0) && (--n <= 0)) {
            return true;
        }
        ++it0, ++it1;
    }
    return (it0 == s0.end()) && (it1 == s1.end());
}

/// @brief Counts the occurences of the substring inside the given string.
/// @param s the input string.
/// @param substring the substring to count.
/// @return the number of occurences.
inline std::size_t count(const std::string &s, const std::string &substring, bool sensitive)
{
    auto __compare_char = [&sensitive](char c0, char c1) {
        return sensitive ? (c0 == c1) : (tolower(c0) == tolower(c1));
    };
    std::size_t occurrences          = 0;
    std::string::difference_type pos = 0, length = static_cast<std::string::difference_type>(substring.length());
    while ((std::search(s.begin() + pos, s.end(), substring.begin(), substring.end(), __compare_char)) != s.end()) {
        ++occurrences, pos += length;
    }
    return occurrences;
}

inline bool word_is_among(
    const std::string &word,
    const std::vector<std::string> words,
    bool sensitive,
    bool begins_with,
    bool ends_with,
    bool exact_match)
{
    typename std::vector<std::string>::const_iterator it;
    for (it = words.begin(); it != words.end(); ++it) {
        if (begins_with && ustr::begin_with(*it, word, sensitive, 0)) {
            return true;
        }
        if (ends_with && ustr::begin_with(*it, word, sensitive, 0)) {
            return true;
        }
        if (exact_match && ustr::compare(word, *it, sensitive, 0)) {
            return true;
        }
    }
    return false;
}

} // namespace ustr
