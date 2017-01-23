#ifndef PHI_HASH_SOMEENUM_HASH_HPP
#define PHI_HASH_SOMEENUM_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "Phi/types/SomeEnum.hpp"

namespace std {

template<>
struct hash<Phi::SomeEnum> {
public:
    size_t operator()(const Phi::SomeEnum& v) const {
        return std::hash<unsigned int>()(static_cast<unsigned int>(v));
    }
};

}

#endif
