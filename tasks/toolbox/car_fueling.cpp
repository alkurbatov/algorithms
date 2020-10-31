#include <iostream>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
int compute_min_refills(unsigned dist, unsigned tank, const std::vector<unsigned>& stops) {
    int refills = 0;
    unsigned current_stop = 0;

    std::vector<unsigned> route;
    route.push_back(0);
    route.insert(route.end(), stops.begin(), stops.end());
    route.push_back(dist);

    while (route[current_stop] + tank < dist) {
        for (size_t i = current_stop; i < route.size(); ++i) {
            if (route[current_stop] + tank >= route[i])
                continue;

            if (route[i] - route[i - 1] > tank)
                return -1;

            current_stop = i - 1;
            ++refills;
            break;
        }
    }

    return refills;
}

#ifdef DEBUG
void test_solution() {
    std::vector<unsigned> stops1{ 200, 375, 550, 750 };
    Timer timer;
    ASSERT_EQ(compute_min_refills(950, 400, stops1), 2);
    EXPECT_LE(timer.elapsed(), 1000);

    std::vector<unsigned> stops2{ 1, 2, 5, 9 };
    timer.restart();
    ASSERT_EQ(compute_min_refills(10, 3, stops2), -1);
    EXPECT_LE(timer.elapsed(), 1000);

    std::vector<unsigned> stops3{ 100, 150 };
    timer.restart();
    ASSERT_EQ(compute_min_refills(200, 250, stops3), 0);
    EXPECT_LE(timer.elapsed(), 1000);

    std::vector<unsigned> stops4{ 100, 200, 300, 400 };
    timer.restart();
    ASSERT_EQ(compute_min_refills(700, 200, stops4), -1);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        unsigned d = 0;
        std::cin >> d;
        unsigned m = 0;
        std::cin >> m;
        size_t n = 0;
        std::cin >> n;

        std::vector<unsigned> stops(n);
        for (size_t i = 0; i < n; ++i)
            std::cin >> stops.at(i);

        std::cout << compute_min_refills(d, m, stops) << std::endl;
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
