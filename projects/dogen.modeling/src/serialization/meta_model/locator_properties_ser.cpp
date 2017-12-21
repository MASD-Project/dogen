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
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.modeling/serialization/meta_model/locator_properties_ser.hpp"
#include "dogen.modeling/serialization/meta_model/model_segment_properties_ser.hpp"
#include "dogen.modeling/serialization/meta_model/directory_structure_styles_ser.hpp"
#include "dogen.modeling/serialization/meta_model/archetype_family_properties_ser.hpp"
#include "dogen.modeling/serialization/meta_model/intra_backend_segment_properties_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::modeling::meta_model::locator_properties& v,
    const unsigned int /*version*/) {
    ar << make_nvp("directory_structure_style", v.directory_structure_style_);
    ar << make_nvp("name_separator", v.name_separator_);
    ar << make_nvp("model_segment_properties", v.model_segment_properties_);
    ar << make_nvp("intra_backend_segment_properties", v.intra_backend_segment_properties_);
    ar << make_nvp("archetype_family_properties", v.archetype_family_properties_);
    ar << make_nvp("force_backend_directory", v.force_backend_directory_);
    ar << make_nvp("disable_facet_directories", v.disable_facet_directories_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::modeling::meta_model::locator_properties& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("directory_structure_style", v.directory_structure_style_);
    ar >> make_nvp("name_separator", v.name_separator_);
    ar >> make_nvp("model_segment_properties", v.model_segment_properties_);
    ar >> make_nvp("intra_backend_segment_properties", v.intra_backend_segment_properties_);
    ar >> make_nvp("archetype_family_properties", v.archetype_family_properties_);
    ar >> make_nvp("force_backend_directory", v.force_backend_directory_);
    ar >> make_nvp("disable_facet_directories", v.disable_facet_directories_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::modeling::meta_model::locator_properties& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::modeling::meta_model::locator_properties& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::modeling::meta_model::locator_properties& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::modeling::meta_model::locator_properties& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::modeling::meta_model::locator_properties& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::modeling::meta_model::locator_properties& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::modeling::meta_model::locator_properties& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::modeling::meta_model::locator_properties& v, unsigned int version);

} }
