/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_TWO_LAYERS_WITH_OBJECTS_SERIALIZATION_PACKAGE_2_CLASS_2_SER_HPP
#define DOGEN_TWO_LAYERS_WITH_OBJECTS_SERIALIZATION_PACKAGE_2_CLASS_2_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/nvp.hpp>
#include "dogen/two_layers_with_objects/domain/Package_2/class_2.hpp"
#include "dogen/two_layers_with_objects/serialization/versioned_key_ser.hpp"

namespace dogen {
namespace two_layers_with_objects {
namespace Package_2 {

class class_2_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::two_layers_with_objects::Package_2::class_2& value,
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
    dogen::two_layers_with_objects::Package_2::class_2& value,
    const unsigned int version) {
    dogen::two_layers_with_objects::Package_2::class_2_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
