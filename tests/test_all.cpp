/// @file test_all.cpp
/// @author Enrico Fraccaroli (enry.frak@gmail.com)
/// @brief Tests all functions.
/// @copyright
/// Copyright (c) 2024-2025. All rights reserved.
/// Licensed under the MIT License. See LICENSE file in the project root for details.

#include "ustr/check.hpp"
#include "ustr/manipulate.hpp"
#include "ustr/utility.hpp"

#include <iostream>
#include <vector>

#define RUN_CHECK(input, output)                                                                                       \
    if ((input) != (output)) {                                                                                         \
        std::cerr << "FAIL (" #input ") `" << (input) << "` != `" << (output) << "`\n";                                \
        return 1;                                                                                                      \
    }

int main(int, char *[])
{
    // Testing string checking functions
    // Testing `begin_with` function
    RUN_CHECK(ustr::begin_with("Hello world!", "Hello", true, 0), true);
    RUN_CHECK(ustr::begin_with("Hello world!", "hello", false, 0), true);
    RUN_CHECK(ustr::begin_with("Hello world!", "Hello", true, 3), true);

    // Testing `end_with` function
    RUN_CHECK(ustr::end_with("Hello world!", "world!", true, 0), true);
    RUN_CHECK(ustr::end_with("Hello world!", "World!", false, 0), true);

    // Testing `compare` function
    RUN_CHECK(ustr::compare("Hello", "hello", false, 0), true);
    RUN_CHECK(ustr::compare("Hello", "HELLO", true, 0), false);

    // Testing `count` function
    RUN_CHECK(ustr::count("apple orange apple apple", "apple", false), 3);
    RUN_CHECK(ustr::count("apple orange apple apple", "DOG", false), 0);
    RUN_CHECK(ustr::count("apple orange apple apple", "apple", true), 3);
    RUN_CHECK(ustr::count("apple orange apple apple", "Apple", true), 0);

    // Testing `is_abbreviation_of` function
    RUN_CHECK(ustr::is_abbreviation_of("str", "string", false, 3), true);
    RUN_CHECK(ustr::is_abbreviation_of("abc", "abcd", false, 2), true);

    // Additional edge case tests for `compare` and `count`
    RUN_CHECK(ustr::compare("cat", "catalog", false, 3), true);           // Should match 'cat' within 'catalog'
    RUN_CHECK(ustr::count("apple orange apple apple", "apple", true), 3); // Case insensitive count
    RUN_CHECK(ustr::count("apple orange apple apple", "Apple", true), 0); // Case sensitive count

    // Testing string manipulation functions
    // Testing `trim`, `ltrim`, and `rtrim`
    RUN_CHECK(ustr::trim("_ _-_abc_-_ _", " _-"), "abc");
    RUN_CHECK(ustr::ltrim("_-_ _abc ", " _-"), "abc ");
    RUN_CHECK(ustr::rtrim(" abc_-_ _", " _-"), " abc");

    // Testing `to_upper` and `to_lower`
    RUN_CHECK(ustr::to_upper("hello there!"), "HELLO THERE!");
    RUN_CHECK(ustr::to_lower("HELLO THERE!"), "hello there!");

    // Testing `ralign`, `lalign`, `calign`
    RUN_CHECK(ustr::ralign("hello", 10), "     hello");
    RUN_CHECK(ustr::lalign("hello", 10), "hello     ");
    RUN_CHECK(ustr::calign("hello", 10), "  hello   ");

    // Testing `replace` and `replace_inplace`
    RUN_CHECK(ustr::replace("Hello there!", "there", "friend", 0), "Hello friend!");
    {
        std::string str("Hello world!");
        RUN_CHECK(ustr::replace_inplace(str, "world", "friend", 0), "Hello friend!");
    }

    // Testing `split_paragraph` and `merge_paragraph`
    RUN_CHECK(ustr::split_paragraph("AAAA BBBB CCCC DDDD", 4), "AAAA\nBBBB\nCCCC\nDDDD");
    RUN_CHECK(ustr::merge_paragraph("AAAA\nBBBB\nCCCC\nDDDD"), "AAAA BBBB CCCC DDDD");

    // Testing capitalization and decapitalization
    RUN_CHECK(ustr::capitalize("hello there friend!", 2), "Hello There friend!");
    RUN_CHECK(ustr::decapitalize("Hello There Friend!", 2), "hello there Friend!");

    // Testing utility functions
    // Testing `to_human_size`
    RUN_CHECK(ustr::to_human_size(1024), "1.00 KB");

    // Testing `decimal_to_binary_string`
    RUN_CHECK(ustr::decimal_to_binary_string(5, 8), "00000101");

    // Testing `get_ordinal`
    RUN_CHECK(ustr::get_ordinal(1), "1st");
    RUN_CHECK(ustr::get_ordinal(2), "2nd");
    RUN_CHECK(ustr::get_ordinal(3), "3rd");
    RUN_CHECK(ustr::get_ordinal(4), "4th");

    // Edge case tests for `get_ordinal`
    RUN_CHECK(ustr::get_ordinal(11), "11th");
    RUN_CHECK(ustr::get_ordinal(12), "12th");
    RUN_CHECK(ustr::get_ordinal(13), "13th");

    // Tests for special cases
    RUN_CHECK(ustr::trim("123  ", " "), "123");
    RUN_CHECK(ustr::trim("  123", " "), "123");

    return 0;
}
