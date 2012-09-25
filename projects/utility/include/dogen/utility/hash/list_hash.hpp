/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_HASH_LIST_HASH_HPP
#define DOGEN_UTILITY_HASH_LIST_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <functional>
#include "dogen/utility/hash/combine.hpp"

namespace std {

// FIXME: couldn't get this to work
template<typename HashableType>
class hash<std::list<HashableType> > {
public:
    size_t operator()(const HashableType& value) const {
        size_t seed(0);
        for (auto hashableType : value)
            dogen::utility::hash::combine(seed, hashableType);
        return seed;
    }
};

}

#endif
