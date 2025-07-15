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
## Features
Morph Sort library supports various basic sorting algorithms

- Bubble sort
- Heap sort
- Insertion sort
- Quick sort
- Merge sort
- Selection sort

predefined member types that might be helpful

<some_sort_fn>::sort_type
```cpp
    auto sort_func = morph::make_sort<morph::adapter::merge_sort>();
    static_assert(std::is_same_v<decltype(sort_func)::sort_type, morph::adapter::merge_sort>);
```
and

<some_sort_fn>::is_stable
```cpp
    auto sort_func = morph::make_sort<morph::adapter::merge_sort>();
    static_assert(decltype(sort_func)::is_stable::value);
```
### Signatures
#### Bubble sort
```cpp
void bubble_sort(ForwardIter begin, ForwardIter end, Compare compare, Projection projection)
void heap_sort_impl(RandomAccessIter begin, RandomAccessIter end, Compare compare, Projection projection)


