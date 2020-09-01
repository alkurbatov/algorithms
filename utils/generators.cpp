#include <algorithm>
#include <vector>

#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

namespace {
boost::random::random_device rng;
}

std::vector<int> generateRandomSequence(size_t length) {
    boost::random::uniform_int_distribution<> udist(1, length);
    std::vector<int> res(length);

    std::generate(res.begin(), res.end(), std::bind(udist, std::ref(rng)));
    return res;
}
