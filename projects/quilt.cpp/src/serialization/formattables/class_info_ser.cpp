/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/yarn/serialization/generation_types_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/entity_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/class_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/parent_info_ser.hpp"
#include "dogen/quilt.cpp/serialization/formattables/property_info_ser.hpp"

BOOST_CLASS_TRACKING(
    dogen::quilt::cpp::formattables::class_info,
    boost::serialization::track_selectively)

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::quilt::cpp::formattables::class_info& v,
    const unsigned int /*version*/) {
    ar << make_nvp("entity", base_object<dogen::quilt::cpp::formattables::entity>(v));

    ar << make_nvp("properties", v.properties_);
    ar << make_nvp("all_properties", v.all_properties_);
    ar << make_nvp("requires_stream_manipulators", v.requires_stream_manipulators_);
    ar << make_nvp("requires_manual_move_constructor", v.requires_manual_move_constructor_);
    ar << make_nvp("requires_manual_default_constructor", v.requires_manual_default_constructor_);
    ar << make_nvp("parents", v.parents_);
    ar << make_nvp("is_parent", v.is_parent_);
    ar << make_nvp("root_parent_name", v.root_parent_name_);
    ar << make_nvp("root_parent_name_qualified", v.root_parent_name_qualified_);
    ar << make_nvp("leaves", v.leaves_);
    ar << make_nvp("is_visitable", v.is_visitable_);
    ar << make_nvp("is_immutable", v.is_immutable_);
    ar << make_nvp("is_root_parent_visitable", v.is_root_parent_visitable_);
    ar << make_nvp("generation_type", v.generation_type_);
    ar << make_nvp("is_final", v.is_final_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::quilt::cpp::formattables::class_info& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("entity", base_object<dogen::quilt::cpp::formattables::entity>(v));

    ar >> make_nvp("properties", v.properties_);
    ar >> make_nvp("all_properties", v.all_properties_);
    ar >> make_nvp("requires_stream_manipulators", v.requires_stream_manipulators_);
    ar >> make_nvp("requires_manual_move_constructor", v.requires_manual_move_constructor_);
    ar >> make_nvp("requires_manual_default_constructor", v.requires_manual_default_constructor_);
    ar >> make_nvp("parents", v.parents_);
    ar >> make_nvp("is_parent", v.is_parent_);
    ar >> make_nvp("root_parent_name", v.root_parent_name_);
    ar >> make_nvp("root_parent_name_qualified", v.root_parent_name_qualified_);
    ar >> make_nvp("leaves", v.leaves_);
    ar >> make_nvp("is_visitable", v.is_visitable_);
    ar >> make_nvp("is_immutable", v.is_immutable_);
    ar >> make_nvp("is_root_parent_visitable", v.is_root_parent_visitable_);
    ar >> make_nvp("generation_type", v.generation_type_);
    ar >> make_nvp("is_final", v.is_final_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::quilt::cpp::formattables::class_info& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::quilt::cpp::formattables::class_info& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::quilt::cpp::formattables::class_info& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::quilt::cpp::formattables::class_info& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::quilt::cpp::formattables::class_info& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::quilt::cpp::formattables::class_info& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::quilt::cpp::formattables::class_info& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::quilt::cpp::formattables::class_info& v, unsigned int version);

} }
