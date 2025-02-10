
#include "ustr/check.hpp"
#include "ustr/manipulate.hpp"
#include "ustr/utility.hpp"

#include <iostream>

#define RUN_CHECK(guard)                                                                                               \
    if (!(guard)) {                                                                                                    \
        std::cerr << "Fails : " #guard "\n";                                                                           \
        return 1;                                                                                                      \
    }

int main(int, char *[])
{
    RUN_CHECK(ustr::begin_with("Hello there!", "Hello", true, 0))
    RUN_CHECK(ustr::begin_with("Hello there!", "hello", false, 0))
    RUN_CHECK(ustr::begin_with("Hello there!", "HelAA", true, 3))
    RUN_CHECK(ustr::begin_with("Hello there!", "helAA", false, 3))
    RUN_CHECK(ustr::end_with("Hello there!", "there!", true, 0))
    RUN_CHECK(ustr::end_with("Hello there!", "TherE!", false, 0))
    RUN_CHECK(ustr::end_with("Hello there!", "AAAre!", true, 3))
    RUN_CHECK(ustr::end_with("Hello there!", "AAArE!", false, 3))
    RUN_CHECK(ustr::compare("Hello there!", "Hello there!", true, 0))
    RUN_CHECK(ustr::compare("Hello there!", "HELLO THERE!", false, 0))
    RUN_CHECK(ustr::compare("Hello there!", "Hello AAAAA!", true, 4))
    RUN_CHECK(ustr::compare("Hello there!", "HELLO AAAAA!", false, 4))
    RUN_CHECK(ustr::count("Cat, Dog, Cat, Cat", "Cat", false) != 3)
    RUN_CHECK(ustr::count("Cat, Dog, Cat, Cat", "DOG", false) != 0)
    RUN_CHECK(ustr::count("Cat, Dog, cat, Cat", "Cat", true) != 2)
    RUN_CHECK(ustr::count("Cat, Dog, DOG, Cat", "DOG", true) != 1)
    RUN_CHECK(ustr::is_abbreviation_of("mag", "magic", true, 3) == true)
    RUN_CHECK(ustr::is_abbreviation_of("mag", "magic", true, 3) == true)
    RUN_CHECK(ustr::is_abbreviation_of("magi", "magic", true, 3) == true)
    RUN_CHECK(ustr::is_abbreviation_of("ma", "magic", true, 3) == false)
    RUN_CHECK(ustr::is_abbreviation_of("MAG", "magic", true, 3) == false)
    RUN_CHECK(ustr::is_abbreviation_of("MAG", "magic", false, 3) == true)
    RUN_CHECK(ustr::compare("str", "stat") == false)
    return 0;
}
