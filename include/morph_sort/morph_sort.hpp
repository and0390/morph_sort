#ifndef MORPH_SORT_MAIN
#define MORPH_SORT_MAIN

#include "detail/sort.hpp"
#include "detail/adapters.hpp"

namespace morph
{
   template<typename Adapter>
   inline constexpr
   auto make_sort() noexcept 
      -> morph::sort<Adapter>
   {
        return morph::sort<Adapter>{};
   }
}


#endif //MORPH_SORT_MAIN