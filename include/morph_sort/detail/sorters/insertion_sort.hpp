#ifndef MORPH_INSERTION_SORT
#define MORPH_INSERTION_SORT

#include <iterator>
#include <functional>
#include "../utils/resolve_projection.hpp"
#include "../sort_interface.hpp"
#include "default_sort.hpp"

namespace morph
{
    template<>
    struct sort<morph::adapter::insertion_sort> 
    : detail::sort_interface<morph::adapter::insertion_sort>
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
            insertion_sort_impl(
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
        auto insertion_sort_impl(RandomAccessIter begin,
                                 RandomAccessIter end,
                                 Compare compare,
                                 Projection projection) const -> void
        {
            if(begin != end)
            {
                using value_type = 
                    typename std::iterator_traits<RandomAccessIter>::value_type;

                for (RandomAccessIter main{ begin }; main != end; ++main)
                {
                    RandomAccessIter second{ main };

                    value_type temp{ std::move(*main) };

                    for (RandomAccessIter first{ main }; 
                        first != begin && compare(projection(temp), projection(*(--first))); 
                        --second)
                    {
                        *second = std::move(*first);
                    }

                    *second = std::move(temp);
                }
            }
        }
    };
}

#endif //MORPH_INSERTION_SORT