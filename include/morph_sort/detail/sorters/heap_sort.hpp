#ifndef MORPH_HEAP_SORT
#define MORPH_HEAP_SORT

#include <iterator>
#include <functional>
#include "../algs/heap.hpp"
#include "default_sort.hpp"
#include "../utils/resolve_projection.hpp"
#include "../utils/identity.hpp"

namespace morph
{
    template<>
    struct sort<morph::adapter::heap_sort> 
    : detail::sort_interface<morph::adapter::heap_sort>
    {
    public:
        template<typename Container,
                 typename Compare = std::less<void>,
                 typename Projection = morph::identity>
        inline constexpr
        auto operator()(Container& container,
                        Compare compare = {},
                        Projection projection = {}) const -> void
        {
            (*this)(std::begin(container),std::end(container),
                    std::move(compare),std::move(projection));
        }

        template<typename RandomAccessIter,
                 typename Compare = std::less<void>,
                 typename Projection = morph::identity>
        inline constexpr
        auto operator()(RandomAccessIter begin,
                        RandomAccessIter end,
                        Compare compare = {},
                        Projection projection = {}) const 
            -> void
        {
            if(begin != end)
            {
        using ValType =
            typename std::iterator_traits<RandomAccessIter>::value_type;

                ValType* const PtrBegin = traits::unwrap_iter(begin);
                ValType* const PtrEnd = traits::unwrap_iter(end);

                if(PtrEnd - PtrBegin > 1)
                {
                    heap_sort_impl(
                        PtrBegin,
                        PtrEnd,         
                        std::move(compare),
                        detail::fn_projection(std::move(projection))
                    );
                }
            }
        }
    private:
        template<typename RandomAccessIter,
                 typename Compare,
                 typename Projection>
        inline constexpr 
        auto heap_sort_impl(RandomAccessIter* begin,
                            RandomAccessIter* end, 
                            Compare compare,
                            Projection projection) const
            -> void
        {   
            RandomAccessIter* const pBegin = begin + 1;

            make_heap.make_heap_impl(
                begin, 
                end, 
                compare, 
                projection
            );

            for (;pBegin != end; --end)
            {
                pop_heap.pop_heap_impl(
                    begin, 
                    end, 
                    compare, 
                    projection
                );
            }
        }
    };
}




#endif //MORPH_HEAP_SORT