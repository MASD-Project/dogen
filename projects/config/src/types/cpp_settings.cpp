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
#include "dogen/config/types/cpp_settings.hpp"

namespace dogen {
namespace config {

cpp_settings::cpp_settings()
    : verbose_(static_cast<bool>(0)),
      split_project_(static_cast<bool>(0)),
      disable_backend_(static_cast<bool>(0)),
      disable_cmakelists_(static_cast<bool>(0)),
      disable_complete_constructor_(static_cast<bool>(0)),
      disable_facet_includers_(static_cast<bool>(0)),
      disable_facet_folders_(static_cast<bool>(0)),
      disable_unique_file_names_(static_cast<bool>(0)),
      disable_xml_serialization_(static_cast<bool>(0)),
      use_integrated_io_(static_cast<bool>(0)),
      disable_versioning_(static_cast<bool>(0)) { }

cpp_settings::cpp_settings(cpp_settings&& rhs)
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
      disable_complete_constructor_(std::move(rhs.disable_complete_constructor_)),
      disable_facet_includers_(std::move(rhs.disable_facet_includers_)),
      disable_facet_folders_(std::move(rhs.disable_facet_folders_)),
      disable_unique_file_names_(std::move(rhs.disable_unique_file_names_)),
      domain_facet_folder_(std::move(rhs.domain_facet_folder_)),
      hash_facet_folder_(std::move(rhs.hash_facet_folder_)),
      io_facet_folder_(std::move(rhs.io_facet_folder_)),
      serialization_facet_folder_(std::move(rhs.serialization_facet_folder_)),
      test_data_facet_folder_(std::move(rhs.test_data_facet_folder_)),
      odb_facet_folder_(std::move(rhs.odb_facet_folder_)),
      disable_xml_serialization_(std::move(rhs.disable_xml_serialization_)),
      use_integrated_io_(std::move(rhs.use_integrated_io_)),
      disable_versioning_(std::move(rhs.disable_versioning_)) { }

cpp_settings::cpp_settings(
    const bool verbose,
    const bool split_project,
    const boost::filesystem::path& project_directory,
    const boost::filesystem::path& source_directory,
    const boost::filesystem::path& include_directory,
    const bool disable_backend,
    const bool disable_cmakelists,
    const std::set<dogen::config::cpp_facet_types>& enabled_facets,
    const std::string& header_extension,
    const std::string& source_extension,
    const bool disable_complete_constructor,
    const bool disable_facet_includers,
    const bool disable_facet_folders,
    const bool disable_unique_file_names,
    const std::string& domain_facet_folder,
    const std::string& hash_facet_folder,
    const std::string& io_facet_folder,
    const std::string& serialization_facet_folder,
    const std::string& test_data_facet_folder,
    const std::string& odb_facet_folder,
    const bool disable_xml_serialization,
    const bool use_integrated_io,
    const bool disable_versioning)
    : verbose_(verbose),
      split_project_(split_project),
      project_directory_(project_directory),
      source_directory_(source_directory),
      include_directory_(include_directory),
      disable_backend_(disable_backend),
      disable_cmakelists_(disable_cmakelists),
      enabled_facets_(enabled_facets),
      header_extension_(header_extension),
      source_extension_(source_extension),
      disable_complete_constructor_(disable_complete_constructor),
      disable_facet_includers_(disable_facet_includers),
      disable_facet_folders_(disable_facet_folders),
      disable_unique_file_names_(disable_unique_file_names),
      domain_facet_folder_(domain_facet_folder),
      hash_facet_folder_(hash_facet_folder),
      io_facet_folder_(io_facet_folder),
      serialization_facet_folder_(serialization_facet_folder),
      test_data_facet_folder_(test_data_facet_folder),
      odb_facet_folder_(odb_facet_folder),
      disable_xml_serialization_(disable_xml_serialization),
      use_integrated_io_(use_integrated_io),
      disable_versioning_(disable_versioning) { }

void cpp_settings::swap(cpp_settings& other) noexcept {
    using std::swap;
    swap(verbose_, other.verbose_);
    swap(split_project_, other.split_project_);
    swap(project_directory_, other.project_directory_);
    swap(source_directory_, other.source_directory_);
    swap(include_directory_, other.include_directory_);
    swap(disable_backend_, other.disable_backend_);
    swap(disable_cmakelists_, other.disable_cmakelists_);
    swap(enabled_facets_, other.enabled_facets_);
    swap(header_extension_, other.header_extension_);
    swap(source_extension_, other.source_extension_);
    swap(disable_complete_constructor_, other.disable_complete_constructor_);
    swap(disable_facet_includers_, other.disable_facet_includers_);
    swap(disable_facet_folders_, other.disable_facet_folders_);
    swap(disable_unique_file_names_, other.disable_unique_file_names_);
    swap(domain_facet_folder_, other.domain_facet_folder_);
    swap(hash_facet_folder_, other.hash_facet_folder_);
    swap(io_facet_folder_, other.io_facet_folder_);
    swap(serialization_facet_folder_, other.serialization_facet_folder_);
    swap(test_data_facet_folder_, other.test_data_facet_folder_);
    swap(odb_facet_folder_, other.odb_facet_folder_);
    swap(disable_xml_serialization_, other.disable_xml_serialization_);
    swap(use_integrated_io_, other.use_integrated_io_);
    swap(disable_versioning_, other.disable_versioning_);
}

bool cpp_settings::operator==(const cpp_settings& rhs) const {
    return verbose_ == rhs.verbose_ &&
        split_project_ == rhs.split_project_ &&
        project_directory_ == rhs.project_directory_ &&
        source_directory_ == rhs.source_directory_ &&
        include_directory_ == rhs.include_directory_ &&
        disable_backend_ == rhs.disable_backend_ &&
        disable_cmakelists_ == rhs.disable_cmakelists_ &&
        enabled_facets_ == rhs.enabled_facets_ &&
        header_extension_ == rhs.header_extension_ &&
        source_extension_ == rhs.source_extension_ &&
        disable_complete_constructor_ == rhs.disable_complete_constructor_ &&
        disable_facet_includers_ == rhs.disable_facet_includers_ &&
        disable_facet_folders_ == rhs.disable_facet_folders_ &&
        disable_unique_file_names_ == rhs.disable_unique_file_names_ &&
        domain_facet_folder_ == rhs.domain_facet_folder_ &&
        hash_facet_folder_ == rhs.hash_facet_folder_ &&
        io_facet_folder_ == rhs.io_facet_folder_ &&
        serialization_facet_folder_ == rhs.serialization_facet_folder_ &&
        test_data_facet_folder_ == rhs.test_data_facet_folder_ &&
        odb_facet_folder_ == rhs.odb_facet_folder_ &&
        disable_xml_serialization_ == rhs.disable_xml_serialization_ &&
        use_integrated_io_ == rhs.use_integrated_io_ &&
        disable_versioning_ == rhs.disable_versioning_;
}

cpp_settings& cpp_settings::operator=(cpp_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_settings::verbose() const {
    return verbose_;
}

void cpp_settings::verbose(const bool v) {
    verbose_ = v;
}

bool cpp_settings::split_project() const {
    return split_project_;
}

void cpp_settings::split_project(const bool v) {
    split_project_ = v;
}

const boost::filesystem::path& cpp_settings::project_directory() const {
    return project_directory_;
}

boost::filesystem::path& cpp_settings::project_directory() {
    return project_directory_;
}

void cpp_settings::project_directory(const boost::filesystem::path& v) {
    project_directory_ = v;
}

void cpp_settings::project_directory(const boost::filesystem::path&& v) {
    project_directory_ = std::move(v);
}

const boost::filesystem::path& cpp_settings::source_directory() const {
    return source_directory_;
}

boost::filesystem::path& cpp_settings::source_directory() {
    return source_directory_;
}

void cpp_settings::source_directory(const boost::filesystem::path& v) {
    source_directory_ = v;
}

void cpp_settings::source_directory(const boost::filesystem::path&& v) {
    source_directory_ = std::move(v);
}

const boost::filesystem::path& cpp_settings::include_directory() const {
    return include_directory_;
}

boost::filesystem::path& cpp_settings::include_directory() {
    return include_directory_;
}

void cpp_settings::include_directory(const boost::filesystem::path& v) {
    include_directory_ = v;
}

void cpp_settings::include_directory(const boost::filesystem::path&& v) {
    include_directory_ = std::move(v);
}

bool cpp_settings::disable_backend() const {
    return disable_backend_;
}

void cpp_settings::disable_backend(const bool v) {
    disable_backend_ = v;
}

bool cpp_settings::disable_cmakelists() const {
    return disable_cmakelists_;
}

void cpp_settings::disable_cmakelists(const bool v) {
    disable_cmakelists_ = v;
}

const std::set<dogen::config::cpp_facet_types>& cpp_settings::enabled_facets() const {
    return enabled_facets_;
}

std::set<dogen::config::cpp_facet_types>& cpp_settings::enabled_facets() {
    return enabled_facets_;
}

void cpp_settings::enabled_facets(const std::set<dogen::config::cpp_facet_types>& v) {
    enabled_facets_ = v;
}

void cpp_settings::enabled_facets(const std::set<dogen::config::cpp_facet_types>&& v) {
    enabled_facets_ = std::move(v);
}

const std::string& cpp_settings::header_extension() const {
    return header_extension_;
}

std::string& cpp_settings::header_extension() {
    return header_extension_;
}

void cpp_settings::header_extension(const std::string& v) {
    header_extension_ = v;
}

void cpp_settings::header_extension(const std::string&& v) {
    header_extension_ = std::move(v);
}

const std::string& cpp_settings::source_extension() const {
    return source_extension_;
}

std::string& cpp_settings::source_extension() {
    return source_extension_;
}

void cpp_settings::source_extension(const std::string& v) {
    source_extension_ = v;
}

void cpp_settings::source_extension(const std::string&& v) {
    source_extension_ = std::move(v);
}

bool cpp_settings::disable_complete_constructor() const {
    return disable_complete_constructor_;
}

void cpp_settings::disable_complete_constructor(const bool v) {
    disable_complete_constructor_ = v;
}

bool cpp_settings::disable_facet_includers() const {
    return disable_facet_includers_;
}

void cpp_settings::disable_facet_includers(const bool v) {
    disable_facet_includers_ = v;
}

bool cpp_settings::disable_facet_folders() const {
    return disable_facet_folders_;
}

void cpp_settings::disable_facet_folders(const bool v) {
    disable_facet_folders_ = v;
}

bool cpp_settings::disable_unique_file_names() const {
    return disable_unique_file_names_;
}

void cpp_settings::disable_unique_file_names(const bool v) {
    disable_unique_file_names_ = v;
}

const std::string& cpp_settings::domain_facet_folder() const {
    return domain_facet_folder_;
}

std::string& cpp_settings::domain_facet_folder() {
    return domain_facet_folder_;
}

void cpp_settings::domain_facet_folder(const std::string& v) {
    domain_facet_folder_ = v;
}

void cpp_settings::domain_facet_folder(const std::string&& v) {
    domain_facet_folder_ = std::move(v);
}

const std::string& cpp_settings::hash_facet_folder() const {
    return hash_facet_folder_;
}

std::string& cpp_settings::hash_facet_folder() {
    return hash_facet_folder_;
}

void cpp_settings::hash_facet_folder(const std::string& v) {
    hash_facet_folder_ = v;
}

void cpp_settings::hash_facet_folder(const std::string&& v) {
    hash_facet_folder_ = std::move(v);
}

const std::string& cpp_settings::io_facet_folder() const {
    return io_facet_folder_;
}

std::string& cpp_settings::io_facet_folder() {
    return io_facet_folder_;
}

void cpp_settings::io_facet_folder(const std::string& v) {
    io_facet_folder_ = v;
}

void cpp_settings::io_facet_folder(const std::string&& v) {
    io_facet_folder_ = std::move(v);
}

const std::string& cpp_settings::serialization_facet_folder() const {
    return serialization_facet_folder_;
}

std::string& cpp_settings::serialization_facet_folder() {
    return serialization_facet_folder_;
}

void cpp_settings::serialization_facet_folder(const std::string& v) {
    serialization_facet_folder_ = v;
}

void cpp_settings::serialization_facet_folder(const std::string&& v) {
    serialization_facet_folder_ = std::move(v);
}

const std::string& cpp_settings::test_data_facet_folder() const {
    return test_data_facet_folder_;
}

std::string& cpp_settings::test_data_facet_folder() {
    return test_data_facet_folder_;
}

void cpp_settings::test_data_facet_folder(const std::string& v) {
    test_data_facet_folder_ = v;
}

void cpp_settings::test_data_facet_folder(const std::string&& v) {
    test_data_facet_folder_ = std::move(v);
}

const std::string& cpp_settings::odb_facet_folder() const {
    return odb_facet_folder_;
}

std::string& cpp_settings::odb_facet_folder() {
    return odb_facet_folder_;
}

void cpp_settings::odb_facet_folder(const std::string& v) {
    odb_facet_folder_ = v;
}

void cpp_settings::odb_facet_folder(const std::string&& v) {
    odb_facet_folder_ = std::move(v);
}

bool cpp_settings::disable_xml_serialization() const {
    return disable_xml_serialization_;
}

void cpp_settings::disable_xml_serialization(const bool v) {
    disable_xml_serialization_ = v;
}

bool cpp_settings::use_integrated_io() const {
    return use_integrated_io_;
}

void cpp_settings::use_integrated_io(const bool v) {
    use_integrated_io_ = v;
}

bool cpp_settings::disable_versioning() const {
    return disable_versioning_;
}

void cpp_settings::disable_versioning(const bool v) {
    disable_versioning_ = v;
}

} }