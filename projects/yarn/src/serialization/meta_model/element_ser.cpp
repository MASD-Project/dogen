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
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/yarn/serialization/meta_model/name_ser.hpp"
#include "dogen/annotations/serialization/annotation_ser.hpp"
#include "dogen/yarn/serialization/meta_model/module_ser.hpp"
#include "dogen/yarn/serialization/meta_model/object_ser.hpp"
#include "dogen/yarn/serialization/meta_model/builtin_ser.hpp"
#include "dogen/yarn/serialization/meta_model/concept_ser.hpp"
#include "dogen/yarn/serialization/meta_model/element_ser.hpp"
#include "dogen/yarn/serialization/meta_model/visitor_ser.hpp"
#include "dogen/yarn/serialization/meta_model/exception_ser.hpp"
#include "dogen/yarn/serialization/meta_model/primitive_ser.hpp"
#include "dogen/yarn/serialization/meta_model/enumeration_ser.hpp"
#include "dogen/yarn/serialization/meta_model/origin_types_ser.hpp"
#include "dogen/yarn/serialization/meta_model/element_properties_ser.hpp"

BOOST_CLASS_TRACKING(
    dogen::yarn::meta_model::element,
    boost::serialization::track_selectively)

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::yarn::meta_model::element& v,
    const unsigned int /*version*/) {
    ar << make_nvp("documentation", v.documentation_);
    ar << make_nvp("annotation", v.annotation_);
    ar << make_nvp("name", v.name_);
    ar << make_nvp("origin_type", v.origin_type_);
    ar << make_nvp("contained_by", v.contained_by_);
    ar << make_nvp("in_global_module", v.in_global_module_);
    ar << make_nvp("stereotypes", v.stereotypes_);
    ar << make_nvp("meta_name", v.meta_name_);
    ar << make_nvp("is_element_extension", v.is_element_extension_);
    ar << make_nvp("element_properties", v.element_properties_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::yarn::meta_model::element& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("documentation", v.documentation_);
    ar >> make_nvp("annotation", v.annotation_);
    ar >> make_nvp("name", v.name_);
    ar >> make_nvp("origin_type", v.origin_type_);
    ar >> make_nvp("contained_by", v.contained_by_);
    ar >> make_nvp("in_global_module", v.in_global_module_);
    ar >> make_nvp("stereotypes", v.stereotypes_);
    ar >> make_nvp("meta_name", v.meta_name_);
    ar >> make_nvp("is_element_extension", v.is_element_extension_);
    ar >> make_nvp("element_properties", v.element_properties_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::yarn::meta_model::element& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::yarn::meta_model::element& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::yarn::meta_model::element& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::yarn::meta_model::element& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::yarn::meta_model::element& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::yarn::meta_model::element& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::yarn::meta_model::element& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::yarn::meta_model::element& v, unsigned int version);

} }
