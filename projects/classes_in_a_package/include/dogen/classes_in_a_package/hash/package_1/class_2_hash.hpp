/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASSES_IN_A_PACKAGE_HASH_PACKAGE_1_CLASS_2_HASH_HPP
#define DOGEN_CLASSES_IN_A_PACKAGE_HASH_PACKAGE_1_CLASS_2_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/classes_in_a_package/domain/package_1/class_2.hpp"
#include "dogen/classes_in_a_package/hash/versioned_key_hash.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace std {

template<>
class hash<dogen::classes_in_a_package::package_1::class_2> {
public:
    size_t operator()(dogen::classes_in_a_package::package_1::class_2 value) const {
        using dogen::utility::hash::combine;
        std::size_t seed(0);

        combine(seed, value.versioned_key());

        return seed;
    }
};

}
#endif
