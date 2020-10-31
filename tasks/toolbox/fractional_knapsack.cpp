#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
// first is value, second is weight.
typedef std::pair<unsigned, unsigned> food_t;

// first is value per fraction, second is available weight.
typedef std::pair<double, unsigned> food_fraction_t;

bool sortrev(const food_fraction_t& a, const food_fraction_t& b) { 
  return a.first > b.first; 
}

double get_optimal_value(size_t capacity, const std::vector<food_t>& items) {
    double value = 0.0;

    std::vector<food_fraction_t> fractions;
    for (auto food : items) {
        fractions.push_back(
            std::make_pair(static_cast<double>(food.first) / food.second, food.second));
    }

    std::sort(fractions.begin(), fractions.end(), sortrev);

    for (auto i : fractions) {
        if (capacity > i.second) {
            value += i.first * i.second;
            capacity -= i.second;
            continue;
        }

        value += capacity * i.first;
        break;
    }

    return static_cast<long>(value * 10000) / 10000.0;
}

#ifdef DEBUG
void test_solution() {
    std::vector<food_t> items1;
    items1.push_back(std::make_pair(60, 20));
    items1.push_back(std::make_pair(100, 50));
    items1.push_back(std::make_pair(120, 30));

    Timer timer;
    ASSERT_EQ(get_optimal_value(50, items1), 180.0000);
    EXPECT_LE(timer.elapsed(), 1000);

    std::vector<food_t> items2;
    items2.push_back(std::make_pair(500, 30));

    timer.restart();
    ASSERT_EQ(get_optimal_value(10, items2), 166.6666);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
      size_t n, capacity;
      std::cin >> n >> capacity;

      std::vector<food_t> items;
      for (size_t i = 0; i < n; i++) {
        unsigned value, weight;
        std::cin >> value >> weight;
        items.push_back(std::make_pair(value, weight));
      }

      double optimal_value = get_optimal_value(capacity, items);

      std::cout.precision(10);
      std::cout << optimal_value << std::endl;
      return 0;
    }

#ifdef DEBUG
    if (std::string(argv[1]) == "test") {
        test_solution();
        return 0;
    }
#endif

    return 1;
}
