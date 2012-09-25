/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
