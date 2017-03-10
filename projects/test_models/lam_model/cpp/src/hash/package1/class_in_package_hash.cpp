#include "dogen/test_models/lam_model/hash/package1/class_in_package_hash.hpp"

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
namespace package1 {

std::size_t class_in_package_hasher::hash(const class_in_package& v) {
    std::size_t seed(0);

    combine(seed, v.prop_0());
    return seed;
}

} } } }
