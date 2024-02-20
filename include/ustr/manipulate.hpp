/// @file manipulate.hpp
/// @author Enrico Fraccaroli (enry.frak@gmail.com)
/// @brief List of functions to manipulate strings.

#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace ustr
{

/// @brief Removes the specified characters from both the beginning and the end of the string.
/// @param s the input string.
/// @param padchar the char that should be removed.
/// @return the trimmed string.
inline std::string trim(const std::string &s, const std::string &padchar = " ")
{
    std::string::size_type left  = s.find_first_not_of(padchar);
    std::string::size_type right = s.find_last_not_of(padchar);
    return (left != std::string::npos) ? s.substr(left, right - left + 1) : "";
}

/// @brief Removes the specified characters from the beginning of the string.
/// @param s the input string.
/// @param padchar the char that should be removed.
/// @return the trimmed string.
inline std::string ltrim(const std::string &s, const std::string &padchar = " ")
{
    std::string::size_type left = s.find_first_not_of(padchar);
    return (left != std::string::npos) ? s.substr(left) : "";
}

/// @brief Removes the specified characters from the end of the string.
/// @param s the input string.
/// @param padchar the char that should be removed.
/// @return the trimmed string.
inline std::string rtrim(const std::string &s, const std::string &padchar = " ")
{
    std::string::size_type right = s.find_last_not_of(padchar);
    return (right != std::string::npos) ? s.substr(0, right + 1) : "";
}

/// @brief Converts the string to all uper-case.
/// @param s the input string.
/// @return the new string.
inline std::string to_upper(std::string s)
{
    for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
        *it = static_cast<char>(toupper(*it));
    }
    return s;
}

/// @brief Converts the string to all lower-case.
/// @param s the input string.
/// @return the new string.
inline std::string to_lower(std::string s)
{
    for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
        *it = static_cast<char>(tolower(*it));
    }
    return s;
}

/// @brief Aligns the string to the right.
/// @param s the input string.
/// @param width the full lenght of the final string.
/// @param fill the char used to fill the tring.
/// @return the aligned string.
inline std::string ralign(std::string s, std::string::size_type width, char fill = ' ')
{
    std::string::size_type pad = (width > s.length()) ? (width - s.length()) : 0;
    return s.insert(0, pad, fill);
}

/// @brief Aligns the string to the left.
/// @param s the input string.
/// @param width the full lenght of the final string.
/// @param fill the char used to fill the tring.
/// @return the aligned string.
inline std::string lalign(std::string s, std::string::size_type width, char fill = ' ')
{
    std::string::size_type pad = (width > s.length()) ? (width - s.length()) : 0;
    return s.append(pad, fill);
}

/// @brief Center aligns the string.
/// @param s the input string.
/// @param width the full lenght of the final string.
/// @param fill the char used to fill the tring.
/// @return the aligned string.
inline std::string calign(std::string s, std::string::size_type width, char fill = ' ')
{
    std::string::size_type len   = s.length();
    std::string::size_type pad   = (width > len) ? (width - len) / 2 : 0;
    std::string::size_type extra = (width > len) ? (width - len) % 2 : 0;
    return s.insert(0, pad, fill).append(pad + extra, fill);
}

/// @brief Replaces all occurences of the given substring.
/// @param s the input string.
/// @param substring the substring that should be replaced.
/// @param substitute the substitute.
/// @param occurences how many occurences should we replace (0 = all of them).
/// @return a reference to the modified string.
inline std::string replace(std::string s, const std::string &substring, const std::string &substitute, unsigned occurences = 0)
{
    // Find the first occurence.
    std::string::size_type pos = s.find(substring);
    // Iterate until the end of the string.
    while (pos != std::string::npos) {
        // Replace the occurence.
        s.replace(pos, substring.size(), substitute);
        // Check how many of them we still need to replace.
        if ((occurences > 0) && ((--occurences) == 0)) {
            break;
        }
        // Advance to the next occurence.
        pos = s.find(substring, pos + substitute.size());
    }
    return s;
}

/// @brief Replaces all occurences of the given substring.
/// @param s the input string.
/// @param substring the substring that should be replaced.
/// @param substitute the substitute.
/// @param occurences how many occurences should we replace (0 = all of them).
/// @return a reference to the modified string.
inline std::string &replace_inplace(std::string &s, const std::string &substring, const std::string &substitute, unsigned occurences)
{
    // Find the first occurence.
    std::string::size_type pos = s.find(substring);
    // Iterate until the end of the string.
    while (pos != std::string::npos) {
        // Replace the occurence.
        s.replace(pos, substring.size(), substitute);
        // Check how many of them we still need to replace.
        if ((occurences > 0) && ((--occurences) == 0)) {
            break;
        }
        // Advance to the next occurence.
        pos = s.find(substring, pos + substitute.size());
    }
    return s;
}

/// @brief Strips the given character from the string.
/// @param s the input string.
/// @param c the character to remove.
/// @return the modified string.
inline std::string strip(std::string s, char c)
{
    s.erase(std::remove(s.begin(), s.end(), c), s.end());
    return s;
}

