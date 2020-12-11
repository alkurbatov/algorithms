set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/graphs)

set(Solutions
    acyclicity
    bfs
    bipartite
    connected_components
    dijkstra
    reachability
    strongly_connected
    toposort
)

foreach(solution IN LISTS Solutions)
    add_executable(${solution} ${solution}.cpp)
    target_link_libraries(${solution} GTest::GTest utils)
endforeach()
