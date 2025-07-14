#ifndef SORT_CHECK_HPP
#define SORT_CHECK_HPP

#include <morph_sort/morph_sort.hpp>
#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <cassert>
#include "aggregrate/person.hpp"
#include <algs/is_sorted.hpp>
#include <iomanip>
#include <string_view>


template<typename Adapter>
void sort_check(std::string_view sv)
{
    std::vector<int> nums(1000);

    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<> dist(1,1000000);

    std::generate(nums.begin(), nums.end(), [&dist,&gen]() { return dist(gen); });

    auto sort_func = 
        morph::make_sort<Adapter>();

    sort_func(nums, std::less<>());

    bool is_sorted = std::is_sorted(nums.cbegin(),nums.cend());

    if(!is_sorted)
    {
        std::cerr << "nums is not sorted properly with " << sv;
        std::abort();
    }

    nums.clear();
    nums.shrink_to_fit();

    std::vector<Person> people {
        {"Person1", 20},
        {"Person2", 21},
        {"Person3", 22},
        {"Person4", 23},
        {"Person5", 24},
        {"Person6", 25},
        {"Person7", 26},
        {"Person8", 27},
        {"Person9", 28},
        {"Person10", 29},
        {"Person11", 30},
        {"Person12", 31},
        {"Person13", 32},
        {"Person14", 33},
        {"Person15", 34},
        {"Person16", 35},
        {"Person17", 36},
        {"Person18", 37},
        {"Person19", 38},
        {"Person20", 39},
        {"Person21", 40},
        {"Person22", 41},
        {"Person23", 42},
        {"Person24", 43},
        {"Person25", 44},
        {"Person26", 45},
        {"Person27", 46},
        {"Person28", 47},
        {"Person29", 48},
        {"Person30", 49},
        {"Person31", 50},
        {"Person32", 20},
        {"Person33", 21},
        {"Person34", 22},
        {"Person35", 23},
        {"Person36", 24},
        {"Person37", 25},
        {"Person38", 26},
        {"Person39", 27},
        {"Person40", 28},
        {"Person41", 29},
        {"Person42", 30},
        {"Person43", 31},
        {"Person44", 32},
        {"Person45", 33},
        {"Person46", 34},
        {"Person47", 35},
        {"Person48", 36},
        {"Person49", 37},
        {"Person50", 38},
        {"Person51", 39},
        {"Person52", 40},
        {"Person53", 41},
        {"Person54", 42},
        {"Person55", 43},
        {"Person56", 44},
        {"Person57", 45},
        {"Person58", 46},
        {"Person59", 47},
        {"Person60", 48},
        {"Person61", 49},
        {"Person62", 50},
        {"Person63", 20},
        {"Person64", 21},
        {"Person65", 22},
        {"Person66", 23},
        {"Person67", 24},
        {"Person68", 25},
        {"Person69", 26},
        {"Person70", 27},
        {"Person71", 28},
        {"Person72", 29},
        {"Person73", 30},
        {"Person74", 31},
        {"Person75", 32},
        {"Person76", 33},
        {"Person77", 34},
        {"Person78", 35},
        {"Person79", 36},
        {"Person80", 37},
        {"Person81", 38},
        {"Person82", 39},
        {"Person83", 40},
        {"Person84", 41},
        {"Person85", 42},
        {"Person86", 43},
        {"Person87", 44},
        {"Person88", 45},
        {"Person89", 46},
        {"Person90", 47},
        {"Person91", 48},
        {"Person92", 49},
        {"Person93", 50},
        {"Person94", 22},
        {"Person95", 23},
        {"Person96", 24},
        {"Person97", 25},
        {"Person98", 26},
        {"Person99", 27},
        {"Person100", 28},
    };

    sort_func(people, std::less<>(), &Person::age);
    is_sorted = morph::is_sorted(people, std::less_equal<>(), &Person::age);

    if(!is_sorted)
    {
        std::cerr << "object person is not sorted properly with " << sv;
        std::abort();
    }
}

#endif