# morph_sort

a simple sorting library for C++

##preview
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
