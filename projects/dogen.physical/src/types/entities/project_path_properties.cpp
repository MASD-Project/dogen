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
#include "dogen.physical/types/entities/project_path_properties.hpp"

namespace dogen::physical::entities {

project_path_properties::project_path_properties()
    : disable_facet_directories_(static_cast<bool>(0)),
      enable_unique_file_names_(static_cast<bool>(0)),
      enable_backend_directories_(static_cast<bool>(0)) { }

project_path_properties::project_path_properties(project_path_properties&& rhs)
    : include_directory_name_(std::move(rhs.include_directory_name_)),
      source_directory_name_(std::move(rhs.source_directory_name_)),
      disable_facet_directories_(std::move(rhs.disable_facet_directories_)),
      header_file_extension_(std::move(rhs.header_file_extension_)),
      implementation_file_extension_(std::move(rhs.implementation_file_extension_)),
      tests_directory_name_(std::move(rhs.tests_directory_name_)),
      templates_directory_name_(std::move(rhs.templates_directory_name_)),
      templates_file_extension_(std::move(rhs.templates_file_extension_)),
      enable_unique_file_names_(std::move(rhs.enable_unique_file_names_)),
      headers_output_directory_(std::move(rhs.headers_output_directory_)),
      enable_backend_directories_(std::move(rhs.enable_backend_directories_)),
      implementation_directory_full_path_(std::move(rhs.implementation_directory_full_path_)) { }

project_path_properties::project_path_properties(
    const std::string& include_directory_name,
    const std::string& source_directory_name,
    const bool disable_facet_directories,
    const std::string& header_file_extension,
    const std::string& implementation_file_extension,
    const std::string& tests_directory_name,
    const std::string& templates_directory_name,
    const std::string& templates_file_extension,
    const bool enable_unique_file_names,
    const std::string& headers_output_directory,
    const bool enable_backend_directories,
    const boost::filesystem::path& implementation_directory_full_path)
    : include_directory_name_(include_directory_name),
      source_directory_name_(source_directory_name),
      disable_facet_directories_(disable_facet_directories),
      header_file_extension_(header_file_extension),
      implementation_file_extension_(implementation_file_extension),
      tests_directory_name_(tests_directory_name),
      templates_directory_name_(templates_directory_name),
      templates_file_extension_(templates_file_extension),
      enable_unique_file_names_(enable_unique_file_names),
      headers_output_directory_(headers_output_directory),
      enable_backend_directories_(enable_backend_directories),
      implementation_directory_full_path_(implementation_directory_full_path) { }

void project_path_properties::swap(project_path_properties& other) noexcept {
    using std::swap;
    swap(include_directory_name_, other.include_directory_name_);
    swap(source_directory_name_, other.source_directory_name_);
    swap(disable_facet_directories_, other.disable_facet_directories_);
    swap(header_file_extension_, other.header_file_extension_);
    swap(implementation_file_extension_, other.implementation_file_extension_);
    swap(tests_directory_name_, other.tests_directory_name_);
    swap(templates_directory_name_, other.templates_directory_name_);
    swap(templates_file_extension_, other.templates_file_extension_);
    swap(enable_unique_file_names_, other.enable_unique_file_names_);
    swap(headers_output_directory_, other.headers_output_directory_);
    swap(enable_backend_directories_, other.enable_backend_directories_);
    swap(implementation_directory_full_path_, other.implementation_directory_full_path_);
}

bool project_path_properties::operator==(const project_path_properties& rhs) const {
    return include_directory_name_ == rhs.include_directory_name_ &&
        source_directory_name_ == rhs.source_directory_name_ &&
        disable_facet_directories_ == rhs.disable_facet_directories_ &&
        header_file_extension_ == rhs.header_file_extension_ &&
        implementation_file_extension_ == rhs.implementation_file_extension_ &&
        tests_directory_name_ == rhs.tests_directory_name_ &&
        templates_directory_name_ == rhs.templates_directory_name_ &&
        templates_file_extension_ == rhs.templates_file_extension_ &&
        enable_unique_file_names_ == rhs.enable_unique_file_names_ &&
        headers_output_directory_ == rhs.headers_output_directory_ &&
        enable_backend_directories_ == rhs.enable_backend_directories_ &&
        implementation_directory_full_path_ == rhs.implementation_directory_full_path_;
}

project_path_properties& project_path_properties::operator=(project_path_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& project_path_properties::include_directory_name() const {
    return include_directory_name_;
}

std::string& project_path_properties::include_directory_name() {
    return include_directory_name_;
}

void project_path_properties::include_directory_name(const std::string& v) {
    include_directory_name_ = v;
}

void project_path_properties::include_directory_name(const std::string&& v) {
    include_directory_name_ = std::move(v);
}

const std::string& project_path_properties::source_directory_name() const {
    return source_directory_name_;
}

std::string& project_path_properties::source_directory_name() {
    return source_directory_name_;
}

void project_path_properties::source_directory_name(const std::string& v) {
    source_directory_name_ = v;
}

void project_path_properties::source_directory_name(const std::string&& v) {
    source_directory_name_ = std::move(v);
}

bool project_path_properties::disable_facet_directories() const {
    return disable_facet_directories_;
}

void project_path_properties::disable_facet_directories(const bool v) {
    disable_facet_directories_ = v;
}

const std::string& project_path_properties::header_file_extension() const {
    return header_file_extension_;
}

std::string& project_path_properties::header_file_extension() {
    return header_file_extension_;
}

void project_path_properties::header_file_extension(const std::string& v) {
    header_file_extension_ = v;
}

void project_path_properties::header_file_extension(const std::string&& v) {
    header_file_extension_ = std::move(v);
}

const std::string& project_path_properties::implementation_file_extension() const {
    return implementation_file_extension_;
}

std::string& project_path_properties::implementation_file_extension() {
    return implementation_file_extension_;
}

void project_path_properties::implementation_file_extension(const std::string& v) {
    implementation_file_extension_ = v;
}

void project_path_properties::implementation_file_extension(const std::string&& v) {
    implementation_file_extension_ = std::move(v);
}

const std::string& project_path_properties::tests_directory_name() const {
    return tests_directory_name_;
}

std::string& project_path_properties::tests_directory_name() {
    return tests_directory_name_;
}

void project_path_properties::tests_directory_name(const std::string& v) {
    tests_directory_name_ = v;
}

void project_path_properties::tests_directory_name(const std::string&& v) {
    tests_directory_name_ = std::move(v);
}

const std::string& project_path_properties::templates_directory_name() const {
    return templates_directory_name_;
}

std::string& project_path_properties::templates_directory_name() {
    return templates_directory_name_;
}

void project_path_properties::templates_directory_name(const std::string& v) {
    templates_directory_name_ = v;
}

void project_path_properties::templates_directory_name(const std::string&& v) {
    templates_directory_name_ = std::move(v);
}

const std::string& project_path_properties::templates_file_extension() const {
    return templates_file_extension_;
}

std::string& project_path_properties::templates_file_extension() {
    return templates_file_extension_;
}

void project_path_properties::templates_file_extension(const std::string& v) {
    templates_file_extension_ = v;
}

void project_path_properties::templates_file_extension(const std::string&& v) {
    templates_file_extension_ = std::move(v);
}

bool project_path_properties::enable_unique_file_names() const {
    return enable_unique_file_names_;
}

void project_path_properties::enable_unique_file_names(const bool v) {
    enable_unique_file_names_ = v;
}

const std::string& project_path_properties::headers_output_directory() const {
    return headers_output_directory_;
}

std::string& project_path_properties::headers_output_directory() {
    return headers_output_directory_;
}

void project_path_properties::headers_output_directory(const std::string& v) {
    headers_output_directory_ = v;
}

void project_path_properties::headers_output_directory(const std::string&& v) {
    headers_output_directory_ = std::move(v);
}

bool project_path_properties::enable_backend_directories() const {
    return enable_backend_directories_;
}

void project_path_properties::enable_backend_directories(const bool v) {
    enable_backend_directories_ = v;
}

const boost::filesystem::path& project_path_properties::implementation_directory_full_path() const {
    return implementation_directory_full_path_;
}

boost::filesystem::path& project_path_properties::implementation_directory_full_path() {
    return implementation_directory_full_path_;
}

void project_path_properties::implementation_directory_full_path(const boost::filesystem::path& v) {
    implementation_directory_full_path_ = v;
}

void project_path_properties::implementation_directory_full_path(const boost::filesystem::path&& v) {
    implementation_directory_full_path_ = std::move(v);
}

}
