set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/toolbox)

set(Solutions
	binary_search
	car_fueling
	change
	change_dp
	dot_product
	edit_distance
	fibonacci_huge
	fibonacci_last_digit
	fibonacci_number
	fibonacci_sum_last_digit
	fractional_knapsack
	greatest_common_divisor
	knapsack
	least_common_multiple
	lcs2
	majority_element
	max_pairwise_product
	partition3
	primitive_calculator
	sorting
)

foreach(solution IN LISTS Solutions)
	add_executable(${solution} ${solution}.cpp)
	target_link_libraries(${solution} GTest::GTest utils)
endforeach()
