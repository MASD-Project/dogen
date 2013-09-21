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
#include <boost/serialization/set.hpp>
#include <boost/serialization/string.hpp>
#include "dogen/config/serialization/cpp_facet_types_ser.hpp"
#include "dogen/config/serialization/cpp_settings_ser.hpp"
#include "dogen/utility/serialization/path.hpp"

#ifdef __linux__
#include "eos/portable_iarchive.hpp"
#include "eos/portable_oarchive.hpp"
#endif

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::config::cpp_settings& v,
    const unsigned int /*version*/) {
    ar << make_nvp("verbose", v.verbose_);
    ar << make_nvp("split_project", v.split_project_);
    ar << make_nvp("project_directory", v.project_directory_.generic_string());
    ar << make_nvp("source_directory", v.source_directory_.generic_string());
    ar << make_nvp("include_directory", v.include_directory_.generic_string());
    ar << make_nvp("disable_backend", v.disable_backend_);
    ar << make_nvp("disable_cmakelists", v.disable_cmakelists_);
    ar << make_nvp("enabled_facets", v.enabled_facets_);
    ar << make_nvp("header_extension", v.header_extension_);
    ar << make_nvp("source_extension", v.source_extension_);
    ar << make_nvp("disable_complete_constructor", v.disable_complete_constructor_);
    ar << make_nvp("disable_facet_includers", v.disable_facet_includers_);
    ar << make_nvp("disable_facet_folders", v.disable_facet_folders_);
    ar << make_nvp("disable_unique_file_names", v.disable_unique_file_names_);
    ar << make_nvp("domain_facet_folder", v.domain_facet_folder_);
    ar << make_nvp("hash_facet_folder", v.hash_facet_folder_);
    ar << make_nvp("io_facet_folder", v.io_facet_folder_);
    ar << make_nvp("serialization_facet_folder", v.serialization_facet_folder_);
    ar << make_nvp("test_data_facet_folder", v.test_data_facet_folder_);
    ar << make_nvp("odb_facet_folder", v.odb_facet_folder_);
    ar << make_nvp("disable_xml_serialization", v.disable_xml_serialization_);
    ar << make_nvp("use_integrated_io", v.use_integrated_io_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::config::cpp_settings& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("verbose", v.verbose_);
    ar >> make_nvp("split_project", v.split_project_);
    std::string project_directory_tmp;
    ar >> make_nvp("project_directory", project_directory_tmp);
    v.project_directory_ = project_directory_tmp;
    std::string source_directory_tmp;
    ar >> make_nvp("source_directory", source_directory_tmp);
    v.source_directory_ = source_directory_tmp;
    std::string include_directory_tmp;
    ar >> make_nvp("include_directory", include_directory_tmp);
    v.include_directory_ = include_directory_tmp;
    ar >> make_nvp("disable_backend", v.disable_backend_);
    ar >> make_nvp("disable_cmakelists", v.disable_cmakelists_);
    ar >> make_nvp("enabled_facets", v.enabled_facets_);
    ar >> make_nvp("header_extension", v.header_extension_);
    ar >> make_nvp("source_extension", v.source_extension_);
    ar >> make_nvp("disable_complete_constructor", v.disable_complete_constructor_);
    ar >> make_nvp("disable_facet_includers", v.disable_facet_includers_);
    ar >> make_nvp("disable_facet_folders", v.disable_facet_folders_);
    ar >> make_nvp("disable_unique_file_names", v.disable_unique_file_names_);
    ar >> make_nvp("domain_facet_folder", v.domain_facet_folder_);
    ar >> make_nvp("hash_facet_folder", v.hash_facet_folder_);
    ar >> make_nvp("io_facet_folder", v.io_facet_folder_);
    ar >> make_nvp("serialization_facet_folder", v.serialization_facet_folder_);
    ar >> make_nvp("test_data_facet_folder", v.test_data_facet_folder_);
    ar >> make_nvp("odb_facet_folder", v.odb_facet_folder_);
    ar >> make_nvp("disable_xml_serialization", v.disable_xml_serialization_);
    ar >> make_nvp("use_integrated_io", v.use_integrated_io_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::config::cpp_settings& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::config::cpp_settings& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::config::cpp_settings& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::config::cpp_settings& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::config::cpp_settings& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::config::cpp_settings& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::config::cpp_settings& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::config::cpp_settings& v, unsigned int version);

#ifdef __linux__
template void save(eos::portable_oarchive& ar, const dogen::config::cpp_settings& v, unsigned int version);
template void load(eos::portable_iarchive& ar, dogen::config::cpp_settings& v, unsigned int version);
#endif

} }