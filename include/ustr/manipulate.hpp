/// @file manipulate.hpp
/// @author Enrico Fraccaroli (enry.frak@gmail.com)
/// @brief List of functions to manipulate strings.
/// @copyright
/// Copyright (c) 2024-2025. All rights reserved.
/// Licensed under the MIT License. See LICENSE file in the project root for details.

#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace ustr
{

/// @brief Removes the specified characters from both the beginning and the end of the string.
/// @param str the input string.
/// @param padchar the char that should be removed.
/// @return the trimmed string.
inline auto trim(const std::string &str, const std::string &padchar = " ") -> std::string
{
    std::string::size_type left  = str.find_first_not_of(padchar);
    std::string::size_type right = str.find_last_not_of(padchar);
    return (left != std::string::npos) ? str.substr(left, right - left + 1) : "";
}

/// @brief Removes the specified characters from the beginning of the string.
/// @param str the input string.
/// @param padchar the char that should be removed.
/// @return the trimmed string.
inline auto ltrim(const std::string &str, const std::string &padchar = " ") -> std::string
{
    std::string::size_type left = str.find_first_not_of(padchar);
    return (left != std::string::npos) ? str.substr(left) : "";
}

/// @brief Removes the specified characters from the end of the string.
/// @param str the input string.
/// @param padchar the char that should be removed.
/// @return the trimmed string.
inline auto rtrim(const std::string &str, const std::string &padchar = " ") -> std::string
{
    std::string::size_type right = str.find_last_not_of(padchar);
    return (right != std::string::npos) ? str.substr(0, right + 1) : "";
}

/// @brief Converts the string to all uper-case.
/// @param str the input string.
/// @return the new string.
inline auto to_upper(std::string str) -> std::string
{
    for (char &chr : str) {
        chr = static_cast<char>(toupper(chr));
    }
    return str;
}

/// @brief Converts the string to all lower-case.
/// @param str the input string.
/// @return the new string.
inline auto to_lower(std::string str) -> std::string
{
    for (char &chr : str) {
        chr = static_cast<char>(tolower(chr));
    }
    return str;
}

/// @brief Aligns the string to the right.
/// @param str the input string.
/// @param width the full lenght of the final string.
/// @param fill the char used to fill the tring.
/// @return the aligned string.
inline auto ralign(std::string str, std::string::size_type width, char fill = ' ') -> std::string
{
    std::string::size_type pad = (width > str.length()) ? (width - str.length()) : 0;
    return str.insert(0, pad, fill);
}

/// @brief Aligns the string to the left.
/// @param str the input string.
/// @param width the full lenght of the final string.
/// @param fill the char used to fill the tring.
/// @return the aligned string.
inline auto lalign(std::string str, std::string::size_type width, char fill = ' ') -> std::string
{
    std::string::size_type pad = (width > str.length()) ? (width - str.length()) : 0;
    return str.append(pad, fill);
}

/// @brief Center aligns the string.
/// @param str the input string.
/// @param width the full lenght of the final string.
/// @param fill the char used to fill the tring.
/// @return the aligned string.
inline auto calign(std::string str, std::string::size_type width, char fill = ' ') -> std::string
{
    std::string::size_type len   = str.length();
    std::string::size_type pad   = (width > len) ? (width - len) / 2 : 0;
    std::string::size_type extra = (width > len) ? (width - len) % 2 : 0;
    return str.insert(0, pad, fill).append(pad + extra, fill);
}

/// @brief Replaces all count of the given substring.
/// @param str the input string.
/// @param substring the substring that should be replaced.
/// @param substitute the substitute.
/// @param count how many count should we replace (0 = all of them).
/// @return a reference to the modified string.
inline auto replace(std::string str, const std::string &substring, const std::string &substitute, std::size_t count = 0)
    -> std::string
{
    // Early exit if the substring is empty (no replacement needed).
    if (substring.empty()) {
        return str;
    }

    std::string::size_type pos = 0;

    // If 0, replace all occurrences.
    count = (count == 0) ? str.length() : count;

    while ((pos = str.find(substring, pos)) != std::string::npos && count > 0) {
        str.replace(pos, substring.size(), substitute);
        // Move past the substituted part.
        pos += substitute.size();
        // Stop once we've replaced the required number of occurrences.
        if (--count == 0) {
            break;
        }
    }

    return str;
}

/// @brief Replaces all occurrences of the given substring.
/// @param str the input string.
/// @param substring the substring that should be replaced.
/// @param substitute the substitute.
/// @param count how many occurrences should we replace (0 = all of them).
/// @return a reference to the modified string.
inline auto
replace_inplace(std::string &str, const std::string &substring, const std::string &substitute, std::size_t count = 0)
    -> std::string &
{
    // Early exit if the substring is empty (no replacement needed).
    if (substring.empty()) {
        return str;
    }

    std::string::size_type pos = 0;

    // If 0, replace all occurrences.
    count = (count == 0) ? str.length() : count;

    while ((pos = str.find(substring, pos)) != std::string::npos && count > 0) {
        str.replace(pos, substring.size(), substitute);
        // Move past the substituted part.
        pos += substitute.size();
        // Stop once we've replaced the required number of occurrences.
        if (--count == 0) {
            break;
        }
    }

    return str;
}

/// @brief Strips the given character from the string.
/// @param str the input string.
/// @param chr the character to remove.
/// @return the modified string.
inline auto strip(std::string str, char chr) -> std::string
{
    // Remove all occurrences of the character 'chr' in the string
    str.erase(std::remove(str.begin(), str.end(), chr), str.end());
    return str;
}

/// @brief Strips the given character from the string.
/// @param str the input string.
/// @param chr the character to remove.
/// @return a reference to the modified string.
inline auto strip_inplace(std::string &str, char chr) -> std::string &
{
    // Remove all occurrences of the character 'chr' in the string
    str.erase(std::remove(str.begin(), str.end(), chr), str.end());
    return str;
}

/// @brief Transforms a single-line string a paragraph formatted string.
/// @param str the input string.
/// @param width the width of the paragraphs.
/// @param whitespace the filler character.
/// @return the string splitted into paragraphs.
inline auto split_paragraph(std::string str, std::string::size_type width, const std::string &whitespace = " \t\r")
    -> std::string
{
    std::string::size_type index    = width - 1;
    std::string::size_type index_nl = 0;
    std::string::size_type to_trim  = 0;

    while (index < str.length()) {
        index = str.find_last_of(whitespace, index + 1);
        if (index == std::string::npos) {
            break;
        }
        index = str.find_last_not_of(whitespace, index);
        if (index == std::string::npos) {
            break;
        }
        to_trim = str.find_first_not_of(whitespace, index + 1) - index - 1;
        str.replace(index + 1, to_trim, "\n");
        index_nl = str.find_first_of('\n', index + 1 + to_trim);
        if (index_nl < (index + width)) {
            index = index_nl;
        }
        index += (width + 1);
    }
    return str;
}

/// @brief Transforms a paragraph formatted string into a single line.
/// @param str the string to manipulate.
/// @return the single line.
inline auto merge_paragraph(std::string str) -> std::string
{
    for (std::string::size_type i = 1, j = 1; i < str.length(); ++i) {
        if (str[i] == ' ') {
            // Remove multiple spaces.
            // Go searching for the last ' ' of a series of ' '.
            for (j = i + 1; (j < str.length()) && (str[j] == ' '); ++j) {
                ;
            }
            // Compute the amount of characters to remove.
            std::string::size_type to_remove = (j - i) - 1;
            // Remove the excess spaces.
            str.erase(i, to_remove);
        } else if (str[i] == '\n') {
            // Remove newlines and compress more than two newlines.
            // Go searching for the last '\n' of a series of '\n'.
            for (j = i + 1; (j < str.length()) && (str[j] == '\n'); ++j) {
            }
            // Compute the amount of characters to remove. Take advantage of bool,
            //  because if we have more than 1 '\n' it means that we need to remove
            //  all of them except one.
            std::string::size_type to_remove = (j - i) - static_cast<std::string::size_type>(j - i > 1);
            // Remove the excess newlines.
            str.replace(i, to_remove, " ");
            // Move after the eventual Wanted new-line.
            i += static_cast<std::string::size_type>(j - i > 1);
        }
    }
    return str;
}

/// @brief Given a string and a delimiter, the string is splitted by using the delimiter.
/// @param str the input string.
/// @param delimiter the delimiter which has to be used.
/// @return the splitted string.
inline auto split(std::string const &str, std::string const &delimiter) -> std::vector<std::string>
{
    std::vector<std::string> result;
    std::string::size_type curr = 0;
    std::string::size_type next = 0;
    while ((next = str.find_first_of(delimiter, curr)) != std::string::npos) {
        if (next - curr > 0) {
            result.push_back(str.substr(curr, next - curr));
        }
        curr = next + 1;
    }
    std::string last(str, curr);
    if (!last.empty()) {
        result.push_back(last);
    }
    return result;
}

/// @brief Capitalize the first letter of the string.
/// @param str the input string.
/// @param count the number of occurrences we need to manipulate (0 = all of them).
/// @return the string with the first letter capitalized.
inline auto capitalize(std::string str, std::size_t count = 0) -> std::string
{
    // Early exit if the string is empty.
    if (str.empty()) {
        return str;
    }

    // If 0, capitalize all.
    count = (count == 0) ? str.length() : count;

    for (std::string::size_type pos = 0; pos < str.length() && count > 0; ++pos) {
        if ((pos == 0 && (isalpha(str[pos]) != 0)) || (pos > 0 && str[pos - 1] == ' ')) {
            // Capitalize the character.
            str[pos] = static_cast<char>(std::toupper(str[pos]));
            // Stop once we reach the required number of occurrences.
            if (--count == 0) {
                break;
            }
        }
    }

    return str;
}

/// @brief Restituisce una stringa con la prima lettera minuscola.
/// @param str La stringa sorgente.
/// @param count Il numero di occorrenze da modificare (0 = tutte).
/// @return La stringa con la prima lettera minuscola.
inline auto decapitalize(std::string str, std::size_t count = 0) -> std::string
{
    // Early exit if the string is empty.
    if (str.empty()) {
        return str;
    }

    // If 0, decapitalize all.
    count = (count == 0) ? str.length() : count;

    for (std::string::size_type pos = 0; pos < str.length() && count > 0; ++pos) {
        if ((pos == 0 && (isalpha(str[pos]) != 0)) || (pos > 0 && str[pos - 1] == ' ')) {
            // Decapitalize the character.
            str[pos] = static_cast<char>(std::tolower(str[pos]));
            // Stop once we reach the required number of occurrences.
            if (--count == 0) {
                break;
            }
        }
    }

    return str;
}

} // namespace ustr
