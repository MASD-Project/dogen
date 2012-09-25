/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_COMPRESSED_HASH_PACKAGE1_FIRST_CLASS_HASH_HPP
#define DOGEN_COMPRESSED_HASH_PACKAGE1_FIRST_CLASS_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/compressed/domain/package1/first_class.hpp"
#include "dogen/compressed/hash/versioned_key_hash.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace std {

template<>
class hash<dogen::compressed::package1::first_class> {
public:
    size_t operator()(dogen::compressed::package1::first_class value) const {
        using dogen::utility::hash::combine;
        std::size_t seed(0);

        combine(seed, value.public_attribute());
        combine(seed, value.private_attribute());
        combine(seed, value.versioned_key());

        return seed;
    }
};

}
#endif
