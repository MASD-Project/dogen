#ifndef PHI_HASH_TESTTYPE_HASH_HPP
#define PHI_HASH_TESTTYPE_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "Phi/types/TestType.hpp"

namespace Phi {

struct TestType_hasher {
public:
    static std::size_t hash(const TestType& v);
};

}

namespace std {

template<>
struct hash<Phi::TestType> {
public:
    size_t operator()(const Phi::TestType& v) const {
        return Phi::TestType_hasher::hash(v);
    }
};

}
#endif
