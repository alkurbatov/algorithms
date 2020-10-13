#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#ifdef DEBUG
#include <fstream>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
const int DROPPED = -1;
const int SCHEDULED = -2;

struct Packet {
    Packet(unsigned arrival_time, unsigned process_time):
        arrival_time(arrival_time), process_time(process_time) {
    }

    unsigned arrival_time;
    unsigned process_time;
};

struct Socket {
    Socket(): m_data_to_send(0) {
    }

    void send(unsigned data) {
        m_data_to_send = data;
    }

    void next_tick() {
        if (m_data_to_send == 0)
            return;

        --m_data_to_send;
    }

    unsigned data_left() const {
        return m_data_to_send;
    }

    bool ready() const {
        return m_data_to_send == 0;
    }

 private:
    unsigned m_data_to_send;
};

struct Planner {
    explicit Planner(unsigned buffer_size):
        m_now(0), m_available_buffer(buffer_size) {
    }

    void schedule(const Packet& packet) {
        if (m_available_buffer == 0) {
            m_responses.push_back(DROPPED);
            return;
        }

        if (m_work_to_do.empty() && packet.process_time == 0) {
            m_responses.push_back(m_now);
            return;
        }

        m_responses.push_back(SCHEDULED);
        m_work_to_do.push(packet);
        --m_available_buffer;
    }

    void next_tick() {
        if (m_socket.ready()) {
            while(!m_work_to_do.empty()) {
                auto pos = std::find(m_responses.begin(), m_responses.end(), SCHEDULED);
                *pos = m_now;

                if (m_work_to_do.front().process_time == 0) {
                    m_work_to_do.pop();
                    continue;
                }

                m_socket.send(m_work_to_do.front().process_time);
                break;
            }
        }

        if (m_socket.data_left()) {
            m_socket.next_tick();

            if (m_socket.ready()) {
                ++m_available_buffer;
                m_work_to_do.pop();
            }
        }

        ++m_now;
    }

    std::vector<int> responses() const {
        return m_responses;
    }

    bool idle() const {
        return m_work_to_do.empty();
    }

    unsigned now() const {
        return m_now;
    }

    unsigned available_buffer() const {
        return m_available_buffer;
    }

 private:
    unsigned m_now;
    unsigned m_available_buffer;
    std::queue<Packet> m_work_to_do;
    std::vector<int> m_responses;
    Socket m_socket;
};

std::vector<int> solution(unsigned buffer_size, const std::deque<Packet>& packets) {
    Planner planner(buffer_size);
    std::queue<Packet> input(packets);

    while(!input.empty() || !planner.idle()) {
        while(!input.empty()) {
            if (input.front().arrival_time != planner.now())
                break;

            planner.schedule(input.front());
            input.pop();
        }

        planner.next_tick();
    }

    return planner.responses();
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();

    ASSERT_TRUE(solution(1, {}).empty());
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();

    ASSERT_THAT(
        solution(1, { Packet(0, 0) }),
        testing::ElementsAre(0)
    );
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();

    ASSERT_THAT(
        solution(1, { Packet(0, 1), Packet(0, 1) }),
        testing::ElementsAre(0, DROPPED)
    );
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();

    ASSERT_THAT(
        solution(1, { Packet(0, 1), Packet(1, 1) }),
        testing::ElementsAre(0, 1)
    );
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();

    ASSERT_THAT(
        solution(1, { Packet(0, 1), Packet(0, 0) }),
        testing::ElementsAre(0, DROPPED)
    );
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();

    ASSERT_THAT(
        solution(1, { Packet(0, 0), Packet(0, 0) }),
        testing::ElementsAre(0, 0)
    );
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();

    ASSERT_THAT(
        solution(2, { Packet(0, 1), Packet(0, 1) }),
        testing::ElementsAre(0, 1)
    );
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();

    ASSERT_THAT(
        solution(1, { Packet(0, 0), Packet(0, 1) }),
        testing::ElementsAre(0, 0)
    );
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();

    ASSERT_THAT(
        solution(1, { Packet(0, 1), Packet(1, 3), Packet(4, 2) }),
        testing::ElementsAre(0, 1, 4)
    );
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();

    ASSERT_THAT(
        solution(1, { Packet(0, 2), Packet(1, 4), Packet(5, 3) }),
        testing::ElementsAre(0, DROPPED, 5)
    );
    EXPECT_LE(timer.elapsed(), 2000);
}

void test_solution_on_file(const std::string& task, const std::string& answers) {
    std::ifstream task_file(task);
    if (!task_file.is_open()) {
        std::cerr << "Failed to open task file " << task << std::endl;
        return;
    }

    unsigned buffer_size, count;
    task_file >> buffer_size >> count;

    std::deque<Packet> packets;
    while(!task_file.eof()) {
        unsigned arrival_time, process_time;
        task_file >> arrival_time >> process_time;

        packets.emplace_back(arrival_time, process_time);
    }

    task_file.close();

    auto timer = Timer();
    std::vector<int> responses = solution(buffer_size, packets);
    EXPECT_LE(timer.elapsed(), 2000);

    std::ifstream answers_file(answers);
    if (!answers_file.is_open()) {
        std::cerr << "Failed to open result file " << task << std::endl;
        return;
    }

    unsigned index = 0;
    while(!answers_file.eof()) {
        int answer;
        answers_file >> answer;
        ASSERT_EQ(responses[index], answer);
        ++index;
    }

    answers_file.close();
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        unsigned buffer_size;
        std::cin >> buffer_size;

        unsigned count;
        std::cin >> count;

        std::deque<Packet> packets;
        for (int i = 0; i < count; ++i) {
            unsigned arrival_time, process_time;
            std::cin >> arrival_time >> process_time;

            packets.emplace_back(arrival_time, process_time);
        }

        std::vector<int> responses = solution(buffer_size, packets);

        for (auto r : responses)
            std::cout << r << std::endl;

        return 0;
    }

#ifdef DEBUG
    if (std::string(argv[1]) == "test") {
        test_solution();
        return 0;
    }

    if (std::string(argv[1]) == "from-files") {
        test_solution_on_file(argv[2], argv[3]);
        return 0;
    }
#endif

    return 1;
}
