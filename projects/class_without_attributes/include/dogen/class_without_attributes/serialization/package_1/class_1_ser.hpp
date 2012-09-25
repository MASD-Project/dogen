/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASS_WITHOUT_ATTRIBUTES_SERIALIZATION_PACKAGE_1_CLASS_1_SER_HPP
#define DOGEN_CLASS_WITHOUT_ATTRIBUTES_SERIALIZATION_PACKAGE_1_CLASS_1_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/nvp.hpp>
#include "dogen/class_without_attributes/domain/package_1/class_1.hpp"
#include "dogen/class_without_attributes/serialization/versioned_key_ser.hpp"

namespace dogen {
namespace class_without_attributes {
namespace package_1 {

class class_1_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::class_without_attributes::package_1::class_1& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;

        archive & make_nvp("versioned_key", value.versioned_key_);
    }
};

} } }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::class_without_attributes::package_1::class_1& value,
    const unsigned int version) {
    dogen::class_without_attributes::package_1::class_1_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
