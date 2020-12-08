#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace
{
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

    bool isBipartite() const
    {
        enum Colors
        {
            None,
            Black,
            White,
        };

        std::vector<Colors> colors(m_nodes.size(), Colors::None);

        for (size_t i = 0; i < m_nodes.size(); ++i)
        {
            if (colors[i] != Colors::None)
                continue;

            std::queue<const Node*> open;
            open.push(&m_nodes[i]);
            colors[i] = Colors::Black;

            while (!open.empty())
            {
                const Node* node = open.front();
                open.pop();

                for (const auto link : node->links)
                {
                    if (colors[node->id - 1] == colors[link->id - 1])
                        return false;

                    if (colors[link->id - 1] != Colors::None)
                        continue;

                    if (colors[node->id - 1] == Colors::Black)
                        colors[link->id - 1] = Colors::White;
                    else
                        colors[link->id - 1] = Colors::Black;

                    open.push(link);
                }
            }
        }

        return true;
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

    ASSERT_FALSE(graph.isBipartite());
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();
    graph.reset(5);
    graph.link(5, 2);
    graph.link(4, 2);
    graph.link(3, 4);
    graph.link(1, 4);

    ASSERT_TRUE(graph.isBipartite());
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

        std::cout << graph.isBipartite() << std::endl;

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
