add_library(utils generators.h generators.cpp timer.h timer.cpp)
target_link_libraries(utils boost_random-mt)
