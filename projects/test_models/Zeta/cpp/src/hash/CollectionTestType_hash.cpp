#include "Phi/hash/CollectionTestType_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_vector_std_string(const std::vector<std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace Phi {

std::size_t CollectionTestType_hasher::hash(const CollectionTestType& v) {
    std::size_t seed(0);

    combine(seed, hash_std_vector_std_string(v.BinariesTest()));
    return seed;
}

}
