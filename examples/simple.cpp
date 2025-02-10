
#include "ustr/check.hpp"
#include "ustr/manipulate.hpp"
#include "ustr/utility.hpp"

#include "colors.hpp"

#include <iostream>

int main(int, char *[])
{
    std::string gr = "Two quantities are in the golden ratio if their ratio is the same as the ratio of their sum to "
                     "the larger of the two quantities.";

    std::cout << "'" << ustr::trim(" Hello world!  ") << "'\n";
    std::cout << "'" << ustr::ltrim(" Hello world!  ") << "'\n";
    std::cout << "'" << ustr::rtrim(" Hello world!  ") << "'\n";
    std::cout << "'" << ustr::lalign("Hello", 8) << "'\n";
    std::cout << "'" << ustr::ralign("Hello", 8) << "'\n";
    std::cout << "'" << ustr::calign("Hello", 8) << "'\n";
    std::cout << "'" << ustr::to_lower("Hello") << "'\n";
    std::cout << "'" << ustr::to_upper("Hello") << "'\n";
    std::cout << "'" << ustr::replace_inplace(gr, "ratio", "RATIO", 1) << "'\n";
    std::cout << "'" << ustr::replace_inplace(gr, "ratio", "RATIO", 0) << "'\n";
    std::cout << "'" << ustr::replace_inplace(gr, "RATIO", "ratio", 0) << "'\n";
    gr = ustr::split_paragraph(gr, 40);
    std::cout << "'''\n" << gr << "\n'''\n";
    gr = ustr::merge_paragraph(gr);
    std::cout << "'" << gr << "'\n";
    std::cout << "'" << ustr::capitalize(" two quantities are in the golden ", 3) << "'\n";
    std::cout << "'" << ustr::capitalize(" two quantities are in the golden ", 0) << "'\n";
    std::cout << "'" << ustr::decapitalize(" Two Quantities Are In The Golden ", 3) << "'\n";
    std::cout << "'" << ustr::decapitalize(" Two Quantities Are In The Golden ", 0) << "'\n";
    return 0;
}
