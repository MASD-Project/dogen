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
#include "dogen/formatters/serialization/code_generation_marker_property_sheet_ser.hpp"
#include "dogen/formatters/serialization/general_property_sheet_ser.hpp"


namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::formatters::general_property_sheet& v,
    const unsigned int /*version*/) {
    ar << make_nvp("enabled", v.enabled_);
    ar << make_nvp("generate_preamble", v.generate_preamble_);
    ar << make_nvp("copyright", v.copyright_);
    ar << make_nvp("licence_name", v.licence_name_);
    ar << make_nvp("modeline_group_name", v.modeline_group_name_);
    ar << make_nvp("code_generation_marker", v.code_generation_marker_);
    ar << make_nvp("feature_directory_name", v.feature_directory_name_);
    ar << make_nvp("enable_facet_directories", v.enable_facet_directories_);
    ar << make_nvp("facet_directory_name", v.facet_directory_name_);
    ar << make_nvp("facet_postfix", v.facet_postfix_);
    ar << make_nvp("overwrite", v.overwrite_);
    ar << make_nvp("file_name", v.file_name_);
    ar << make_nvp("file_postfix", v.file_postfix_);
    ar << make_nvp("extension", v.extension_);
    ar << make_nvp("enable_unique_file_names", v.enable_unique_file_names_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::formatters::general_property_sheet& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("enabled", v.enabled_);
    ar >> make_nvp("generate_preamble", v.generate_preamble_);
    ar >> make_nvp("copyright", v.copyright_);
    ar >> make_nvp("licence_name", v.licence_name_);
    ar >> make_nvp("modeline_group_name", v.modeline_group_name_);
    ar >> make_nvp("code_generation_marker", v.code_generation_marker_);
    ar >> make_nvp("feature_directory_name", v.feature_directory_name_);
    ar >> make_nvp("enable_facet_directories", v.enable_facet_directories_);
    ar >> make_nvp("facet_directory_name", v.facet_directory_name_);
    ar >> make_nvp("facet_postfix", v.facet_postfix_);
    ar >> make_nvp("overwrite", v.overwrite_);
    ar >> make_nvp("file_name", v.file_name_);
    ar >> make_nvp("file_postfix", v.file_postfix_);
    ar >> make_nvp("extension", v.extension_);
    ar >> make_nvp("enable_unique_file_names", v.enable_unique_file_names_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::formatters::general_property_sheet& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::formatters::general_property_sheet& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::formatters::general_property_sheet& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::formatters::general_property_sheet& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::formatters::general_property_sheet& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::formatters::general_property_sheet& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::formatters::general_property_sheet& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::formatters::general_property_sheet& v, unsigned int version);

} }