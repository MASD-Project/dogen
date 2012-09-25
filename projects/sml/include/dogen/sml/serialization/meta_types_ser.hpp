/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_SERIALIZATION_META_TYPES_SER_HPP
#define DOGEN_SML_SERIALIZATION_META_TYPES_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include "dogen/sml/domain/meta_types.hpp"

namespace dogen {
namespace sml {

class meta_types_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::sml::meta_types& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;
        archive & make_nvp("meta_types", value);
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::sml::meta_types& value,
    const unsigned int version) {
    dogen::sml::meta_types_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
