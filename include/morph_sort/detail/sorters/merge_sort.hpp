////////////
//////////// implementation for merge sort morph library
////////////
////////////

#ifndef MORPH_MERGE_SORT
#define MORPH_MERGE_SORT

#include <iterator>
#include <functional>
#include <memory>
#include "../utils/identity.hpp"
#include "../utils/resolve_projection.hpp"
#include "../utils/unwrap.hpp"
#include "../sort_interface.hpp"
#include "default_sort.hpp"
#include "../buffer_delete.hpp"

namespace morph
{
    template<>
    struct sort<morph::adapter::merge_sort> 
    : detail::sort_interface<morph::adapter::merge_sort>
    {
    public:
        template<typename Container,
                 typename Compare = std::less<void>,
                 typename Projection = morph::identity>
        inline constexpr
        auto operator()(Container& container,
                        Compare compare = {},
                        Projection projection = {}) const 
            -> void
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
        using ValType = 
            typename std::iterator_traits<RandomAccessIter>::value_type;
            
        /// Throwing exceptions during merge sort may result in memory leaks
        static_assert(std::is_nothrow_move_constructible_v<ValType>,
            "Move semantics must not throw");

            merge_sort_impl(
                std::move(begin),
                std::move(end),
                std::move(compare),
                detail::fn_projection(std::move(projection))
            );
        }
        
    private:

        template<typename RandomAccessIter,
                 typename Compare,
                 typename Projection>
        constexpr
        auto merge_sort_impl(RandomAccessIter begin,
                             RandomAccessIter end,
                             Compare compare,
                             Projection projection) const 
            -> void
        {
        using DiffType = 
            typename std::iterator_traits<RandomAccessIter>::difference_type;
        using ValType = 
            typename std::iterator_traits<RandomAccessIter>::value_type; 
        using ptrType = 
            typename std::iterator_traits<RandomAccessIter>::pointer;
        using BufferTemp = 
            std::unique_ptr<ValType[], detail::buffer_delete<ValType[]>>;
            /// Unwraps the iterator object to prevent unexpected exceptions during access or dereferencing.
            /// and for optimization
            ptrType const first = traits::unwrap_iter(begin);
            ptrType const  last = traits::unwrap_iter(std::prev(end));

            const DiffType size = end - begin;

            /// Allocates a raw memory buffer with sufficient space to hold the contents of the original array,
            /// calculated as sizeof(valType) multiplied by the number of elements.
            if(size > 1)
            {
                void* const raw_mem = 
                    operator new[](sizeof(ValType) * size);

                BufferTemp temp_buffer (static_cast<ptrType>(raw_mem));

                for(DiffType pGrow = 1; pGrow < size; pGrow *= 2)
                {
                    for(DiffType left = 0; left < size; left += (2 * pGrow))
                    {
                        ptrType mid = 
                            std::min(
                                first + (left + pGrow - 1), 
                                last
                            );
                        ptrType right = 
                            std::min(
                                first + (left + 2 * pGrow - 1),
                                last
                            );
                        merging_move(
                            first + left,
                            mid, right,
                            temp_buffer.get(),
                            compare,
                            projection
                        );
                    }
                }
            }
        }

        template<typename RandomAccessIter,
                 typename Compare,
                 typename Projection>
        constexpr 
        auto merging_move(RandomAccessIter* first,
                          RandomAccessIter* mid,
                          RandomAccessIter* last,
                          RandomAccessIter* buffer,
                          const Compare& compare,
                          const Projection& projection) const noexcept
            -> void
        {
        using RandomPtr = 
            RandomAccessIter*;

            std::uninitialized_move(first, last + 1, buffer);

            RandomPtr const end =
                buffer + (last - first + 1);
            RandomPtr const half_end = 
                buffer + (mid - first + 1);

            RandomPtr pos1 = buffer;
            RandomPtr pos2 = half_end;

            while(pos1 < half_end && pos2 < end)
            {
                if(compare(projection(*pos1), projection(*pos2)) || 
                    projection(*pos1) == projection(*pos2))
                {
                    *first = std::move(*pos1++);
                }
                else
                {
                    *first = std::move(*pos2++);
                }
                first++;
            }

            merging_finalize_move(
                pos1, 
                half_end,
                first
            );
            merging_finalize_move(
                pos2, 
                end, 
                first
            );
        }

        template<typename RandomAccessIter>
        inline
        constexpr 
        auto merging_finalize_move(RandomAccessIter* begin,
                                   RandomAccessIter* end,
                                   RandomAccessIter* dest) const noexcept
            -> void
        {
            while(begin < end)
            {
                *dest++ = std::move(*begin++); 
            }
        }
    };
}

#endif //MORPH_INSERTION_SORT