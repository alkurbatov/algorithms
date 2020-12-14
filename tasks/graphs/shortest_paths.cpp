#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#ifdef DEBUG
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace
{
struct Node;

struct Link
{
    Link(const Node* to_, int cost_): to(to_), cost(cost_)
    {}

    const Node* to;
    int cost;
};

struct Node
{
    explicit Node(unsigned id_): id(id_)
    {}

    unsigned id = 0;
    std::vector<Link> links;
};

struct Graph
{
    explicit Graph(size_t vertices_)
    {
        reset(vertices_);
    }

    void reset(size_t vertices_)
    {
        m_nodes.clear();

        for (size_t i = 0; i < vertices_; ++i)
            m_nodes.emplace_back(i + 1);
    }

    void link(unsigned from_, unsigned to_, int cost_)
    {
        m_nodes[from_ - 1].links.emplace_back(&m_nodes[to_ - 1], cost_);
    }

    std::vector<std::string> distances(unsigned from_) const
    {
        std::vector<long int> dist(m_nodes.size(), std::numeric_limits<long int>::max());
        dist[from_ - 1] = 0;

        std::queue<const Node*> negative;
        for (size_t it = 0; it < m_nodes.size(); ++it)
        {
            std::queue<const Node*> open;
            open.push(&m_nodes[from_ - 1]);

            std::vector<unsigned> closed(m_nodes.size(), 0);
            closed[from_ - 1] = 1;

            while (!open.empty())
            {
                const Node* node = open.front();
                open.pop();

                for (const auto& link : node->links)
                {
                    long int nextMoveCost = dist[node ->id - 1] + link.cost;
                    if (dist[link.to->id - 1] > nextMoveCost)
                    {
                        dist[link.to->id - 1] = nextMoveCost;

                        if (it == m_nodes.size() - 1)
                            negative.push(link.to);
                    }

                    if (closed[link.to->id - 1])
                        continue;

                    open.push(link.to);
                    closed[link.to->id - 1] = 1;
                }
            }
        }

        while (!negative.empty())
        {
            const Node* node = negative.front();
            negative.pop();

            for (const auto& link : node->links)
            {
                if (dist[link.to->id - 1] == std::numeric_limits<long int>::min())
                    continue;

                dist[link.to->id - 1] = std::numeric_limits<long int>::min();
                negative.push(link.to);
            }
        }

        std::vector<std::string> distance;
        for (size_t i = 0; i < m_nodes.size(); ++i)
        {
            if (dist[i] == std::numeric_limits<long int>::min())
            {
                distance.emplace_back("-");
                continue;
            }

            if (dist[i] == std::numeric_limits<long int>::max())
            {
                distance.emplace_back("*");
                continue;
            }

            distance.emplace_back(std::to_string(dist[i]));
        }

        return distance;
    }

 private:
    std::vector<Node> m_nodes;
};

#ifdef DEBUG
void test_solution() {
    Timer timer;

    Graph graph(6);
    graph.link(1, 2, 10);
    graph.link(2, 3, 5);
    graph.link(1, 3, 100);
    graph.link(3, 5, 7);
    graph.link(5, 4, 10);
    graph.link(4, 3, -18);
    graph.link(6, 1, -1);

    ASSERT_THAT(graph.distances(1), testing::ElementsAre("0", "10", "-", "-", "-", "*"));
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();
    graph.reset(5);

    graph.link(1, 2, 1);
    graph.link(4, 1, 2);
    graph.link(2, 3, 2);
    graph.link(3, 1, -5);

    ASSERT_THAT(graph.distances(4), testing::ElementsAre("-", "-", "-", "0", "*"));
    EXPECT_LE(timer.elapsed(), 2000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1)
    {
        size_t n, m;
        std::cin >> n >> m;

        Graph graph(n);

        unsigned from, to;
        int cost;
        for (size_t i = 0; i < m; ++i)
        {
          std::cin >> from >> to >> cost;
          graph.link(from, to, cost);
        }

        std::cin >> from;
        for (const auto& dist : graph.distances(from))
            std::cout << dist << std::endl;

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
