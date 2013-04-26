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
#include <boost/serialization/nvp.hpp>
#include "dogen/dia_to_sml/serialization/object_profile_ser.hpp"

#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::dia_to_sml::object_profile& v,
    const unsigned int /*version*/) {
    ar << make_nvp("is_uml_large_package", v.is_uml_large_package_);
    ar << make_nvp("is_uml_class", v.is_uml_class_);
    ar << make_nvp("is_uml_generalization", v.is_uml_generalization_);
    ar << make_nvp("is_uml_association", v.is_uml_association_);
    ar << make_nvp("is_uml_note", v.is_uml_note_);
    ar << make_nvp("is_uml_message", v.is_uml_message_);
    ar << make_nvp("is_uml_realization", v.is_uml_realization_);
    ar << make_nvp("is_enumeration", v.is_enumeration_);
    ar << make_nvp("is_exception", v.is_exception_);
    ar << make_nvp("is_entity", v.is_entity_);
    ar << make_nvp("is_value", v.is_value_);
    ar << make_nvp("is_service", v.is_service_);
    ar << make_nvp("is_non_generatable", v.is_non_generatable_);
    ar << make_nvp("is_versioned", v.is_versioned_);
    ar << make_nvp("is_keyed", v.is_keyed_);
    ar << make_nvp("is_visitable", v.is_visitable_);
    ar << make_nvp("is_immutable", v.is_immutable_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::dia_to_sml::object_profile& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("is_uml_large_package", v.is_uml_large_package_);
    ar >> make_nvp("is_uml_class", v.is_uml_class_);
    ar >> make_nvp("is_uml_generalization", v.is_uml_generalization_);
    ar >> make_nvp("is_uml_association", v.is_uml_association_);
    ar >> make_nvp("is_uml_note", v.is_uml_note_);
    ar >> make_nvp("is_uml_message", v.is_uml_message_);
    ar >> make_nvp("is_uml_realization", v.is_uml_realization_);
    ar >> make_nvp("is_enumeration", v.is_enumeration_);
    ar >> make_nvp("is_exception", v.is_exception_);
    ar >> make_nvp("is_entity", v.is_entity_);
    ar >> make_nvp("is_value", v.is_value_);
    ar >> make_nvp("is_service", v.is_service_);
    ar >> make_nvp("is_non_generatable", v.is_non_generatable_);
    ar >> make_nvp("is_versioned", v.is_versioned_);
    ar >> make_nvp("is_keyed", v.is_keyed_);
    ar >> make_nvp("is_visitable", v.is_visitable_);
    ar >> make_nvp("is_immutable", v.is_immutable_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::dia_to_sml::object_profile& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::dia_to_sml::object_profile& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::dia_to_sml::object_profile& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::dia_to_sml::object_profile& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::dia_to_sml::object_profile& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::dia_to_sml::object_profile& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::dia_to_sml::object_profile& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::dia_to_sml::object_profile& v, unsigned int version);

#ifdef __linux__
template void save(eos::portable_oarchive& ar, const dogen::dia_to_sml::object_profile& v, unsigned int version);
template void load(eos::portable_iarchive& ar, dogen::dia_to_sml::object_profile& v, unsigned int version);
#endif

} }