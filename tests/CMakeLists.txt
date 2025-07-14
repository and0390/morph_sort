add_library(morph_sort INTERFACE)
target_include_directories(morph_sort INTERFACE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/morph_sort/detail
)
add_executable(test_debug main.cpp)
target_link_libraries(test_debug PRIVATE morph_sort)


