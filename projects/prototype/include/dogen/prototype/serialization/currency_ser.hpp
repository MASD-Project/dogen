/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
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
