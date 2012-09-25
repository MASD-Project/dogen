/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASSES_INSIDE_AND_OUTSIDE_PACKAGE_SERIALIZATION_CLASS_2_SER_HPP
#define DOGEN_CLASSES_INSIDE_AND_OUTSIDE_PACKAGE_SERIALIZATION_CLASS_2_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/nvp.hpp>
#include "dogen/classes_inside_and_outside_package/domain/class_2.hpp"
#include "dogen/classes_inside_and_outside_package/serialization/versioned_key_ser.hpp"

namespace dogen {
namespace classes_inside_and_outside_package {

class class_2_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::classes_inside_and_outside_package::class_2& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;

        archive & make_nvp("versioned_key", value.versioned_key_);
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::classes_inside_and_outside_package::class_2& value,
    const unsigned int version) {
    dogen::classes_inside_and_outside_package::class_2_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
