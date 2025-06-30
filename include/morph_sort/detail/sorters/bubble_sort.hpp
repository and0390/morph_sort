#ifndef MORPH_BUBBLE_SORT
#define MORPH_BUBBLE_SORT

#include "../adapters.hpp"
#include "default_sort.hpp"
#include "../utils/identity.hpp"
#include "../sort_interface.hpp"
#include "../utils/resolve_projection.hpp"
#include <iterator>

namespace morph
{
    template<>
	struct sort<morph::adapter::bubble_sort> 
	: detail::sort_interface<morph::adapter::bubble_sort>
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
            bubble_sort_impl(
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
                        Projection projection = {}) const -> void
		{
			(*this)(std::begin(container),std::end(container),
                    std::move(compare),std::move(projection));
		}

    private:
        template<typename ForwardIter,
                 typename Compare,
                 typename Projection>
        constexpr 
        auto bubble_sort_impl(ForwardIter begin, 
                              ForwardIter end, 
                              Compare compare, 
                              Projection projection) const -> void
        {
            if (begin != end)
			{
				while (begin != end)
				{
					ForwardIter first{ begin }, second{ begin };

					for (++second; second != end; ++first, ++second)
					{
						if (compare(projection(*second), projection(*first)))
						{
							std::iter_swap(first, second);
						}
					}
					end = first;
				}
			}
        }
	};
}

#endif //MORPH_BUBBLE_SORT