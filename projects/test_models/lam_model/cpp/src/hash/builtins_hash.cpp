#include "dogen/test_models/lam_model/hash/builtins_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}

namespace dogen {
namespace test_models {
namespace lam_model {

std::size_t builtins_hasher::hash(const builtins& v) {
    std::size_t seed(0);

    combine(seed, v.prop_0());
    combine(seed, v.prop_1());
    combine(seed, v.prop_2());
    combine(seed, v.prop_3());
    combine(seed, v.prop_4());
    combine(seed, v.prop_5());
    combine(seed, v.prop_6());
    combine(seed, v.prop_7());
    combine(seed, v.prop_8());
    combine(seed, v.prop_9());

    return seed;
}

} } }
