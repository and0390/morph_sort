#include "sort_check.hpp"

int main()
{
    //all passes without assertion error = everything's fine
    sort_check<morph::adapter::bubble_sort>("bubble sort");
    sort_check<morph::adapter::heap_sort>("heap sort");
    sort_check<morph::adapter::insertion_sort>("insertion sort");
    sort_check<morph::adapter::merge_sort>("merge sort");
    sort_check<morph::adapter::quick_sort>("quick sort");
    sort_check<morph::adapter::selection_sort>("selection sort");

    return 0;
}