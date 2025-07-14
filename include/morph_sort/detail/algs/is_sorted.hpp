#ifndef MORPH_IS_SORTED
#define MORPH_IS_SORTED

#include <functional>
#include "../utils/identity.hpp"
#include "../utils/resolve_projection.hpp"

namespace morph
{
    namespace detail
    {
        template<typename ForwardIter,
                 typename Compare,
                 typename Projection>
        constexpr
        auto is_sorted_impl(ForwardIter begin, 
                    ForwardIter end,
                    Compare compare, 
                    Projection projection)
            -> bool
        {
            for(auto pBegin = begin++; begin != end; ++pBegin, ++begin)
            {
                if(!compare(projection(*pBegin), projection(*begin)))
                    return false;
            }
            return true;
        }
    }

    template<typename ForwardIter,
             typename Compare = std::less<void>,
             typename Projection = morph::identity>
    inline constexpr
    auto is_sorted(ForwardIter begin,
                   ForwardIter end,
                   Compare compare = {},
                   Projection projection = {})
        -> bool
    {
        return detail::is_sorted_impl(
            std::move(begin),
            std::move(end),
            std::move(compare),
            ::detail::fn_projection(std::move(projection))
        );
    }

    template<typename Container,
             typename Compare = std::less<void>,
             typename Projection = morph::identity>
    inline constexpr
    auto is_sorted(Container& container,
                   Compare compare = {},
                   Projection projection = {})
        -> bool
    {
        return detail::is_sorted_impl(
            std::begin(container),
            std::end(container),
            std::move(compare),
            ::detail::fn_projection(std::move(projection))
        );
    }
}


#endif //MORPH_IS_SORTED