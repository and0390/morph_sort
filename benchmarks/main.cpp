
#include "others.hpp"
#include <morph_sort/morph_sort.hpp>


int main()
{
    double val = primitive_performance_test(morph::make_sort<morph::adapter::bubble_sort>());
    primitive_print_benchnmark(val,"bubble sort");

    val = primitive_performance_test(morph::make_sort<morph::adapter::heap_sort>());
    primitive_print_benchnmark(val, "heap sort");

    val = primitive_performance_test(morph::make_sort<morph::adapter::insertion_sort>());
    primitive_print_benchnmark(val, "insertion sort");

    val = primitive_performance_test(morph::make_sort<morph::adapter::merge_sort>());
    primitive_print_benchnmark(val, "merge sort");

    val = primitive_performance_test(morph::make_sort<morph::adapter::quick_sort>());
    primitive_print_benchnmark(val, "quick sort");

    val = primitive_performance_test(morph::make_sort<morph::adapter::selection_sort>());
    primitive_print_benchnmark(val, "inserton sort");

    return 0;
}