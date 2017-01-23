#ifndef PHI_HASH_NOFIELDS_HASH_HPP
#define PHI_HASH_NOFIELDS_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "Phi/types/NoFields.hpp"

namespace Phi {

struct NoFields_hasher {
public:
    static std::size_t hash(const NoFields& v);
};

}

namespace std {

template<>
struct hash<Phi::NoFields> {
public:
    size_t operator()(const Phi::NoFields& v) const {
        return Phi::NoFields_hasher::hash(v);
    }
};

}
#endif
