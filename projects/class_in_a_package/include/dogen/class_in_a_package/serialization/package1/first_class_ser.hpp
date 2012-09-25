/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASS_IN_A_PACKAGE_SERIALIZATION_PACKAGE1_FIRST_CLASS_SER_HPP
#define DOGEN_CLASS_IN_A_PACKAGE_SERIALIZATION_PACKAGE1_FIRST_CLASS_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/nvp.hpp>
#include "dogen/class_in_a_package/domain/package1/first_class.hpp"
#include "dogen/class_in_a_package/serialization/versioned_key_ser.hpp"

namespace dogen {
namespace class_in_a_package {
namespace package1 {

class first_class_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::class_in_a_package::package1::first_class& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;

        archive & make_nvp("public_attribute", value.public_attribute_);
        archive & make_nvp("private_attribute", value.private_attribute_);
        archive & make_nvp("versioned_key", value.versioned_key_);
    }
};

} } }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::class_in_a_package::package1::first_class& value,
    const unsigned int version) {
    dogen::class_in_a_package::package1::first_class_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
