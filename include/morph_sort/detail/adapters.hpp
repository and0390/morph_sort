#ifndef MORPH_ADAPTERS
#define MORPH_ADAPTERS

#include <type_traits>

namespace morph
{
    namespace adapter
    {
        struct bubble_sort { using is_stable = std::true_type; };
        struct insertion_sort { using is_stable = std::true_type; };
        struct merge_sort { using is_stable = std::true_type; };
        struct quick_sort { using is_stable = std::false_type; };
        struct selection_sort { using is_stable = std::false_type; };
        struct heap_sort { using is_stable = std::false_type; };
    }
}

#endif