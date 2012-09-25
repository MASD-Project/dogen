/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_ALL_PRIMITIVES_HASH_A_CLASS_HASH_HPP
#define DOGEN_ALL_PRIMITIVES_HASH_A_CLASS_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/all_primitives/domain/a_class.hpp"
#include "dogen/all_primitives/hash/versioned_key_hash.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace std {

template<>
class hash<dogen::all_primitives::a_class> {
public:
    size_t operator()(dogen::all_primitives::a_class value) const {
        using dogen::utility::hash::combine;
        std::size_t seed(0);

        combine(seed, value.bool_property());
        combine(seed, value.char_property());
        combine(seed, value.uchar_property());
        combine(seed, value.int_property());
        combine(seed, value.uint_property());
        combine(seed, value.long_property());
        combine(seed, value.ulong_property());
        combine(seed, value.long_long_property());
        combine(seed, value.ulong_long_property());
        combine(seed, value.short_property());
        combine(seed, value.ushort_property());
        combine(seed, value.versioned_key());

        return seed;
    }
};

}
#endif
