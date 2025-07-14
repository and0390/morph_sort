#ifndef OTHERS
#define OTHERS

#include <chrono>
#include <vector>
#include <random>
#include <functional>
#include <iostream>
#include <algorithm>
#include <string_view>

template<typename T>
void primitive_print_benchnmark(T val, std::string_view sort_type)
{
    std::cout << "Benchmark for : " << sort_type << '\n';
    std::cout << "Val type : Primitive (int)\n";
    std::cout << "Value : " << val << "ms\n\n";
}

template<typename Func,
         typename Ret = double,
         typename Period = std::milli>
Ret primitive_performance_test(Func func)
{
    //primitive type
    std::vector<int> nums(1000);
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<> dist(1,1000000);
    std::generate(nums.begin(), nums.end(), [&dist,&gen]() { return dist(gen); });

    using namespace std::chrono;
    auto begin = high_resolution_clock::now();

    func(nums, std::less<>());

    auto end = high_resolution_clock::now();

    return duration<Ret,Period>(end - begin).count();
}


#endif //OTHERS