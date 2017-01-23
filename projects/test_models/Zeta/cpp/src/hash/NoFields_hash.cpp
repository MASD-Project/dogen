#include "Phi/hash/NoFields_hash.hpp"

namespace {


}

namespace Phi {

std::size_t NoFields_hasher::hash(const NoFields&) {
    std::size_t seed(0);
    return seed;
}

}
