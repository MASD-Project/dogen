/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_SERIALIZATION_QUALIFIED_NAME_SER_HPP
#define DOGEN_SML_SERIALIZATION_QUALIFIED_NAME_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include "dogen/sml/domain/qualified_name.hpp"
#include "dogen/sml/serialization/meta_types_ser.hpp"

namespace dogen {
namespace sml {

class qualified_name_serializer {
public:
    template<typename Archive>
    void serialize(Archive & ar,
        dogen::sml::qualified_name& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;
        ar & make_nvp("model_name", value.model_name_);
        ar & make_nvp("external_package_path", value.external_package_path_);
        ar & make_nvp("package_path", value.package_path_);
        ar & make_nvp("type_name", value.type_name_);
        ar & make_nvp("meta_type", value.meta_type_);
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::sml::qualified_name& value,
    const unsigned int version) {
    dogen::sml::qualified_name_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
