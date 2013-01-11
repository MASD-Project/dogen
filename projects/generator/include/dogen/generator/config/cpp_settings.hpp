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
#ifndef DOGEN_GENERATOR_CONFIG_CPP_SETTINGS_HPP
#define DOGEN_GENERATOR_CONFIG_CPP_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/backends/cpp/cpp_facet_types.hpp"

namespace dogen {
namespace generator {
namespace config {

class cpp_settings {
public:
    cpp_settings(const cpp_settings&) = default;
    ~cpp_settings() = default;
    cpp_settings& operator=(const cpp_settings&) = default;

public:
    cpp_settings() :
        verbose_(false),
        split_project_(false),
        disable_backend_(false),
        disable_cmakelists_(false),
        disable_complete_constructor_(false),
        disable_facet_includers_(false),
        disable_facet_folders_(false),
        disable_unique_file_names_(false),
        disable_xml_serialization_(false),
        use_integrated_io_(false),
        disable_versioning_(false) { }

    cpp_settings(cpp_settings&& rhs)
    : verbose_(std::move(rhs.verbose_)),
      split_project_(std::move(rhs.split_project_)),
      project_directory_(std::move(rhs.project_directory_)),
      source_directory_(std::move(rhs.source_directory_)),
      include_directory_(std::move(rhs.include_directory_)),
      disable_backend_(std::move(rhs.disable_backend_)),
      disable_cmakelists_(std::move(rhs.disable_cmakelists_)),
      enabled_facets_(std::move(rhs.enabled_facets_)),
      header_extension_(std::move(rhs.header_extension_)),
      source_extension_(std::move(rhs.source_extension_)),
      disable_complete_constructor_(
          std::move(rhs.disable_complete_constructor_)),
      disable_facet_includers_(std::move(rhs.disable_facet_includers_)),
      disable_facet_folders_(std::move(rhs.disable_facet_folders_)),
      disable_unique_file_names_(std::move(rhs.disable_unique_file_names_)),
      domain_facet_folder_(std::move(rhs.domain_facet_folder_)),
      hash_facet_folder_(std::move(rhs.hash_facet_folder_)),
      io_facet_folder_(std::move(rhs.io_facet_folder_)),
      serialization_facet_folder_(std::move(rhs.serialization_facet_folder_)),
      test_data_facet_folder_(std::move(rhs.test_data_facet_folder_)),
      disable_xml_serialization_(std::move(rhs.disable_xml_serialization_)),
      use_integrated_io_(std::move(rhs.use_integrated_io_)),
      disable_versioning_(std::move(rhs.disable_versioning_)) { }

public:
    /**
     * @brief Print additional diagnostic information to standard output.
     */
    /**@{*/
    bool verbose() const { return verbose_; }
    cpp_settings& verbose(bool value) {
        verbose_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief If true, project is split into source and include
     * directories, both configurable.
     *
     * If false, there is only a single top-level directory for the
     * entire project, containing as sub-directories both the source
     * and include directories.
     */
    /**@{*/
    bool split_project() const { return split_project_; }
    cpp_settings& split_project(bool value) {
        split_project_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Directory in which to place all of the C++ code.
     *
     * Implies project splitting is off.
     */
    /**@{*/
    boost::filesystem::path project_directory() const {
        return project_directory_;
    }
    cpp_settings& project_directory(boost::filesystem::path value) {
        project_directory_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Directory in which to place the C++ implementation
     * files.
     *
     * Can only be supplied if split project is set to true.
     */
    /**@{*/
    boost::filesystem::path source_directory() const {
        return source_directory_;
    }
    cpp_settings& source_directory(boost::filesystem::path value) {
        source_directory_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Directory in which to place the C++ header files.
     *
     * Can only be supplied if split project is set to true.
     */
    /**@{*/
    boost::filesystem::path include_directory() const {
        return include_directory_;
    }
    cpp_settings& include_directory(boost::filesystem::path value) {
        include_directory_ = value;
        return *this;
    }
    /**@}*/

    /**
     * @brief Disable the C++ backend entirely.
     */
    /**@{*/
    bool disable_backend() const { return disable_backend_; }
    cpp_settings& disable_backend(bool value) {
        disable_backend_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Do not generate CMakeLists.txt for C++ projects.
     */
    /**@{*/
    bool disable_cmakelists() const { return disable_cmakelists_; }
    cpp_settings& disable_cmakelists(bool value) {
        disable_cmakelists_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief C++ facets for which to generate code.
     */
    /**@{*/
    typedef backends::cpp::cpp_facet_types cpp_facet_types;
    std::set<cpp_facet_types> enabled_facets() const {
        return enabled_facets_;
    }
    cpp_settings& enabled_facets(std::set<cpp_facet_types> value) {
        enabled_facets_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Extension to use for C++ header files.
     */
    /**@{*/
    std::string header_extension() const { return header_extension_; }
    cpp_settings& header_extension(std::string value) {
        header_extension_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Extension to use for C++ source files.
     */
    /**@{*/
    std::string source_extension() const { return source_extension_; }
    cpp_settings& source_extension(std::string value) {
        source_extension_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Do not generate a constructor that takes as arguments as
     * member variables.
     */
    /**@{*/
    bool disable_complete_constructor() const {
        return disable_complete_constructor_;
    }
    cpp_settings& disable_complete_constructor(bool value) {
        disable_complete_constructor_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Do not create a global header file that includes all
     * header files in that facet.
     */
    /**@{*/
    bool disable_facet_includers() const { return disable_facet_includers_; }
    cpp_settings& disable_facet_includers(bool value) {
        disable_facet_includers_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Do not create individual folders for each facet.
     *
     * Instead put all the files in one folder.
     */
    /**@{*/
    bool disable_facet_folders() const { return disable_facet_folders_; }
    cpp_settings& disable_facet_folders(bool value) {
        disable_facet_folders_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Do not generate unique file names for each facet.
     *
     * All file names will use the domain object name.
     */
    /**@{*/
    bool disable_unique_file_names() const {
        return disable_unique_file_names_;
    }
    cpp_settings& disable_unique_file_names(bool value) {
        disable_unique_file_names_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Name of the folder to house domain object code.
     */
    /**@{*/
    std::string domain_facet_folder() const { return domain_facet_folder_; }
    cpp_settings& domain_facet_folder(std::string value) {
        domain_facet_folder_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Name of the folder to house hashing code.
     */
    /**@{*/
    std::string hash_facet_folder() const { return hash_facet_folder_; }
    cpp_settings& hash_facet_folder(std::string value) {
        hash_facet_folder_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Name of the folder to house IO (streaming) code.
     */
    /**@{*/
    std::string io_facet_folder() const { return io_facet_folder_; }
    cpp_settings& io_facet_folder(std::string value) {
        io_facet_folder_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Name of the folder to house boost serialisation code.
     */
    /**@{*/
    std::string serialization_facet_folder() const {
        return serialization_facet_folder_;
    }
    cpp_settings& serialization_facet_folder(std::string value) {
        serialization_facet_folder_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Name of the folder to house test data generators.
     */
    /**@{*/
    std::string test_data_facet_folder() const {
        return test_data_facet_folder_;
    }
    cpp_settings& test_data_facet_folder(std::string value) {
        test_data_facet_folder_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Do not use NVP macros in serialisation code.
     *
     * This has the effect of disabling support for boost XML archives.
     */
    /**@{*/
    bool disable_xml_serialization() const {
        return disable_xml_serialization_;
    }
    cpp_settings& disable_xml_serialization(bool value) {
        disable_xml_serialization_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief Generate the streaming operators directly in the domain
     * class.
     */
    /**@{*/
    bool use_integrated_io() const { return use_integrated_io_; }
    cpp_settings& use_integrated_io(bool value) {
        use_integrated_io_ = value;
        return *this;
    }
    /**@*/

    /**
     * @brief If false, add versioning code to domain entities; if
     * true, no versioning code is added.
     */
    /**@{*/
    bool disable_versioning() const { return disable_versioning_; }
    cpp_settings& disable_versioning(bool value) {
        disable_versioning_ = value;
        return *this;
    }
    /**@}*/

private:
    bool verbose_;
    bool split_project_;
    boost::filesystem::path project_directory_;
    boost::filesystem::path source_directory_;
    boost::filesystem::path include_directory_;
    bool disable_backend_;
    bool disable_cmakelists_;

    std::set<cpp_facet_types> enabled_facets_;
    std::string header_extension_;
    std::string source_extension_;
    bool disable_complete_constructor_;
    bool disable_facet_includers_;
    bool disable_facet_folders_;
    bool disable_unique_file_names_;
    std::string domain_facet_folder_;
    std::string hash_facet_folder_;
    std::string io_facet_folder_;
    std::string serialization_facet_folder_;
    std::string test_data_facet_folder_;
    bool disable_xml_serialization_;
    bool use_integrated_io_;
    bool disable_versioning_;
};

std::ostream& operator<<(std::ostream& stream, cpp_settings value);

} } }

#endif
