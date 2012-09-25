/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_TWO_LAYERS_WITH_OBJECTS_HASH_PACKAGE_1_CLASS_1_HASH_HPP
#define DOGEN_TWO_LAYERS_WITH_OBJECTS_HASH_PACKAGE_1_CLASS_1_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/two_layers_with_objects/domain/package_1/class_1.hpp"
#include "dogen/two_layers_with_objects/hash/versioned_key_hash.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace std {

template<>
class hash<dogen::two_layers_with_objects::package_1::class_1> {
public:
    size_t operator()(dogen::two_layers_with_objects::package_1::class_1 value) const {
        using dogen::utility::hash::combine;
        std::size_t seed(0);

        combine(seed, value.versioned_key());

        return seed;
    }
};

}
#endif
