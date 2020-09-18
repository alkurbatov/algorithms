include_directories(${PROJECT_SOURCE_DIR})

set(Solutions
	car_fueling
	change
	dot_product
	fibonacci_huge
	fibonacci_last_digit
	fibonacci_number
	fibonacci_sum_last_digit
	fractional_knapsack
	greatest_common_divisor
	least_common_multiple
	max_pairwise_product
)

foreach(solution IN LISTS Solutions)
	add_executable(${solution} ${solution}.cpp)
	target_link_libraries(${solution} gtest utils)
endforeach()
