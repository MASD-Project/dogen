#include "dogen/test_models/split_project/hash/package1/first_class_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}

namespace dogen {
namespace test_models {
namespace split_project {
namespace package1 {

std::size_t first_class_hasher::hash(const first_class& v) {
    std::size_t seed(0);

    combine(seed, v.public_attribute());
    combine(seed, v.private_attribute());

    return seed;
}

} } } }
