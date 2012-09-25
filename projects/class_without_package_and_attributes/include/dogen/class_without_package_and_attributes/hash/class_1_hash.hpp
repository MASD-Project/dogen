/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASS_WITHOUT_PACKAGE_AND_ATTRIBUTES_HASH_CLASS_1_HASH_HPP
#define DOGEN_CLASS_WITHOUT_PACKAGE_AND_ATTRIBUTES_HASH_CLASS_1_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/class_without_package_and_attributes/domain/class_1.hpp"
#include "dogen/class_without_package_and_attributes/hash/versioned_key_hash.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace std {

template<>
class hash<dogen::class_without_package_and_attributes::class_1> {
public:
    size_t operator()(dogen::class_without_package_and_attributes::class_1 value) const {
        using dogen::utility::hash::combine;
        std::size_t seed(0);

        combine(seed, value.versioned_key());

        return seed;
    }
};

}
#endif
