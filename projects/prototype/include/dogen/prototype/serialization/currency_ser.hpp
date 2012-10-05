/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_PROTOTYPE_SERIALIZATION_CURRENCY_SER_HPP
#define DOGEN_PROTOTYPE_SERIALIZATION_CURRENCY_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/string.hpp>
#include <boost/serialization/access.hpp>
#include "dogen/prototype/serialization/versioned_key_ser.hpp"
#include "dogen/prototype/domain/currency.hpp"

namespace dogen {
namespace prototype {

class currency_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::prototype::currency& serializee,
        const unsigned int /*version*/) {
        archive & serializee.versioned_key_;
        archive & serializee.numeric_code_;
        archive & serializee.name_;
        archive & serializee.alpha_code_;
        archive & serializee.decimal_places_;
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::prototype::currency& serializee,
    const unsigned int version) {
    dogen::prototype::currency_serializer serializer;
    serializer.serialize<Archive>(archive, serializee, version);
}

} }

#endif
