#ifndef MORPH_IDENTITY
#define MORPH_IDENTITY

#include <utility>

namespace morph
{
	struct identity
	{
		template<typename Type>
		constexpr 
		Type&& operator()(Type&& type) const noexcept
		{
			return std::forward<Type>(type);
		}
	};
}

#endif