#ifndef PHI_HASH_COLLECTIONTESTTYPE_HASH_HPP
#define PHI_HASH_COLLECTIONTESTTYPE_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "Phi/types/CollectionTestType.hpp"

namespace Phi {

struct CollectionTestType_hasher {
public:
    static std::size_t hash(const CollectionTestType& v);
};

}

namespace std {

template<>
struct hash<Phi::CollectionTestType> {
public:
    size_t operator()(const Phi::CollectionTestType& v) const {
        return Phi::CollectionTestType_hasher::hash(v);
    }
};

}
#endif
