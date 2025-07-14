# Morph Sort

a simple sorting library for C++ 17 and beyond

## Preview
```cpp
#include <vector>
#include <morph_sort/morph_sort.hpp>

int main()
{
    std::vector<int> nums {5,4,3,2,1,0,-1,-2,8};

    auto bubble_sort = morph::make_sort<morph::adapter::bubble_sort>();

    bubble_sort(nums);

    return 0;
}
```
or with projection

```cpp
#include <vector>
#include <morph_sort/morph_sort.hpp>
#include <functional>

struct Person
{
    int age;
    const char* name;
};

int main()
{
    std::vector<Person> people {
        {21,"Henry"}, 
        {22,"Jonathan"},
        {19,"Mila"},
        {18,"Roderick"}
    };

    auto merge_sort = morph::make_sort<morph::adapter::merge_sort>();

    merge_sort(people, std::less<>(), &Person::age);

    return 0;
}
```
