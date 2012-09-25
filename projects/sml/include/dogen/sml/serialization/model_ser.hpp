/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_SERIALIZATION_MODEL_SER_HPP
#define DOGEN_SML_SERIALIZATION_MODEL_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include "dogen/utility/serialization/unordered_map.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/sml/serialization/qualified_name_ser.hpp"
#include "dogen/sml/serialization/package_ser.hpp"
#include "dogen/sml/serialization/pod_ser.hpp"
#include "dogen/sml/serialization/primitive_ser.hpp"

namespace dogen {
namespace sml {

class model_serializer {
public:
    template<typename Archive>
    void serialize(Archive & ar,
        dogen::sml::model& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;
        ar & make_nvp("name", value.name_);
        ar & make_nvp("packages", value.packages_);
        ar & make_nvp("pods", value.pods_);
        ar & make_nvp("primitives", value.primitives_);
        ar & make_nvp("external_package_path", value.external_package_path_);
        ar & make_nvp("schema_name", value.schema_name_);
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::sml::model& value,
    const unsigned int version) {
    dogen::sml::model_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
