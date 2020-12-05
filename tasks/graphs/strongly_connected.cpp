#include <algorithm>
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
    explicit Node(unsigned id_): id(id_), postorder(0)
    {}

    Node* expand(const std::vector<unsigned>& closed_) const
    {
        for (const auto link : links)
        {
            if (closed_[link->id - 1])
                continue;

            return link;
        }

        return nullptr;
    }

    void print() const
    {
        std::cout << "id: " << id
            << "(" << postorder << ")"
            << std::endl;

        std::cout << "\t";
        for (const auto link : links)
            std::cout << link->id << " ";
        std::cout << std::endl;
    }

    unsigned id = 0;
    unsigned postorder = 0;
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
    }

    void reverse()
    {
        std::vector<Node> oldOrder(m_nodes);

        for (auto& node : m_nodes)
            node.links.clear();

        for (size_t i = 0; i < oldOrder.size(); ++i)
        {
            for (const auto to : oldOrder[i].links)
                link(to->id, m_nodes[i].id);
        }
    }

    void calculatePostOrders()
    {
        std::vector<unsigned> closed(m_nodes.size(), 0);

        unsigned postorder = 0;
        for (size_t i = 0; i < m_nodes.size(); ++i)
        {
            if (closed[i])
                continue;

            std::stack<Node*> open;
            open.push(&m_nodes[i]);

            while(!open.empty())
            {
                Node* node = open.top();
                closed[node->id - 1] = 1;
                ++postorder;

                Node* expandedNode = node->expand(closed);
                if (expandedNode)
                {
                    closed[expandedNode->id - 1] = 1;
                    open.push(expandedNode);
                    continue;
                }

                node->postorder = postorder;
                open.pop();
            }
        }
    }

    unsigned calculateRegions() const
    {
        std::vector<const Node*> sorted;
        for (size_t i = 0; i < m_nodes.size(); ++i)
            sorted.push_back(&m_nodes[i]);

        std::sort(sorted.begin(), sorted.end(),
            [] (const auto& lhs_, const auto& rhs_)
            {
                return lhs_->postorder > rhs_->postorder;
            });

        std::vector<unsigned> closed(m_nodes.size(), 0);

        unsigned regions = 0;
        for (size_t i = 0; i < sorted.size(); ++i)
        {
            if (closed[sorted[i]->id - 1])
                continue;

            std::stack<const Node*> open;
            open.push(sorted[i]);

            while(!open.empty())
            {
                const Node* node = open.top();
                closed[node->id - 1] = 1;

                Node* expandedNode = node->expand(closed);
                if (expandedNode)
                {
                    closed[expandedNode->id - 1] = 1;
                    open.push(expandedNode);
                    continue;
                }

                open.pop();
            }

            ++regions;
        }

        return regions;
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

unsigned solution(Graph& graph_)
{
    //graph_.print();
    graph_.reverse();

    graph_.calculatePostOrders();

    graph_.reverse();
    //graph_.print();

    return graph_.calculateRegions();
}

#ifdef DEBUG
void test_solution() {
    Timer timer;

    Graph graph(4);
    graph.link(1, 2);
    graph.link(4, 1);
    graph.link(2, 3);
    graph.link(3, 1);

    ASSERT_EQ(solution(graph), 2);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    graph.reset(5);
    graph.link(2, 1);
    graph.link(3, 2);
    graph.link(3, 1);
    graph.link(4, 3);
    graph.link(4, 1);
    graph.link(5, 2);
    graph.link(5, 3);

    ASSERT_EQ(solution(graph), 5);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    graph.reset(4);
    graph.link(1, 2);
    graph.link(3, 2);
    graph.link(4, 3);

    ASSERT_EQ(solution(graph), 4);
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

        std::cout << solution(graph) << std::endl;

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
