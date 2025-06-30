
#ifndef MORPH_RESOLVE_PROJECTION
#define MORPH_RESOLVE_PROJECTION

#include <functional>
#include <type_traits>

namespace detail
{
	struct function_projection_type
	{
		template<typename In>
		inline constexpr
		auto operator()(In in) const 
		noexcept(
			noexcept(std::mem_fn(in))
		)
			-> std::enable_if_t<
					std::is_member_pointer<In>::value,
					decltype(std::mem_fn(std::declval<In>()))
			>
		{
			return std::mem_fn(in);
		}
		
		template<typename In>
		inline constexpr
		auto operator()(In&& in) const 
		noexcept
			-> std::enable_if_t<
				!std::is_member_pointer<std::remove_reference_t<In>>::value,
				In&&
			>
		{
			return std::forward<In>(in);
		}
	};

	inline constexpr function_projection_type fn_projection;
}

#endif //MORPHIM_FUNCTIONAL