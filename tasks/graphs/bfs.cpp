#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace
{
const int NOT_FOUND = -1;

struct Node
{
    explicit Node(unsigned id_): id(id_)
    {}

    void print() const
    {
        std::cout << "id: " << id << std::endl;

        std::cout << "\tlinks: ";
        for (const auto link : links)
            std::cout << link->id << " ";
        std::cout << std::endl;
    }

    unsigned id = 0;
    std::vector<Node*> links;
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

    void link(unsigned from_, unsigned to_)
    {
        m_nodes[from_ - 1].links.push_back(&m_nodes[to_ - 1]);
        m_nodes[to_ - 1].links.push_back(&m_nodes[from_ - 1]);
    }

    int distance(unsigned from_, unsigned to_) const
    {
        std::vector<unsigned> dist(m_nodes.size(), std::numeric_limits<unsigned>::max());

        std::queue<const Node*> open;
        open.push(&m_nodes[from_ - 1]);
        dist[open.front()->id - 1] = 0;

        while (!open.empty())
        {
            const Node* node = open.front();
            open.pop();

            if (node->id == to_)
                return dist[node->id - 1];

            for (const auto link : node->links)
            {
                if (dist[link->id - 1] != std::numeric_limits<unsigned>::max())
                    continue;

                open.push(link);
                dist[link->id - 1] = dist[node->id - 1] + 1;
            }
        }

        return NOT_FOUND;
    }

    void print() const
    {
        std::cout << "----------------" << std::endl;

        for (const auto& node : m_nodes)
            node.print();
    }

 private:
    std::vector<Node> m_nodes;
};

#ifdef DEBUG
void test_solution() {
    Timer timer;

    Graph graph(4);
    graph.link(1, 2);
    graph.link(4, 1);
    graph.link(2, 3);
    graph.link(3, 1);

    ASSERT_EQ(graph.distance(2, 4), 2);
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();
    graph.reset(5);
    graph.link(5, 2);
    graph.link(1, 3);
    graph.link(3, 4);
    graph.link(1, 4);

    ASSERT_EQ(graph.distance(3, 5), NOT_FOUND);
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
        for (size_t i = 0; i < m; ++i)
        {
          std::cin >> from >> to;
          graph.link(from, to);
        }

        std::cin >> from >> to;

        std::cout << graph.distance(from, to) << std::endl;

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
