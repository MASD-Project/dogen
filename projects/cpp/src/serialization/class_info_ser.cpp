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
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include "dogen/cpp/serialization/class_info_ser.hpp"
#include "dogen/cpp/serialization/class_types_ser.hpp"
#include "dogen/cpp/serialization/entity_ser.hpp"
#include "dogen/cpp/serialization/parent_info_ser.hpp"
#include "dogen/cpp/serialization/property_info_ser.hpp"
#include "dogen/sml/serialization/generation_types_ser.hpp"


BOOST_CLASS_TRACKING(
    dogen::cpp::class_info,
    boost::serialization::track_selectively)

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::cpp::class_info& v,
    const unsigned int /*version*/) {
    ar << make_nvp("entity", base_object<dogen::cpp::entity>(v));

    ar << make_nvp("name", v.name_);
    ar << make_nvp("namespaces", v.namespaces_);
    ar << make_nvp("properties", v.properties_);
    ar << make_nvp("all_properties", v.all_properties_);
    ar << make_nvp("has_primitive_properties", v.has_primitive_properties_);
    ar << make_nvp("requires_stream_manipulators", v.requires_stream_manipulators_);
    ar << make_nvp("requires_manual_move_constructor", v.requires_manual_move_constructor_);
    ar << make_nvp("requires_manual_default_constructor", v.requires_manual_default_constructor_);
    ar << make_nvp("parents", v.parents_);
    ar << make_nvp("is_parent", v.is_parent_);
    ar << make_nvp("original_parent_name", v.original_parent_name_);
    ar << make_nvp("original_parent_name_qualified", v.original_parent_name_qualified_);
    ar << make_nvp("leaves", v.leaves_);
    ar << make_nvp("opaque_parameters", v.opaque_parameters_);
    ar << make_nvp("is_comparable", v.is_comparable_);
    ar << make_nvp("is_visitable", v.is_visitable_);
    ar << make_nvp("is_immutable", v.is_immutable_);
    ar << make_nvp("is_original_parent_visitable", v.is_original_parent_visitable_);
    ar << make_nvp("class_type", v.class_type_);
    ar << make_nvp("generation_type", v.generation_type_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::cpp::class_info& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("entity", base_object<dogen::cpp::entity>(v));

    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("namespaces", v.namespaces_);
    ar >> make_nvp("properties", v.properties_);
    ar >> make_nvp("all_properties", v.all_properties_);
    ar >> make_nvp("has_primitive_properties", v.has_primitive_properties_);
    ar >> make_nvp("requires_stream_manipulators", v.requires_stream_manipulators_);
    ar >> make_nvp("requires_manual_move_constructor", v.requires_manual_move_constructor_);
    ar >> make_nvp("requires_manual_default_constructor", v.requires_manual_default_constructor_);
    ar >> make_nvp("parents", v.parents_);
    ar >> make_nvp("is_parent", v.is_parent_);
    ar >> make_nvp("original_parent_name", v.original_parent_name_);
    ar >> make_nvp("original_parent_name_qualified", v.original_parent_name_qualified_);
    ar >> make_nvp("leaves", v.leaves_);
    ar >> make_nvp("opaque_parameters", v.opaque_parameters_);
    ar >> make_nvp("is_comparable", v.is_comparable_);
    ar >> make_nvp("is_visitable", v.is_visitable_);
    ar >> make_nvp("is_immutable", v.is_immutable_);
    ar >> make_nvp("is_original_parent_visitable", v.is_original_parent_visitable_);
    ar >> make_nvp("class_type", v.class_type_);
    ar >> make_nvp("generation_type", v.generation_type_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::cpp::class_info& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::cpp::class_info& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::cpp::class_info& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::cpp::class_info& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::cpp::class_info& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::cpp::class_info& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::cpp::class_info& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::cpp::class_info& v, unsigned int version);

} }