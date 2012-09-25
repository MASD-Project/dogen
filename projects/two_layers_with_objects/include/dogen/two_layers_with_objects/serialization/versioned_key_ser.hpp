/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_TWO_LAYERS_WITH_OBJECTS_SERIALIZATION_VERSIONED_KEY_SER_HPP
#define DOGEN_TWO_LAYERS_WITH_OBJECTS_SERIALIZATION_VERSIONED_KEY_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/nvp.hpp>
#include "dogen/two_layers_with_objects/domain/versioned_key.hpp"

namespace dogen {
namespace two_layers_with_objects {

class versioned_key_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::two_layers_with_objects::versioned_key& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;

        archive & make_nvp("id", value.id_);
        archive & make_nvp("version", value.version_);
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::two_layers_with_objects::versioned_key& value,
    const unsigned int version) {
    dogen::two_layers_with_objects::versioned_key_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
