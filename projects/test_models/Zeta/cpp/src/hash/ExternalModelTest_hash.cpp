#include "Phi/hash/Date_hash.hpp"
#include "Zeta/hash/ExternalModelTest_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_list_std_list_std_string(const std::list<std::list<std::string> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_list_std_string(i));
    }
    return seed;
}

inline std::size_t hash_std_list_std_list_std_list_std_string(const std::list<std::list<std::list<std::string> > >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_list_std_list_std_string(i));
    }
    return seed;
}

}

namespace Zeta {

std::size_t ExternalModelTest_hasher::hash(const ExternalModelTest& v) {
    std::size_t seed(0);

    combine(seed, v.DateTest());
    combine(seed, hash_std_list_std_string(v.BinariesTest()));
    combine(seed, hash_std_list_std_list_std_string(v.CollectionOfCollectionTest()));
    combine(seed, hash_std_list_std_list_std_list_std_string(v.CollectionOfCollectionOfCollectionTest()));

    return seed;
}

}
