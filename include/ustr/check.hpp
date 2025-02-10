/// @file check.hpp
/// @author Enrico Fraccaroli (enry.frak@gmail.com)
/// @brief List of functions to check strings.
/// @copyright
/// Copyright (c) 2024-2025. All rights reserved.
/// Licensed under the MIT License. See LICENSE file in the project root for details.

#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace ustr
{

namespace details
{

/// @brief Compares the two characters.
/// @param ch0 The first character.
/// @param ch1 The second character.
/// @param sensitive enables case-sensitive check.
/// @return true if the characters are equal.
/// @return false otherwise.
inline auto compare_char(char ch0, char ch1, bool sensitive = false) -> bool
{
    return sensitive ? (ch0 == ch1) : (std::toupper(ch0) == std::toupper(ch1));
}

/// @brief Compares two characters.
struct compare_char_t {
    /// @brief Construct a new comparison object.
    /// @param sensitive enables case-sensitive check.
    explicit compare_char_t(bool sensitive)
        : _sensitive(sensitive)
    {
        // Nothing to do.
    }

    /// @brief Compares the two characters.
    /// @param ch0 The first character.
    /// @param ch1 The second character.
    /// @return true if the characters are equal.
    /// @return false otherwise.
    auto operator()(char ch0, char ch1) const -> bool { return ustr::details::compare_char(ch0, ch1, _sensitive); }

private:
    /// @brief Enables case-sensitive check.
    bool _sensitive;
};

} // namespace details

/// @brief Checks if the source string begins with a given string.
/// @param s source string.
/// @param prefix the prefix to check.
/// @param sensitive enables case-sensitive check.
/// @param count the number of characters to check (0 = all of prefix).
/// @return true if the string beings with the given prefix.
/// @return false otherwise.
inline auto begin_with(const std::string &s, const std::string &prefix, bool sensitive = false, std::size_t count = 0)
    -> bool
{
    if (&prefix == &s) {
        return true;
    }
    if (prefix.length() > s.length()) {
        return false;
    }
    if (s.empty() || prefix.empty()) {
        return false;
    }

    // If 0, check all.
    count = (count == 0) ? s.length() : count;

    std::string::const_iterator it0 = s.begin();
    std::string::const_iterator it1 = prefix.begin();
    while ((it1 != prefix.end()) && details::compare_char(*it0, *it1, sensitive)) {
        if (--count == 0) {
            return true;
        }
        ++it0, ++it1;
    }
    return it1 == prefix.end();
}

/// @brief Check if the source string end with a given string.
/// @param s source string.
/// @param suffix the suffix to check.
/// @param sensitive enables case-sensitive check.
/// @param count the number of characters to check (0 = all of suffix).
/// @return true if the string ends with the given suffix.
/// @return false otherwise.
inline auto end_with(const std::string &s, const std::string &suffix, bool sensitive = false, std::size_t count = 0)
    -> bool
{
    if (&suffix == &s) {
        return true;
    }
    if (suffix.length() > s.length()) {
        return false;
    }
    if (s.empty() || suffix.empty()) {
        return false;
    }

    // If 0, check all.
    count = (count == 0) ? s.length() : count;

    std::string::const_reverse_iterator it0 = s.rbegin();
    std::string::const_reverse_iterator it1 = suffix.rbegin();
    while ((it1 != suffix.rend()) && details::compare_char(*it0, *it1, sensitive)) {
        if (--count == 0) {
            return true;
        }
        ++it0, ++it1;
    }
    return it1 == suffix.rend();
}

/// @brief Checks if prefix is an abbreviation of s.
/// @param prefix the prefix to check.
/// @param s source string.
/// @param sensitive enables case-sensitive check.
/// @param min_length the minimum number of characters for the prefix.
/// @return true if the prefix is an approved abbreviation of s, false otherwise.
inline auto
is_abbreviation_of(const std::string &prefix, const std::string &s, bool sensitive = false, std::size_t min_length = 1)
    -> bool
{
    if (&prefix == &s) {
        return true;
    }
    if (prefix.length() > s.length()) {
        return false;
    }
    if (prefix.length() < min_length) {
        return false;
    }
    if (s.empty() || prefix.empty()) {
        return false;
    }
    std::string::const_iterator it0 = s.begin();
    std::string::const_iterator it1 = prefix.begin();
    while ((it1 != prefix.end()) && details::compare_char(*it0, *it1, sensitive)) {
        ++it0, ++it1;
    }
    return it1 == prefix.end();
}

/// @brief Compares the two strings.
/// @param s0 the first string.
/// @param s1 the second string.
/// @param sensitive enables case-sensitive check.
/// @param count the number of characters to compare (0 = all).
/// @return true if the strings are equal, based on the given configuration.
/// @return false otherwise.
inline auto compare(const std::string &s0, const std::string &s1, bool sensitive = false, std::size_t count = 0) -> bool
{
    // If 0, check all.
    count = (count == 0) ? std::max(s0.length(), s1.length()) : count;

    std::string::const_iterator it0 = s0.begin();
    std::string::const_iterator it1 = s1.begin();
    while ((it0 != s0.end()) && (it1 != s1.end()) && details::compare_char(*it0, *it1, sensitive)) {
        if (--count == 0) {
            return true;
        }
        ++it0, ++it1;
    }
    return (it0 == s0.end()) && (it1 == s1.end());
}

/// @brief Counts the occurences of the substring inside the given string.
/// @param str the input string.
/// @param substring the substring to count.
/// @param sensitive enables case-sensitive check.
/// @return the number of occurences.
inline auto count(const std::string &str, const std::string &substring, bool sensitive = false) -> std::size_t
{
    // Handle edge case if str or substring are empty.
    if (str.empty() || substring.empty()) {
        return 0;
    }
    std::size_t occurrences = 0;
    // Create a comparison object based on the sensitivity flag.
    details::compare_char_t compare_fn(sensitive);
    // Iterate over the string and search for the substring.
    auto it = str.begin();
    while ((it = std::search(it, str.end(), substring.begin(), substring.end(), compare_fn)) != str.end()) {
        // Increment the occurrences.
        ++occurrences;
        // Move past the current found substring.
        ++it;
    }
    return occurrences;
}

/// @brief Checks if the given control word is among those listed in the words list.
/// @param control the control word to find.
/// @param words the list of words.
/// @param sensitive enables case-sensitive check.
/// @param begins_with should we check if the words begin with control.
/// @param ends_with should we check if the words end with control.
/// @param exact_match should we check if the words are exactly like control.
/// @return true if at least one of the conditions are true.
/// @return false otherwise.
inline auto word_is_among(
    const std::string &control,
    const std::vector<std::string> &words,
    bool sensitive,
    bool begins_with,
    bool ends_with,
    bool exact_match) -> bool
{
    std::vector<std::string>::const_iterator it;
    for (it = words.begin(); it != words.end(); ++it) {
        if (begins_with && ustr::begin_with(*it, control, sensitive, 0)) {
            return true;
        }
        if (ends_with && ustr::begin_with(*it, control, sensitive, 0)) {
            return true;
        }
        if (exact_match && ustr::compare(control, *it, sensitive, 0)) {
            return true;
        }
    }
    return false;
}

} // namespace ustr
