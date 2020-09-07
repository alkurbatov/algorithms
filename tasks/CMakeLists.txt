include_directories(${PROJECT_SOURCE_DIR})

add_executable(max_pairwise_product max_pairwise_product.cpp)
target_link_libraries(max_pairwise_product utils)

add_executable(fibonacci_number fibonacci_number.cpp)
target_link_libraries(fibonacci_number gtest utils)
