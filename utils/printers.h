#pragma once

#include <iostream>
#include <vector>

template<typename T>
void print_vector(const std::vector<T>& src) {
    std::cout << "[";

    for (T i : src)
        std::cout << i << " ";

    std::cout << "] (" << src.size() << ")" << std::endl;
}
