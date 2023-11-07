
#include "ustr/utility.hpp"
#include "ustr/check.hpp"
#include "ustr/manipulate.hpp"

#include <iostream>

#define RUN_CHECK(input, output)                                                        \
    if ((input) != (output)) {                                                          \
        std::cerr << "FAIL (" #input ") `" << (input) << "` != `" << (output) << "`\n"; \
        return 1;                                                                       \
    }

int main(int, char *[])
{
    RUN_CHECK(ustr::trim("_ _-_abc_-_ _", " _-"), "abc")
    RUN_CHECK(ustr::ltrim("_-_ _abc ", " _-"), "abc ")
    RUN_CHECK(ustr::rtrim(" abc_-_ _", " _-"), " abc")
    RUN_CHECK(ustr::to_upper("hello there!"), "HELLO THERE!")
    RUN_CHECK(ustr::to_lower("HELLO THERE!"), "hello there!")
    RUN_CHECK(ustr::ralign("hello", 10), "     hello")
    RUN_CHECK(ustr::lalign("hello", 10), "hello     ")
    RUN_CHECK(ustr::calign("hello", 10), "  hello   ")
    RUN_CHECK(ustr::replace("Hello there!", "there", "friend", 0), "Hello friend!")
    RUN_CHECK(ustr::split_paragraph("AAAA BBBB CCCC DDDD", 4), "AAAA\nBBBB\nCCCC\nDDDD")
    RUN_CHECK(ustr::merge_paragraph("AAAA\nBBBB\nCCCC\nDDDD"), "AAAA BBBB CCCC DDDD")
    RUN_CHECK(ustr::capitalize("hello there friend!", 2), "Hello There friend!")
    RUN_CHECK(ustr::decapitalize("Hello There Friend!", 2), "hello there Friend!")
    return 0;
}
