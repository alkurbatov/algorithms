#include <iostream>
#include <stack>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace
{
struct Node
{
    explicit Node(unsigned id_): id(id_), region(0)
    {}

    unsigned id = 0;
    unsigned region = 0;
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

    unsigned markRegions()
    {
        unsigned regions = 0;

        for (size_t i = 0; i < m_nodes.size(); ++i)
        {
            if (m_nodes[i].region)
                continue;

            ++regions;

            std::stack<Node*> open;
            open.push(&m_nodes[i]);

            while(!open.empty())
            {
                Node* node = open.top();
                open.pop();

                if (node->region)
                    continue;

                node->region = regions;

                for (const auto link : node->links)
                    open.push(link);
            }
        }

        return regions;
    }

 private:
    std::vector<Node> m_nodes;
};

#ifdef DEBUG
void test_solution() {
    Timer timer;

    Graph graph(4);
    graph.link(1, 2);
    graph.link(3, 2);

    ASSERT_EQ(graph.markRegions(), 2);
    EXPECT_LE(timer.elapsed(), 1000);
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

        std::cout << graph.markRegions() << std::endl;

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
