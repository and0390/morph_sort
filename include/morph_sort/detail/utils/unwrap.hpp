#ifndef MORPH_UNWRAP_ITER
#define MORPH_UNWRAP_ITER

#include <memory>
#include <utility>

namespace traits
{
    template<typename Iterator>
    inline constexpr
    auto unwrap_iter(Iterator iter) noexcept 
        -> decltype(std::addressof(*std::declval<Iterator&>()))
    {
        return std::addressof(*iter);
    }
} // namespace detail

#endif