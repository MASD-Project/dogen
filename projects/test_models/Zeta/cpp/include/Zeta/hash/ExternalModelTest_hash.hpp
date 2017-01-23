#ifndef ZETA_HASH_EXTERNALMODELTEST_HASH_HPP
#define ZETA_HASH_EXTERNALMODELTEST_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "Zeta/types/ExternalModelTest.hpp"

namespace Zeta {

struct ExternalModelTest_hasher {
public:
    static std::size_t hash(const ExternalModelTest& v);
};

}

namespace std {

template<>
struct hash<Zeta::ExternalModelTest> {
public:
    size_t operator()(const Zeta::ExternalModelTest& v) const {
        return Zeta::ExternalModelTest_hasher::hash(v);
    }
};

}
#endif
