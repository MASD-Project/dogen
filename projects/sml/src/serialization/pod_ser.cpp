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
#include <boost/serialization/optional.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include "dogen/sml/serialization/category_types_ser.hpp"
#include "dogen/sml/serialization/pod_ser.hpp"
#include "dogen/sml/serialization/pod_types_ser.hpp"
#include "dogen/sml/serialization/property_ser.hpp"
#include "dogen/sml/serialization/qualified_name_ser.hpp"

#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::sml::pod& v,
    const unsigned int /*version*/) {
    ar << make_nvp("name", v.name_);
    ar << make_nvp("properties", v.properties_);
    ar << make_nvp("parent_name", v.parent_name_);
    ar << make_nvp("original_parent_name", v.original_parent_name_);
    ar << make_nvp("leaves", v.leaves_);
    ar << make_nvp("generate", v.generate_);
    ar << make_nvp("is_parent", v.is_parent_);
    ar << make_nvp("category_type", v.category_type_);
    ar << make_nvp("pod_type", v.pod_type_);
    ar << make_nvp("documentation", v.documentation_);
    ar << make_nvp("number_of_type_arguments", v.number_of_type_arguments_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::sml::pod& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("properties", v.properties_);
    ar >> make_nvp("parent_name", v.parent_name_);
    ar >> make_nvp("original_parent_name", v.original_parent_name_);
    ar >> make_nvp("leaves", v.leaves_);
    ar >> make_nvp("generate", v.generate_);
    ar >> make_nvp("is_parent", v.is_parent_);
    ar >> make_nvp("category_type", v.category_type_);
    ar >> make_nvp("pod_type", v.pod_type_);
    ar >> make_nvp("documentation", v.documentation_);
    ar >> make_nvp("number_of_type_arguments", v.number_of_type_arguments_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::sml::pod& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::sml::pod& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::sml::pod& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::sml::pod& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::sml::pod& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::sml::pod& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::sml::pod& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::sml::pod& v, unsigned int version);

#ifdef __linux__
template void save(eos::portable_oarchive& ar, const dogen::sml::pod& v, unsigned int version);
template void load(eos::portable_iarchive& ar, dogen::sml::pod& v, unsigned int version);
#endif

} }