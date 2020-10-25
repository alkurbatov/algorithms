#include <iostream>
#include <memory>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
template <typename T>
struct Heap {
    static Heap* build(const std::vector<T>& data) {
        Heap* heap = new Heap(data);

        for (int i = data.size() / 2; i >= 0; --i)
            heap->siftDown(i);

        return heap;
    };

    unsigned leftChild(unsigned index) const {
        return 2*index + 1;
    }

    unsigned rightChild(unsigned index) const {
        return 2*index + 2;
    }

    void siftDown(unsigned index) {
        unsigned min_index = index;

        unsigned left = this->leftChild(index);
        if (left < m_data.size() && m_data[left] < m_data[min_index])
            min_index = left;

        unsigned right = this->rightChild(index);
        if (right < m_data.size() && m_data[right] < m_data[min_index])
            min_index = right;

        if (index != min_index) {
            m_swaps.emplace_back(index, min_index);
            std::swap(m_data[index], m_data[min_index]);
            this->siftDown(min_index);
        }
    }

    std::vector< std::pair<T, T>> swaps() const {
        return m_swaps;
    }

 private:
    explicit Heap(const std::vector<unsigned>& data): m_data(data) {
    }

    std::vector<T> m_data;
    std::vector< std::pair<T, T>> m_swaps;
};

std::vector< std::pair<unsigned, unsigned>> solution(const std::vector<unsigned>& data) {
    std::unique_ptr<Heap<unsigned>> heap(Heap<unsigned>::build(data));
    return heap->swaps();
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    std::vector< std::pair<unsigned, unsigned>> expected{ {1, 4}, {0, 1}, {1, 3} };

    ASSERT_EQ(solution({ 5, 4, 3, 2, 1 }), expected);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    ASSERT_EQ(solution({ 1, 2, 3, 4, 5 }).size(), 0);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        std::ios_base::sync_with_stdio(false);

        unsigned n;
        std::cin >> n;

        std::vector<unsigned> data;
        data.resize(n);
        for(unsigned i = 0; i < n; ++i)
            std::cin >> data[i];

        auto swaps = solution(data);

        std::cout << swaps.size() << std::endl;
        for (auto i : swaps)
            std::cout << i.first << " " << i.second << std::endl;

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
