/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.codec/serialization/entities/comment_ser.hpp"
#include "dogen.codec/serialization/entities/element_ser.hpp"
#include "dogen.codec/serialization/entities/attribute_ser.hpp"
#include "dogen.identification/serialization/entities/name_ser.hpp"
#include "dogen.identification/serialization/entities/codec_id_ser.hpp"
#include "dogen.identification/serialization/entities/stereotype_ser.hpp"
#include "dogen.variability/serialization/entities/configuration_ser.hpp"
#include "dogen.identification/serialization/entities/tagged_value_ser.hpp"
#include "dogen.identification/serialization/entities/codec_provenance_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::codec::entities::element& v,
    const unsigned int /*version*/) {
    ar << make_nvp("tagged_values", v.tagged_values_);
    ar << make_nvp("stereotypes", v.stereotypes_);
    ar << make_nvp("templates", v.templates_);
    ar << make_nvp("configurations", v.configurations_);
    ar << make_nvp("name", v.name_);
    ar << make_nvp("configuration", v.configuration_);
    ar << make_nvp("provenance", v.provenance_);
    ar << make_nvp("tagged_values_overrides", v.tagged_values_overrides_);
    ar << make_nvp("comment", v.comment_);
    ar << make_nvp("parents", v.parents_);
    ar << make_nvp("attributes", v.attributes_);
    ar << make_nvp("fallback_element_type", v.fallback_element_type_);
    ar << make_nvp("can_be_primitive_underlier", v.can_be_primitive_underlier_);
    ar << make_nvp("in_global_module", v.in_global_module_);
    ar << make_nvp("can_be_enumeration_underlier", v.can_be_enumeration_underlier_);
    ar << make_nvp("is_default_enumeration_type", v.is_default_enumeration_type_);
    ar << make_nvp("is_associative_container", v.is_associative_container_);
    ar << make_nvp("is_floating_point", v.is_floating_point_);
    ar << make_nvp("containing_element_id", v.containing_element_id_);
    ar << make_nvp("plantuml", v.plantuml_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::codec::entities::element& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("tagged_values", v.tagged_values_);
    ar >> make_nvp("stereotypes", v.stereotypes_);
    ar >> make_nvp("templates", v.templates_);
    ar >> make_nvp("configurations", v.configurations_);
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("configuration", v.configuration_);
    ar >> make_nvp("provenance", v.provenance_);
    ar >> make_nvp("tagged_values_overrides", v.tagged_values_overrides_);
    ar >> make_nvp("comment", v.comment_);
    ar >> make_nvp("parents", v.parents_);
    ar >> make_nvp("attributes", v.attributes_);
    ar >> make_nvp("fallback_element_type", v.fallback_element_type_);
    ar >> make_nvp("can_be_primitive_underlier", v.can_be_primitive_underlier_);
    ar >> make_nvp("in_global_module", v.in_global_module_);
    ar >> make_nvp("can_be_enumeration_underlier", v.can_be_enumeration_underlier_);
    ar >> make_nvp("is_default_enumeration_type", v.is_default_enumeration_type_);
    ar >> make_nvp("is_associative_container", v.is_associative_container_);
    ar >> make_nvp("is_floating_point", v.is_floating_point_);
    ar >> make_nvp("containing_element_id", v.containing_element_id_);
    ar >> make_nvp("plantuml", v.plantuml_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::codec::entities::element& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::codec::entities::element& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::codec::entities::element& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::codec::entities::element& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::codec::entities::element& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::codec::entities::element& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::codec::entities::element& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::codec::entities::element& v, unsigned int version);

} }
