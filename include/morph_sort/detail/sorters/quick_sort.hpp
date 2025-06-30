#ifndef MORPH_QUICK_SORT
#define MORPH_QUICK_SORT

#include <iterator>
#include <functional>
#include "../utils/resolve_projection.hpp"
#include "../adapters.hpp"
#include "../utils/identity.hpp"
#include "default_sort.hpp"
#include "../sort_interface.hpp"


namespace morph
{
    template<>
    struct sort<morph::adapter::quick_sort> 
    : detail::sort_interface<morph::adapter::quick_sort>
    {
    public:
        template<typename ForwardIter, 
                 typename Compare = std::less<void>,
                 typename Projection = morph::identity>
        constexpr inline 
        auto operator()(ForwardIter begin, 
                        ForwardIter end, 
                        Compare compare = {}, 
                        Projection projection = {}) const 
            -> void
        {
            if(begin != end)
            {
                quick_sort_impl_rec(
                    begin,
                    std::prev(end),
                    compare,
                    detail::fn_projection(projection)
                );
            }
        }

        template<typename Container, 
                 typename Compare = std::less<void>,
                 typename Projection = morph::identity>
        constexpr inline 
        auto operator()(Container& container,
                        Compare compare = {},
                        Projection projection = {}) const 
            -> void
        {
            (*this)(std::begin(container),std::end(container),
                    std::move(compare),std::move(projection));
        }
        
    private:
        template<typename ForwardIter,
                 typename Compare,
                 typename Projection>
        constexpr
        auto quick_sort_impl_rec(ForwardIter first,
                                 ForwardIter last,
                                 const Compare& compare,
                                 const Projection& projection) const
            -> void
        {
            if(first < last)
            {
                const ForwardIter bound = 
                    partition_impl(
                        first,
                        last, 
                        compare, 
                        projection
                    );

                quick_sort_impl_rec(
                    first, 
                    std::prev(bound), 
                    compare, 
                    projection
                );

                quick_sort_impl_rec(
                    std::next(bound),
                    last,
                    compare,
                    projection    
                );
            }
        }

        template<typename ForwardIter, 
                typename Compare,
                typename Projection>
        constexpr 
        auto partition_impl(ForwardIter first,
                            ForwardIter last, 
                            const Compare& compare, 
                            const Projection& projection) const
            -> ForwardIter
        {
            ForwardIter pos = first;

            for (; first != last; ++first)
            {
                if (compare(projection(*first), projection(*last)))
                {
                    std::iter_swap(first, pos);
                    ++pos;
                }
            }

            std::iter_swap(pos, last);

            return pos;
        }
        
        
    };

}










#endif //MORPH_QUICK_SORT