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
#include "dogen/cpp/serialization/nested_type_info_ser.hpp"

#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::cpp::nested_type_info& v,
    const unsigned int /*version*/) {
    ar << make_nvp("name", v.name_);
    ar << make_nvp("identifiable_name", v.identifiable_name_);
    ar << make_nvp("complete_name", v.complete_name_);
    ar << make_nvp("complete_identifiable_name", v.complete_identifiable_name_);
    ar << make_nvp("is_primitive", v.is_primitive_);
    ar << make_nvp("is_enumeration", v.is_enumeration_);
    ar << make_nvp("is_string_like", v.is_string_like_);
    ar << make_nvp("is_char_like", v.is_char_like_);
    ar << make_nvp("is_int_like", v.is_int_like_);
    ar << make_nvp("is_sequence_container", v.is_sequence_container_);
    ar << make_nvp("is_associative_container", v.is_associative_container_);
    ar << make_nvp("is_smart_pointer", v.is_smart_pointer_);
    ar << make_nvp("is_optional_like", v.is_optional_like_);
    ar << make_nvp("is_variant_like", v.is_variant_like_);
    ar << make_nvp("children", v.children_);
    ar << make_nvp("namespaces", v.namespaces_);
    ar << make_nvp("is_filesystem_path", v.is_filesystem_path_);
    ar << make_nvp("is_date", v.is_date_);
    ar << make_nvp("is_ptime", v.is_ptime_);
    ar << make_nvp("is_time_duration", v.is_time_duration_);
    ar << make_nvp("is_pair", v.is_pair_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::cpp::nested_type_info& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("identifiable_name", v.identifiable_name_);
    ar >> make_nvp("complete_name", v.complete_name_);
    ar >> make_nvp("complete_identifiable_name", v.complete_identifiable_name_);
    ar >> make_nvp("is_primitive", v.is_primitive_);
    ar >> make_nvp("is_enumeration", v.is_enumeration_);
    ar >> make_nvp("is_string_like", v.is_string_like_);
    ar >> make_nvp("is_char_like", v.is_char_like_);
    ar >> make_nvp("is_int_like", v.is_int_like_);
    ar >> make_nvp("is_sequence_container", v.is_sequence_container_);
    ar >> make_nvp("is_associative_container", v.is_associative_container_);
    ar >> make_nvp("is_smart_pointer", v.is_smart_pointer_);
    ar >> make_nvp("is_optional_like", v.is_optional_like_);
    ar >> make_nvp("is_variant_like", v.is_variant_like_);
    ar >> make_nvp("children", v.children_);
    ar >> make_nvp("namespaces", v.namespaces_);
    ar >> make_nvp("is_filesystem_path", v.is_filesystem_path_);
    ar >> make_nvp("is_date", v.is_date_);
    ar >> make_nvp("is_ptime", v.is_ptime_);
    ar >> make_nvp("is_time_duration", v.is_time_duration_);
    ar >> make_nvp("is_pair", v.is_pair_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::cpp::nested_type_info& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::cpp::nested_type_info& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::cpp::nested_type_info& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::cpp::nested_type_info& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::cpp::nested_type_info& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::cpp::nested_type_info& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::cpp::nested_type_info& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::cpp::nested_type_info& v, unsigned int version);

#ifdef __linux__
template void save(eos::portable_oarchive& ar, const dogen::cpp::nested_type_info& v, unsigned int version);
template void load(eos::portable_iarchive& ar, dogen::cpp::nested_type_info& v, unsigned int version);
#endif

} }