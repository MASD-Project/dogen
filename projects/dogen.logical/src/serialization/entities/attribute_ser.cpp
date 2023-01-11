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
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.logical/serialization/entities/attribute_ser.hpp"
#include "dogen.logical/serialization/entities/stereotypes_ser.hpp"
#include "dogen.variability/serialization/entities/configuration_ser.hpp"
#include "dogen.identification/serialization/entities/logical_name_ser.hpp"
#include "dogen.identification/serialization/entities/logical_name_tree_ser.hpp"
#include "dogen.logical/serialization/entities/orm/attribute_properties_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::logical::entities::attribute& v,
    const unsigned int /*version*/) {
    ar << make_nvp("documentation", v.documentation_);
    ar << make_nvp("configuration", v.configuration_);
    ar << make_nvp("name", v.name_);
    ar << make_nvp("stereotypes", v.stereotypes_);
    ar << make_nvp("unparsed_type", v.unparsed_type_);
    ar << make_nvp("parsed_type", v.parsed_type_);
    ar << make_nvp("is_immutable", v.is_immutable_);
    ar << make_nvp("is_fluent", v.is_fluent_);
    ar << make_nvp("orm_properties", v.orm_properties_);
    ar << make_nvp("member_variable_name", v.member_variable_name_);
    ar << make_nvp("getter_setter_name", v.getter_setter_name_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::logical::entities::attribute& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("documentation", v.documentation_);
    ar >> make_nvp("configuration", v.configuration_);
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("stereotypes", v.stereotypes_);
    ar >> make_nvp("unparsed_type", v.unparsed_type_);
    ar >> make_nvp("parsed_type", v.parsed_type_);
    ar >> make_nvp("is_immutable", v.is_immutable_);
    ar >> make_nvp("is_fluent", v.is_fluent_);
    ar >> make_nvp("orm_properties", v.orm_properties_);
    ar >> make_nvp("member_variable_name", v.member_variable_name_);
    ar >> make_nvp("getter_setter_name", v.getter_setter_name_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::logical::entities::attribute& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::logical::entities::attribute& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::logical::entities::attribute& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::logical::entities::attribute& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::logical::entities::attribute& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::logical::entities::attribute& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::logical::entities::attribute& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::logical::entities::attribute& v, unsigned int version);

} }