/// @brief Strips the given character from the string.
/// @param s the input string.
/// @param c the character to remove.
/// @return a reference to the modified string.
inline std::string &strip_inplace(std::string &s, char c)
{
    s.erase(std::remove(s.begin(), s.end(), c), s.end());
    return s;
}

/// @brief Transforms a single-line string a paragraph formatted string.
/// @param s the input string.
/// @param width the width of the paragraphs.
/// @param whitespace the filler character.
/// @return the string splitted into paragraphs.
inline std::string split_paragraph(std::string s, std::string::size_type width, std::string whitespace = " \t\r")
{
    std::string::size_type index = width - 1, index_nl = width - 1, to_trim;

    while (index < s.length()) {
        index = s.find_last_of(whitespace, index + 1);
        if (index == std::string::npos) {
            break;
        }
        index = s.find_last_not_of(whitespace, index);
        if (index == std::string::npos) {
            break;
        }
        to_trim = s.find_first_not_of(whitespace, index + 1) - index - 1;
        s.replace(index + 1, to_trim, "\n");
        index_nl = s.find_first_of('\n', index + 1 + to_trim);
        if (index_nl < (index + width)) {
            index = index_nl;
        }
        index += (width + 1);
    }
    return s;
}

/// @brief Transforms a paragraph formatted string into a single line.
/// @param s the string to manipulate.
/// @return the single line.
inline std::string merge_paragraph(std::string s)
{
    for (std::string::size_type i = 1, j = 1; i < s.length(); ++i) {
        if (s[i] == ' ') {
            // Remove multiple spaces.
            // Go searching for the last ' ' of a series of ' '.
            for (j = i + 1; (j < s.length()) && (s[j] == ' '); ++j)
                ;
            // Compute the amount of characters to remove.
            std::string::size_type to_remove = (j - i) - 1;
            // Remove the excess spaces.
            s.erase(i, to_remove);
        } else if (s[i] == '\n') {
            // Remove newlines and compress more than two newlines.
            // Go searching for the last '\n' of a series of '\n'.
            for (j = i + 1; (j < s.length()) && (s[j] == '\n'); ++j)
                ;
            // Compute the amount of characters to remove. Take advantage of bool,
            //  because if we have more than 1 '\n' it means that we need to remove
            //  all of them except one.
            std::string::size_type to_remove = (j - i) - (j - i > 1);
            // Remove the excess newlines.
            s.replace(i, to_remove, " ");
            // Move after the eventual Wanted new-line.
            i += (j - i > 1);
        }
    }
    return s;
}

/// @brief Given a string and a delimiter, the string is splitted by using the delimiter.
/// @param s the input string.
/// @param delimiter the delimiter which has to be used.
/// @return the splitted string.
inline std::vector<std::string> split(std::string const &s, std::string const &delimiter)
{
    std::vector<std::string> result;
    std::string::size_type curr = 0, next = 0;
    while ((next = s.find_first_of(delimiter, curr)) != std::string::npos) {
        if (next - curr > 0) {
            result.push_back(s.substr(curr, next - curr));
        }
        curr = next + 1;
    }
    std::string last(s, curr);
    if (!last.empty()) {
        result.push_back(last);
    }
    return result;
}

/// @brief Compitalize the first letter of the string.
/// @param s the input string.
/// @param occurences the number of occurences we need to manipulate (0 = all of them).
/// @return the string with the first letter capitalized.
inline std::string capitalize(std::string s, unsigned occurences = 1)
{
    if (!s.empty() && (occurences != 0)) {
        // Find the first occurence.
        for (std::string::size_type i = 0; i < s.length(); ++i) {
            // Replace the occurence.
            if (((i == 0) && isalpha(s[i])) || ((i > 0) && (s[i - 1] == ' '))) {
                s[i] = static_cast<char>(std::toupper(s[i]));
                // Check how many of them we still need to capitalize.
                if ((occurences > 0) && ((--occurences) == 0)) {
                    break;
                }
            }
        }
    }
    return s;
}

/// @brief Restituisce una stringa con la prima lettera minuscola.
/// @param s La stringa sorgente.
/// @param occurences the number of occurences we need to manipulate (0 = all of them).
/// @return La stringa con la prima lettera minuscola.
inline std::string decapitalize(std::string s, unsigned occurences = 0)
{
    if (!s.empty() && (occurences != 0)) {
        // Find the first occurence.
        for (std::string::size_type i = 0; i < s.length(); ++i) {
            // Replace the occurence.
            if (((i == 0) && isalpha(s[i])) || ((i > 0) && (s[i - 1] == ' '))) {
                s[i] = static_cast<char>(std::tolower(s[i]));
                // Check how many of them we still need to capitalize.
                if ((occurences > 0) && ((--occurences) == 0)) {
                    break;
                }
            }
        }
    }
    return s;
}

} // namespace ustr
