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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_ENABLE_FACET_SERIALIZATION_SERIALIZATION_PACKAGE1_FIRST_CLASS_SER_HPP
#define DOGEN_ENABLE_FACET_SERIALIZATION_SERIALIZATION_PACKAGE1_FIRST_CLASS_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/enable_facet_serialization/domain/package1/first_class.hpp"
#include "dogen/enable_facet_serialization/serialization/versioned_key_ser.hpp"

namespace dogen {
namespace enable_facet_serialization {
namespace package1 {

class first_class_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::enable_facet_serialization::package1::first_class& value,
        const unsigned int /*version*/) {

        archive & value.public_attribute_;
        archive & value.private_attribute_;
        archive & value.versioned_key_;
    }
};

} } }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::enable_facet_serialization::package1::first_class& value,
    const unsigned int version) {
    dogen::enable_facet_serialization::package1::first_class_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
