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
#include "dogen.quilt.csharp/serialization/formattables/helper_descriptor_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::quilt::csharp::formattables::helper_descriptor& v,
    const unsigned int /*version*/) {
    ar << make_nvp("family", v.family_);
    ar << make_nvp("namespaces", v.namespaces_);
    ar << make_nvp("name_identifiable", v.name_identifiable_);
    ar << make_nvp("name_qualified", v.name_qualified_);
    ar << make_nvp("name_tree_qualified", v.name_tree_qualified_);
    ar << make_nvp("name_tree_identifiable", v.name_tree_identifiable_);
    ar << make_nvp("is_simple_type", v.is_simple_type_);
    ar << make_nvp("is_circular_dependency", v.is_circular_dependency_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::quilt::csharp::formattables::helper_descriptor& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("family", v.family_);
    ar >> make_nvp("namespaces", v.namespaces_);
    ar >> make_nvp("name_identifiable", v.name_identifiable_);
    ar >> make_nvp("name_qualified", v.name_qualified_);
    ar >> make_nvp("name_tree_qualified", v.name_tree_qualified_);
    ar >> make_nvp("name_tree_identifiable", v.name_tree_identifiable_);
    ar >> make_nvp("is_simple_type", v.is_simple_type_);
    ar >> make_nvp("is_circular_dependency", v.is_circular_dependency_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::quilt::csharp::formattables::helper_descriptor& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::quilt::csharp::formattables::helper_descriptor& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::quilt::csharp::formattables::helper_descriptor& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::quilt::csharp::formattables::helper_descriptor& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::quilt::csharp::formattables::helper_descriptor& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::quilt::csharp::formattables::helper_descriptor& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::quilt::csharp::formattables::helper_descriptor& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::quilt::csharp::formattables::helper_descriptor& v, unsigned int version);

} }
