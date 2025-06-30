#include <morph_sort/morph_sort.hpp>
#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>

int main()
{
    std::vector<int> nums(10000);

    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<> dist(1,1000000);

    std::generate(nums.begin(), nums.end(), [&]() { return dist(gen); });

    auto bubble_sort = 
        morph::make_sort<morph::adapter::bubble_sort>();

    bubble_sort(nums, std::greater<>());

    std::for_each(nums.cbegin(),nums.cend(),[](int x){
        std::cout << x << ' ';
    });

    return 0;
}