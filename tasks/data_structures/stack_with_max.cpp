#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct StackWithMax {
    explicit StackWithMax(unsigned size) {
        m_aux.reserve(100000);
        m_stack.reserve(100000);
    }

    void push(int value) {
        m_stack.push_back(value);

        if (m_aux.empty()) {
            m_aux.push_back(value);
            return;
        }

        if (m_aux.back() >= value) {
            m_aux.push_back(m_aux.back());
            return;
        }

        m_aux.push_back(value);
    }

    void pop() {
        m_aux.pop_back();
        m_stack.pop_back();
    }

    int max() const {
        return m_aux.back();
    }

 private:
    std::vector<int> m_aux;
    std::vector<int> m_stack;
};

int main() {
    unsigned num_queries;
    std::cin >> num_queries;

    StackWithMax stack(num_queries);

    for (unsigned i = 0; i < num_queries; ++i) {
        std::string query;
        std::cin >> query;

        if (query == "push") {
            unsigned value;
            std::cin >> value;

            stack.push(value);
            continue;
        }

        if (query == "pop") {
            stack.pop();
            continue;
        }

        if (query == "max") {
            std::cout << stack.max() << std::endl;
            continue;
        }
    }

    return 0;
}
