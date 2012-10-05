/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_PROTOTYPE_HASH_CURRENCY_HASH_HPP
#define DOGEN_PROTOTYPE_HASH_CURRENCY_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/prototype/domain/currency.hpp"
#include "dogen/prototype/hash/versioned_key_hash.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace std {

/**
 * @brief Hash function for currency.
 *
 * Relies on the currency invariant that all instances of this class
 * are faithful to ISO 4217.
 */
template<>
class hash<dogen::prototype::currency> {
public:
    size_t operator()(dogen::prototype::currency value) const {
        using dogen::utility::hash::combine;
        std::size_t seed(0);

        combine(seed, value.name());
        combine(seed, value.alpha_code());
        combine(seed, value.decimal_places());
        combine(seed, value.numeric_code());
        combine(seed, value.versioned_key());

        return seed;
    }
};

}

#endif
