#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
// first - id of a thread;
// second - point in the future when the job will be finished.
typedef std::pair<unsigned, unsigned long long> busy_tread_t;

struct Comp{
    bool operator()(const busy_tread_t& a, const busy_tread_t& b) const {
        return a.second > b.second;
    }
};

struct Scheduler {
    Scheduler(unsigned num_threads, const std::vector<unsigned>& jobs):
        m_time(0), m_jobs(std::deque<unsigned>(jobs.begin(), jobs.end())) {
        while(num_threads > 0)
            m_idle_threads.push(--num_threads);
    }

    std::vector<std::pair<unsigned, unsigned long long>> schedule() const {
        return m_schedule;
    }

    bool finished() {
        return m_jobs.empty();
    }

    void nextTick() {
        while(!m_busy_threads.empty()) {
            if (m_time < m_busy_threads.top().second)
                break;

            unsigned id = m_busy_threads.top().first;
#ifdef DEBUG
            std::cout << "Job's done! id: " << id << std::endl;
#endif

            m_idle_threads.push(id);
            m_busy_threads.pop();
        }

        while(!m_idle_threads.empty() && !m_jobs.empty()) {
            unsigned id = m_idle_threads.top();
            unsigned long long done_at = m_time + m_jobs.front();
            m_busy_threads.emplace(id, done_at);

#ifdef DEBUG
            std::cout << "Starting new job! id: " << id <<
                " todo: " << m_jobs.front() <<
                " done at: " << done_at << std::endl;
#endif

            m_schedule.push_back({m_idle_threads.top(), m_time});

            m_jobs.pop();
            m_idle_threads.pop();
        }

        if (m_idle_threads.empty() || m_jobs.empty())
            m_time = m_busy_threads.top().second;
        else
            ++m_time;
    }

 private:
    unsigned long long m_time;
    std::queue<unsigned> m_jobs;
    std::priority_queue<busy_tread_t, std::vector<busy_tread_t>, Comp> m_busy_threads;
    std::priority_queue<unsigned, std::vector<unsigned>, std::greater<unsigned>> m_idle_threads;
    std::vector<std::pair<unsigned, unsigned long long>> m_schedule;
};

std::vector<std::pair<unsigned, unsigned long long>> solution(unsigned num_threads, const std::vector<unsigned>& jobs) {
    Scheduler scheduler(num_threads, jobs);
    while (!scheduler.finished())
        scheduler.nextTick();

    return scheduler.schedule();
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    std::vector<std::pair<unsigned, unsigned long long>> expected{ {0, 0}, {1, 0}, {0, 1}, {1, 2}, {0, 4} };

    ASSERT_EQ(solution(2, { 1, 2, 3, 4, 5 }), expected);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    expected.assign({
        {0, 0}, {1, 0}, {2, 0}, {3, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1}, {0, 2}, {1, 2},
        {2, 2}, {3, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}
    });

    ASSERT_EQ(solution(4, { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }), expected);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    expected.assign({
        {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0},
        {7, 28787989}, {0, 124860658}, {5, 235543106}, {7, 246504708}, {4, 311346104},
        {3, 349021732}, {1, 388437511}, {9, 409836312}, {3, 595181715}, {9, 619331540},
        {6, 665655446}, {8, 706718118}, {1, 707425685}, {2, 753484620}, {5, 845266823},
        {0, 882135358}, {0, 1030418770}, {7, 1127475443}, {0, 1226053489}, {1, 1239139577},
        {4, 1283739291}, {8, 1294605118}, {6, 1439488110}, {5, 1448354598}, {3, 1449889884},
        {2, 1488265968}, {8, 1492349613}, {1, 1543303433}, {8, 1552026381}, {1, 1559345794},
        {9, 1564932477}, {6, 1700692640}, {8, 1762133312}, {9, 1785403332}, {9, 1812712043},
        {4, 1837912198}, {0, 1923308283}, {8, 1925648764}, {2, 1951684676}, {8, 2051689774},
        {5, 2089663653}, {7, 2096109190}, {8, 2100522306}, {3, 2222963076}, {0, 2320394874},
        {4, 2343014119}, {6, 2347796988}, {4, 2405752997}, {1, 2461343674}, {8, 2507700390},
        {0, 2563144828}, {9, 2649050912}, {2, 2656370100}, {6, 2792825301}, {1, 2831769133},
        {9, 2930053292}, {7, 2936370273}, {3, 2946336306}, {5, 3033959396}, {0, 3104934106},
        {8, 3114837717}, {4, 3140480513}, {2, 3205065638}, {2, 3236887517}, {2, 3282959311},
        {0, 3306478249}, {3, 3363648528}, {8, 3408035489}, {4, 3439090637}, {6, 3444003346},
        {1, 3470199591}, {5, 3480453036}, {0, 3490305631}, {1, 3506565968}, {7, 3585123350},
        {0, 3618937640}, {0, 3638771343}, {2, 3792650094}, {4, 3815595208}, {5, 3884584250},
        {9, 3911731663}, {8, 3932551852}, {5, 3943003928}, {5, 3992901123}, {1, 4042282164},
        {7, 4055834901}, {9, 4086865161}, {0, 4155619221}, {5, 4181243134}, {6, 4192821467}
    });

    ASSERT_EQ(solution(10, {
        124860658, 388437511, 753484620, 349021732, 311346104,
        235543106, 665655446, 28787989, 706718118, 409836312,
        217716719, 757274700, 609723717, 880970735, 972393187,
        246159983, 318988174, 209495228, 854708169, 945600937,
        773832664, 587887000, 531713892, 734781348, 603087775,
        148283412, 195634719, 968633747, 697254794, 304163856,
        554172907, 197744495, 261204530, 641309055, 773073192,
        463418708, 59676768, 16042361, 210106931, 901997880,
        220470855, 647104348, 163515452, 27308711, 836338869,
        505101921, 397086591, 126041010, 704685424, 48832532,
        944295743, 840261083, 407178084, 723373230, 242749954,
        62738878, 445028313, 734727516, 370425459, 607137327,
        541789278, 281002380, 548695538, 651178045, 638430458,
        981678371, 648753077, 417312222, 446493640, 201544143,
        293197772, 298610124, 31821879, 46071794, 509690783,
        183827382, 867731980, 524516363, 376504571, 748818121,
        36366377, 404131214, 128632009, 535716196, 470711551,
        19833703, 516847878, 422344417, 453049973, 58419678,
        175133498, 967886806, 49897195, 188342011, 272087192,
        798530288, 210486166, 836411405, 909200386, 561566778
    }), expected);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        std::ios_base::sync_with_stdio(false);

        unsigned num_threads, num_jobs;
        std::cin >> num_threads >> num_jobs;

        std::vector<unsigned> jobs;
        jobs.resize(num_jobs);
        for(unsigned i = 0; i < num_jobs; ++i)
            std::cin >> jobs[i];

        auto schedule = solution(num_threads, jobs);

        for (auto i : schedule)
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
