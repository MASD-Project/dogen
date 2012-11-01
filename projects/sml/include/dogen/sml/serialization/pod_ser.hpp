/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_SML_SERIALIZATION_POD_SER_HPP
#define DOGEN_SML_SERIALIZATION_POD_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/optional.hpp>
#include "dogen/sml/domain/pod.hpp"
#include "dogen/sml/serialization/property_ser.hpp"
#include "dogen/sml/serialization/category_types_ser.hpp"
#include "dogen/sml/serialization/qualified_name_ser.hpp"

namespace dogen {
namespace sml {

class pod_serializer {
public:
    template<typename Archive>
    void serialize(Archive & archive,
        dogen::sml::pod& value,
        const unsigned int /*version*/) {
        using boost::serialization::make_nvp;
        archive & make_nvp("name", value.name_);
        archive & make_nvp("properties", value.properties_);
        archive & make_nvp("parent_name", value.parent_name_);
        archive & make_nvp("generate", value.generate_);
        archive & make_nvp("is_parent", value.is_parent_);
        archive & make_nvp("category_type", value.category_type_);
        archive & make_nvp("documentation", value.documentation_);
        archive & make_nvp("number_of_type_arguments",
            value.number_of_type_arguments_);
        archive & make_nvp("is_sequence_container",
            value.is_sequence_container_);
        archive & make_nvp("is_associative_container",
            value.is_associative_container_);
        archive & make_nvp("is_smart_pointer", value.is_smart_pointer_);
    }
};

} }

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(Archive & archive,
    dogen::sml::pod& value,
    const unsigned int version) {
    dogen::sml::pod_serializer serializer;
    serializer.serialize<Archive>(archive, value, version);
}

} }

#endif
