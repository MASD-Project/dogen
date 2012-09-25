/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_SERIALIZATION_PACKAGE_SER_HPP
#define DOGEN_SML_SERIALIZATION_PACKAGE_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include "dogen/sml/domain/package.hpp"
#include "dogen/sml/serialization/qualified_name_ser.hpp"

namespace dogen {
namespace sml {

class package_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::sml::package& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;
        archive & make_nvp("name", value.name_);
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::sml::package& value,
    const unsigned int version) {
    dogen::sml::package_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
