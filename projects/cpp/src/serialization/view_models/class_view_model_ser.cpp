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
#include <boost/serialization/vector.hpp>
#include "dogen/cpp/serialization/view_models/class_view_model_ser.hpp"
#include "dogen/cpp/serialization/view_models/parent_view_model_ser.hpp"
#include "dogen/cpp/serialization/view_models/property_view_model_ser.hpp"

#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::cpp::view_models::class_view_model& v,
    const unsigned int /*version*/) {
    ar << make_nvp("namespaces", v.namespaces_);
    ar << make_nvp("name", v.name_);
    ar << make_nvp("properties", v.properties_);
    ar << make_nvp("all_properties", v.all_properties_);
    ar << make_nvp("has_primitive_properties", v.has_primitive_properties_);
    ar << make_nvp("requires_stream_manipulators", v.requires_stream_manipulators_);
    ar << make_nvp("requires_manual_move_constructor", v.requires_manual_move_constructor_);
    ar << make_nvp("requires_manual_default_constructor", v.requires_manual_default_constructor_);
    ar << make_nvp("parents", v.parents_);
    ar << make_nvp("is_parent", v.is_parent_);
    ar << make_nvp("documentation", v.documentation_);
    ar << make_nvp("original_parent_name", v.original_parent_name_);
    ar << make_nvp("leaves", v.leaves_);
    ar << make_nvp("implementation_specific_parameters", v.implementation_specific_parameters_);
    ar << make_nvp("is_comparable", v.is_comparable_);
    ar << make_nvp("is_visitable", v.is_visitable_);
    ar << make_nvp("is_fluent", v.is_fluent_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::cpp::view_models::class_view_model& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("namespaces", v.namespaces_);
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("properties", v.properties_);
    ar >> make_nvp("all_properties", v.all_properties_);
    ar >> make_nvp("has_primitive_properties", v.has_primitive_properties_);
    ar >> make_nvp("requires_stream_manipulators", v.requires_stream_manipulators_);
    ar >> make_nvp("requires_manual_move_constructor", v.requires_manual_move_constructor_);
    ar >> make_nvp("requires_manual_default_constructor", v.requires_manual_default_constructor_);
    ar >> make_nvp("parents", v.parents_);
    ar >> make_nvp("is_parent", v.is_parent_);
    ar >> make_nvp("documentation", v.documentation_);
    ar >> make_nvp("original_parent_name", v.original_parent_name_);
    ar >> make_nvp("leaves", v.leaves_);
    ar >> make_nvp("implementation_specific_parameters", v.implementation_specific_parameters_);
    ar >> make_nvp("is_comparable", v.is_comparable_);
    ar >> make_nvp("is_visitable", v.is_visitable_);
    ar >> make_nvp("is_fluent", v.is_fluent_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::cpp::view_models::class_view_model& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::cpp::view_models::class_view_model& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::cpp::view_models::class_view_model& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::cpp::view_models::class_view_model& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::cpp::view_models::class_view_model& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::cpp::view_models::class_view_model& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::cpp::view_models::class_view_model& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::cpp::view_models::class_view_model& v, unsigned int version);

#ifdef __linux__
template void save(eos::portable_oarchive& ar, const dogen::cpp::view_models::class_view_model& v, unsigned int version);
template void load(eos::portable_iarchive& ar, dogen::cpp::view_models::class_view_model& v, unsigned int version);
#endif

} }