#include <algorithm>
#include <iostream>
#include <vector>

#ifdef DEBUG
#include "utils/generators.h"
#endif

namespace {
long long MaxPairwiseProduct(const std::vector<int>& numbers) {
    long long max1 = 0;
    long long max2 = 0;

    for (auto i : numbers) {
        if (i <= max1 && i <= max2) continue;

        if (max1 > max2) {
            max2 = i;
            continue;
        }

        if (max2 > max1) {
            max1 = i;
            continue;
        }

        if (max1 == max2) {
            max1 = i;
            continue;
        }
    }

    return max1 * max2;
}
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        size_t n;
        std::cin >> n;

        std::vector<int> numbers(n);
        for (unsigned i = 0; i < n; ++i)
            std::cin >> numbers[i];

        std::cout << MaxPairwiseProduct(numbers) << std::endl;
        return 0;
    }

#ifdef DEBUG
    if (std::string(argv[1]) == "test") {
        for (int i = 0; i < 10; ++i) {
            std::vector<int> numbers = generateRandomSequence(10);

            std::cout << "[ ";
            for (const auto& i: numbers)
              std::cout << i << " ";
            std::cout << "]" << std::endl;

            std::cout << MaxPairwiseProduct(numbers) << std::endl;
        }

        return 0;
    }
#endif

    return 1;
}
