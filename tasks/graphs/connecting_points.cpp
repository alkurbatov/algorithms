#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace
{
struct Point
{
    Point(unsigned id_, int x_, int y_): id(id_), x(x_), y(y_)
    {}

    long double distance(const Point& to_) const
    {
        return sqrtl(powl(x - to_.x, 2) + powl(y - to_.y, 2));
    }

    unsigned id;
    int x;
    int y;
};

struct Vertex
{
    Vertex(const Point* from_, const Point* to_, long double cost_): from(from_), to(to_), cost(cost_)
    {}

    const Point* from;
    const Point* to;
    long double cost;
};

long double solution(const std::vector<Point>& points_)
{
    long double pathLength = 0.0;

    auto comparer = [](const auto& lhs_, const auto& rhs_)
    {
        return lhs_.cost > rhs_.cost;
    };

    std::priority_queue<Vertex, std::vector<Vertex>, decltype(comparer)> open(comparer);
    std::vector<unsigned> closed(points_.size(), 0);

    open.emplace(&points_[0], &points_[0], 0.0);

    while (!open.empty())
    {
        Vertex vertex(open.top());
        open.pop();

        if (closed[vertex.to->id])
            continue;

        closed[vertex.to->id] = 1;
        pathLength += vertex.cost;

        for (const auto& nextPoint : points_)
        {
            if (closed[nextPoint.id])
                continue;

            long double cost = vertex.to->distance(nextPoint);
            open.emplace(vertex.to, &points_[nextPoint.id], cost);
        }
    }

    return pathLength;
}

#ifdef DEBUG
void test_solution()
{
    Timer timer;
    std::vector<Point> points;

    points.emplace_back(0, 0, 0);
    points.emplace_back(1, 0, 1);
    points.emplace_back(2, 1, 0);
    points.emplace_back(3, 1, 1);

    ASSERT_DOUBLE_EQ(solution(points), 3.0);
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();
    points.clear();

    points.emplace_back(0, 0, 0);
    points.emplace_back(1, 0, 2);
    points.emplace_back(2, 1, 1);
    points.emplace_back(3, 3, 0);
    points.emplace_back(4, 3, 2);

    ASSERT_DOUBLE_EQ(solution(points), 7.0644951022459797);
    EXPECT_LE(timer.elapsed(), 2000);
}
#endif
} // namespace

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        size_t n;
        std::cin >> n;

        int x, y;
        std::vector<Point> points;
        for (size_t i = 0; i < n; ++i)
        {
          std::cin >> x >> y;
          points.emplace_back(i, x, y);
        }

        std::cout << std::setprecision(10) << solution(points) << std::endl;

        return 0;
    }

#ifdef DEBUG
    if (std::string(argv[1]) == "test")
    {
        test_solution();
        return 0;
    }
#endif

    return 1;
}
