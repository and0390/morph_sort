add_executable(test_debug bubble_sort.cpp)

target_include_directories(test_debug PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)