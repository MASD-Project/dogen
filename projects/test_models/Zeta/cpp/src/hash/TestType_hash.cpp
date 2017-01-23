#include "Zeta/hash/String_hash.hpp"
#include "Phi/hash/TestType_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}

namespace Phi {

std::size_t TestType_hasher::hash(const TestType& v) {
    std::size_t seed(0);

    combine(seed, v.Version());
    combine(seed, v.AField());

    return seed;
}

}
