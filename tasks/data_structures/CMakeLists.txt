set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/data_structures)

include_directories(${PROJECT_SOURCE_DIR})

set(Solutions
    check_brackets
    process_packages
    stack_with_max
    tree_height
)

foreach(solution IN LISTS Solutions)
    add_executable(${solution} ${solution}.cpp)
    target_link_libraries(${solution} GTest::GTest utils)
endforeach()
