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
#include "dogen/config/types/cpp_options.hpp"

namespace dogen {
namespace config {

cpp_options::cpp_options()
    : split_project_(static_cast<bool>(0)),
      disable_backend_(static_cast<bool>(0)),
      disable_cmakelists_(static_cast<bool>(0)),
      disable_complete_constructor_(static_cast<bool>(0)),
      disable_facet_includers_(static_cast<bool>(0)),
      disable_facet_folders_(static_cast<bool>(0)),
      disable_unique_file_names_(static_cast<bool>(0)),
      disable_xml_serialization_(static_cast<bool>(0)),
      use_integrated_io_(static_cast<bool>(0)),
      disable_eos_serialization_(static_cast<bool>(0)) { }

cpp_options::cpp_options(cpp_options&& rhs)
    : split_project_(std::move(rhs.split_project_)),
      project_directory_path_(std::move(rhs.project_directory_path_)),
      source_directory_path_(std::move(rhs.source_directory_path_)),
      include_directory_path_(std::move(rhs.include_directory_path_)),
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
      disable_eos_serialization_(std::move(rhs.disable_eos_serialization_)) { }

cpp_options::cpp_options(
    const bool split_project,
    const boost::filesystem::path& project_directory_path,
    const boost::filesystem::path& source_directory_path,
    const boost::filesystem::path& include_directory_path,
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
    const bool disable_eos_serialization)
    : split_project_(split_project),
      project_directory_path_(project_directory_path),
      source_directory_path_(source_directory_path),
      include_directory_path_(include_directory_path),
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
      disable_eos_serialization_(disable_eos_serialization) { }

void cpp_options::swap(cpp_options& other) noexcept {
    using std::swap;
    swap(split_project_, other.split_project_);
    swap(project_directory_path_, other.project_directory_path_);
    swap(source_directory_path_, other.source_directory_path_);
    swap(include_directory_path_, other.include_directory_path_);
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
    swap(disable_eos_serialization_, other.disable_eos_serialization_);
}

bool cpp_options::operator==(const cpp_options& rhs) const {
    return split_project_ == rhs.split_project_ &&
        project_directory_path_ == rhs.project_directory_path_ &&
        source_directory_path_ == rhs.source_directory_path_ &&
        include_directory_path_ == rhs.include_directory_path_ &&
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
        disable_eos_serialization_ == rhs.disable_eos_serialization_;
}

cpp_options& cpp_options::operator=(cpp_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_options::split_project() const {
    return split_project_;
}

void cpp_options::split_project(const bool v) {
    split_project_ = v;
}

const boost::filesystem::path& cpp_options::project_directory_path() const {
    return project_directory_path_;
}

boost::filesystem::path& cpp_options::project_directory_path() {
    return project_directory_path_;
}

void cpp_options::project_directory_path(const boost::filesystem::path& v) {
    project_directory_path_ = v;
}

void cpp_options::project_directory_path(const boost::filesystem::path&& v) {
    project_directory_path_ = std::move(v);
}

const boost::filesystem::path& cpp_options::source_directory_path() const {
    return source_directory_path_;
}

boost::filesystem::path& cpp_options::source_directory_path() {
    return source_directory_path_;
}

void cpp_options::source_directory_path(const boost::filesystem::path& v) {
    source_directory_path_ = v;
}

void cpp_options::source_directory_path(const boost::filesystem::path&& v) {
    source_directory_path_ = std::move(v);
}

const boost::filesystem::path& cpp_options::include_directory_path() const {
    return include_directory_path_;
}

boost::filesystem::path& cpp_options::include_directory_path() {
    return include_directory_path_;
}

void cpp_options::include_directory_path(const boost::filesystem::path& v) {
    include_directory_path_ = v;
}

void cpp_options::include_directory_path(const boost::filesystem::path&& v) {
    include_directory_path_ = std::move(v);
}

bool cpp_options::disable_backend() const {
    return disable_backend_;
}

void cpp_options::disable_backend(const bool v) {
    disable_backend_ = v;
}

bool cpp_options::disable_cmakelists() const {
    return disable_cmakelists_;
}

void cpp_options::disable_cmakelists(const bool v) {
    disable_cmakelists_ = v;
}

const std::set<dogen::config::cpp_facet_types>& cpp_options::enabled_facets() const {
    return enabled_facets_;
}

std::set<dogen::config::cpp_facet_types>& cpp_options::enabled_facets() {
    return enabled_facets_;
}

void cpp_options::enabled_facets(const std::set<dogen::config::cpp_facet_types>& v) {
    enabled_facets_ = v;
}

void cpp_options::enabled_facets(const std::set<dogen::config::cpp_facet_types>&& v) {
    enabled_facets_ = std::move(v);
}

const std::string& cpp_options::header_extension() const {
    return header_extension_;
}

std::string& cpp_options::header_extension() {
    return header_extension_;
}

void cpp_options::header_extension(const std::string& v) {
    header_extension_ = v;
}

void cpp_options::header_extension(const std::string&& v) {
    header_extension_ = std::move(v);
}

const std::string& cpp_options::source_extension() const {
    return source_extension_;
}

std::string& cpp_options::source_extension() {
    return source_extension_;
}

void cpp_options::source_extension(const std::string& v) {
    source_extension_ = v;
}

void cpp_options::source_extension(const std::string&& v) {
    source_extension_ = std::move(v);
}

bool cpp_options::disable_complete_constructor() const {
    return disable_complete_constructor_;
}

void cpp_options::disable_complete_constructor(const bool v) {
    disable_complete_constructor_ = v;
}

bool cpp_options::disable_facet_includers() const {
    return disable_facet_includers_;
}

void cpp_options::disable_facet_includers(const bool v) {
    disable_facet_includers_ = v;
}

bool cpp_options::disable_facet_folders() const {
    return disable_facet_folders_;
}

void cpp_options::disable_facet_folders(const bool v) {
    disable_facet_folders_ = v;
}

bool cpp_options::disable_unique_file_names() const {
    return disable_unique_file_names_;
}

void cpp_options::disable_unique_file_names(const bool v) {
    disable_unique_file_names_ = v;
}

const std::string& cpp_options::domain_facet_folder() const {
    return domain_facet_folder_;
}

std::string& cpp_options::domain_facet_folder() {
    return domain_facet_folder_;
}

void cpp_options::domain_facet_folder(const std::string& v) {
    domain_facet_folder_ = v;
}

void cpp_options::domain_facet_folder(const std::string&& v) {
    domain_facet_folder_ = std::move(v);
}

const std::string& cpp_options::hash_facet_folder() const {
    return hash_facet_folder_;
}

std::string& cpp_options::hash_facet_folder() {
    return hash_facet_folder_;
}

void cpp_options::hash_facet_folder(const std::string& v) {
    hash_facet_folder_ = v;
}

void cpp_options::hash_facet_folder(const std::string&& v) {
    hash_facet_folder_ = std::move(v);
}

const std::string& cpp_options::io_facet_folder() const {
    return io_facet_folder_;
}

std::string& cpp_options::io_facet_folder() {
    return io_facet_folder_;
}

void cpp_options::io_facet_folder(const std::string& v) {
    io_facet_folder_ = v;
}

void cpp_options::io_facet_folder(const std::string&& v) {
    io_facet_folder_ = std::move(v);
}

const std::string& cpp_options::serialization_facet_folder() const {
    return serialization_facet_folder_;
}

std::string& cpp_options::serialization_facet_folder() {
    return serialization_facet_folder_;
}

void cpp_options::serialization_facet_folder(const std::string& v) {
    serialization_facet_folder_ = v;
}

void cpp_options::serialization_facet_folder(const std::string&& v) {
    serialization_facet_folder_ = std::move(v);
}

const std::string& cpp_options::test_data_facet_folder() const {
    return test_data_facet_folder_;
}

std::string& cpp_options::test_data_facet_folder() {
    return test_data_facet_folder_;
}

void cpp_options::test_data_facet_folder(const std::string& v) {
    test_data_facet_folder_ = v;
}

void cpp_options::test_data_facet_folder(const std::string&& v) {
    test_data_facet_folder_ = std::move(v);
}

const std::string& cpp_options::odb_facet_folder() const {
    return odb_facet_folder_;
}

std::string& cpp_options::odb_facet_folder() {
    return odb_facet_folder_;
}

void cpp_options::odb_facet_folder(const std::string& v) {
    odb_facet_folder_ = v;
}

void cpp_options::odb_facet_folder(const std::string&& v) {
    odb_facet_folder_ = std::move(v);
}

bool cpp_options::disable_xml_serialization() const {
    return disable_xml_serialization_;
}

void cpp_options::disable_xml_serialization(const bool v) {
    disable_xml_serialization_ = v;
}

bool cpp_options::use_integrated_io() const {
    return use_integrated_io_;
}

void cpp_options::use_integrated_io(const bool v) {
    use_integrated_io_ = v;
}

bool cpp_options::disable_eos_serialization() const {
    return disable_eos_serialization_;
}

void cpp_options::disable_eos_serialization(const bool v) {
    disable_eos_serialization_ = v;
}

} }