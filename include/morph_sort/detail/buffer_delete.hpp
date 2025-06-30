#ifndef MORPH_BUFFER_DELETE
#define MORPH_BUFFER_DELETE

namespace detail
{
    template<typename T>
    struct buffer_delete;

    template<typename T>
    struct buffer_delete<T[]>
    {
        buffer_delete() = default;

        void operator()(T* ptr)
        {
            operator delete[](ptr);
        }
    };
}

#endif