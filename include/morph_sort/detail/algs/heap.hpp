

#ifndef MORPH_HEAP
#define MORPH_HEAP

#include <functional>
#include "../utils/unwrap.hpp"

namespace morph
{
    struct heap_fn
    {
    private:
        template<class RandomAccessIter, 
                 class DifferentType, 
                 class T, 
                 class Compare,
                 class Projection>
        constexpr 
        auto sift_up(RandomAccessIter* begin, 
                     DifferentType max_parent_pos, 
                     DifferentType pos, 
                     T& temp, 
                     const Compare& compare,
                     const Projection& projection) const
            -> void
        {
            for (DifferentType parent_pos{ (pos - 1) / 2 }; 
                 pos > max_parent_pos && compare(projection(*(begin + parent_pos)), projection(temp)); 
                 parent_pos = (pos - 1) / 2)
            {
                *(begin + pos) = 
                    std::move(*(begin + parent_pos));

                pos = parent_pos;
            }

            *(begin + pos) = std::move(temp);
        }

        template<class RandomAccessIter, 
                 class DifferentType, 
                 class T, 
                 class Compare,
                 class Projection>
        constexpr 
        auto sift_down(RandomAccessIter* begin,
                       DifferentType parent_pos, 
                       DifferentType pos, 
                       DifferentType size, 
                       T& temp, 
                       const Compare& compare,
                       const Projection& projection) const
            -> void
        {
            
            DifferentType child_pos{ 2 * pos + 2 };
            for (; child_pos < size; child_pos = 2 * child_pos + 2)
            {
                if (compare(projection(*(begin + child_pos)), projection(*(begin + (child_pos - 1)))))
                {
                    --child_pos;
                }

                *(begin + pos) = 
                    std::move(*(begin + child_pos));

                pos = child_pos;
            }

            if (child_pos == size)
            {
                *(begin + pos) = 
                    std::move(*(begin + child_pos - 1));

                pos = child_pos - 1;
            }

            sift_up(
                begin, 
                parent_pos, 
                pos, 
                temp, 
                compare, 
                projection
            );
        }

        template<class RandomAccessIter,
                 class Compare,
                 class Projection>
        constexpr 
        auto make_heap_impl(RandomAccessIter* begin, 
                            RandomAccessIter* end, 
                            const Compare& compare,
                            const Projection& projection) const
            -> void
        {
        using ValType = 
            typename std::iterator_traits<RandomAccessIter*>::value_type;
        using DiffType = 
            typename std::iterator_traits<RandomAccessIter*>::difference_type;

            const DiffType size{ end - begin };

            if (size >= 2)
            {
                for(DiffType parent_pos = (size - 2) / 2; parent_pos >= 0; --parent_pos)
                {
                    ValType temp = std::move(*(begin + parent_pos));

                    sift_down(
                        begin,
                        parent_pos,
                        parent_pos,
                        size, temp,
                        compare,
                        projection
                    );
                }
            }
        }

        friend class sort<morph::adapter::heap_sort>;
        friend class pop_heap_fn;

    public:
        template<class RandomAccessIter,
                  class Compare = std::less<void>,
                 class Projection = morph::identity>
        constexpr 
        auto make_heap(RandomAccessIter begin,
                       RandomAccessIter end, 
                       Compare compare = {},
                       Projection projection = {}) const
            -> void
        {
        using ValType =
            typename std::iterator_traits<RandomAccessIter>::value_type;
            
            ValType* const beginPtr = traits::unwrap_iter(begin);
            ValType* const endPtr = traits::unwrap_iter(end);

            make_heap_impl(
                beginPtr,
                endPtr,
                std::move(compare),
                detail::fn_projection(std::move(projection))
            );
        }
    };

    inline constexpr heap_fn make_heap;

    struct pop_heap_fn
    {
    private:
        template<class RandomAccessIter,
                 class Compare,
                 class Projection>
        constexpr 
        auto pop_heap_impl(RandomAccessIter* begin, 
                           RandomAccessIter* end,
                           const Compare& compare,
                           const Projection& projection) const
            -> void
        {
            if (begin != end)
            {
        using DiffType = 
            typename std::iterator_traits<RandomAccessIter*>::difference_type;
        using ValType = 
            typename std::iterator_traits<RandomAccessIter*>::value_type;

                ValType temp = std::move(*std::prev(end));
                const DiffType size = end - begin;

                std::iter_swap(std::prev(end), begin);

                make_heap.sift_down(
                    begin,
                    (DiffType)(0),
                    (DiffType)(0), 
                    size - 1,
                    temp, 
                    std::move(compare),
                    std::move(projection)
                );
            }
        }

        friend class sort<morph::adapter::heap_sort>;

    public:
        template<class RandomAccessIter,
                 class Compare = std::less<void>,
                 class Projection = morph::identity>
        constexpr 
        auto pop_heap(RandomAccessIter begin,
                    RandomAccessIter end,
                    Compare compare = {},
                    Projection projection = {}) const
            -> void
        {
        using ValType =
            typename std::iterator_traits<RandomAccessIter>::value_type;

            ValType* const PtrBegin = traits::unwrap_iter(begin);
            ValType* const PtrEnd = traits::unwrap_iter(end);

            pop_heap_impl(
                PtrBegin, 
                PtrEnd, 
                std::move(compare), 
                std::move(projection)
            );
        }
    };

    inline constexpr pop_heap_fn pop_heap;
}

#endif //MORPH_HEAP