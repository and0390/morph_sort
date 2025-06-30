#ifndef MORPH_SELECTION_SORT
#define MORPH_SELECTION_SORT

#include "../utils/resolve_projection.hpp"
#include "../adapters.hpp"
#include "default_sort.hpp"
#include "../sort_interface.hpp"
#include <iterator>


namespace morph
{
    template<>
    struct sort<morph::adapter::selection_sort> 
    : detail::sort_interface<morph::adapter::selection_sort>
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
            selection_sort_impl(
                std::move(begin),
                std::move(end),
                std::move(compare),
                detail::fn_projection(std::move(projection))
            );
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
        auto selection_sort_impl(ForwardIter begin, 
                                 ForwardIter end, 
                                 Compare compare,
                                 Projection projection) const
            -> void
		{
            if(begin != end)
            {
                for (; begin != end; ++begin)
                {
                    ForwardIter pos = begin;
                    ForwardIter most = begin;

                    for (++pos; pos != end; ++pos)
                    {
                        if (compare(projection(*pos), projection(*most)))
                        {
                            most = pos;
                        }
                    }

                    std::iter_swap(begin, most);
                }
            }
		}
    };
}


#endif //MORPH_SELECTION_SORT