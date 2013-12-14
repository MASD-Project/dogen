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
#include "dogen/sml/serialization/abstract_object_ser.hpp"
#include "dogen/sml/serialization/entity_ser.hpp"
#include "dogen/sml/serialization/factory_ser.hpp"
#include "dogen/sml/serialization/keyed_entity_ser.hpp"
#include "dogen/sml/serialization/operation_ser.hpp"
#include "dogen/sml/serialization/property_ser.hpp"
#include "dogen/sml/serialization/qname_ser.hpp"
#include "dogen/sml/serialization/relationship_types_ser.hpp"
#include "dogen/sml/serialization/repository_ser.hpp"
#include "dogen/sml/serialization/service_ser.hpp"
#include "dogen/sml/serialization/type_ser.hpp"
#include "dogen/sml/serialization/value_object_ser.hpp"
#include "dogen/utility/serialization/unordered_map.hpp"

#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

BOOST_CLASS_TRACKING(
    dogen::sml::abstract_object,
    boost::serialization::track_selectively)

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::sml::abstract_object& v,
    const unsigned int /*version*/) {
    ar << make_nvp("type", base_object<dogen::sml::type>(v));

    ar << make_nvp("all_properties", v.all_properties_);
    ar << make_nvp("local_properties", v.local_properties_);
    ar << make_nvp("inherited_properties", v.inherited_properties_);
    ar << make_nvp("operations", v.operations_);
    ar << make_nvp("is_parent", v.is_parent_);
    ar << make_nvp("number_of_type_arguments", v.number_of_type_arguments_);
    ar << make_nvp("is_visitable", v.is_visitable_);
    ar << make_nvp("is_immutable", v.is_immutable_);
    ar << make_nvp("is_versioned", v.is_versioned_);
    ar << make_nvp("is_comparable", v.is_comparable_);
    ar << make_nvp("is_fluent", v.is_fluent_);
    ar << make_nvp("is_child", v.is_child_);
    ar << make_nvp("relationships", v.relationships_);
    ar << make_nvp("is_inheritance_root", v.is_inheritance_root_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::sml::abstract_object& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("type", base_object<dogen::sml::type>(v));

    ar >> make_nvp("all_properties", v.all_properties_);
    ar >> make_nvp("local_properties", v.local_properties_);
    ar >> make_nvp("inherited_properties", v.inherited_properties_);
    ar >> make_nvp("operations", v.operations_);
    ar >> make_nvp("is_parent", v.is_parent_);
    ar >> make_nvp("number_of_type_arguments", v.number_of_type_arguments_);
    ar >> make_nvp("is_visitable", v.is_visitable_);
    ar >> make_nvp("is_immutable", v.is_immutable_);
    ar >> make_nvp("is_versioned", v.is_versioned_);
    ar >> make_nvp("is_comparable", v.is_comparable_);
    ar >> make_nvp("is_fluent", v.is_fluent_);
    ar >> make_nvp("is_child", v.is_child_);
    ar >> make_nvp("relationships", v.relationships_);
    ar >> make_nvp("is_inheritance_root", v.is_inheritance_root_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::sml::abstract_object& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::sml::abstract_object& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::sml::abstract_object& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::sml::abstract_object& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::sml::abstract_object& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::sml::abstract_object& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::sml::abstract_object& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::sml::abstract_object& v, unsigned int version);

#ifdef __linux__
template void save(eos::portable_oarchive& ar, const dogen::sml::abstract_object& v, unsigned int version);
template void load(eos::portable_iarchive& ar, dogen::sml::abstract_object& v, unsigned int version);
#endif

} }