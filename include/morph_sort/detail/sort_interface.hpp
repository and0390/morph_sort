#ifndef MORPH_SORT_INTERFACE
#define MORPH_SORT_INTERFACE

namespace detail
{
    template<typename Adapter>
    struct sort_interface
    {
        using sort_type = Adapter;
        using is_stable = typename Adapter::is_stable;
        
        sort_interface() = delete;
    };
}

#endif //MOPRH_SORT_INTERFACE