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
      enable_unique_file_names_(static_cast<bool>(0)) { }

project_path_properties::project_path_properties(
    const std::string& include_directory_name,
    const std::string& source_directory_name,
    const bool disable_facet_directories,
    const std::string& header_file_extension,
    const std::string& implementation_file_extension,
    const std::string& backend_directory_name,
    const std::string& tests_directory_name,
    const std::string& templates_directory_name,
    const std::string& templates_file_extension,
    const bool enable_unique_file_names)
    : include_directory_name_(include_directory_name),
      source_directory_name_(source_directory_name),
      disable_facet_directories_(disable_facet_directories),
      header_file_extension_(header_file_extension),
      implementation_file_extension_(implementation_file_extension),
      backend_directory_name_(backend_directory_name),
      tests_directory_name_(tests_directory_name),
      templates_directory_name_(templates_directory_name),
      templates_file_extension_(templates_file_extension),
      enable_unique_file_names_(enable_unique_file_names) { }

void project_path_properties::swap(project_path_properties& other) noexcept {
    using std::swap;
    swap(include_directory_name_, other.include_directory_name_);
    swap(source_directory_name_, other.source_directory_name_);
    swap(disable_facet_directories_, other.disable_facet_directories_);
    swap(header_file_extension_, other.header_file_extension_);
    swap(implementation_file_extension_, other.implementation_file_extension_);
    swap(backend_directory_name_, other.backend_directory_name_);
    swap(tests_directory_name_, other.tests_directory_name_);
    swap(templates_directory_name_, other.templates_directory_name_);
    swap(templates_file_extension_, other.templates_file_extension_);
    swap(enable_unique_file_names_, other.enable_unique_file_names_);
}

bool project_path_properties::operator==(const project_path_properties& rhs) const {
    return include_directory_name_ == rhs.include_directory_name_ &&
        source_directory_name_ == rhs.source_directory_name_ &&
        disable_facet_directories_ == rhs.disable_facet_directories_ &&
        header_file_extension_ == rhs.header_file_extension_ &&
        implementation_file_extension_ == rhs.implementation_file_extension_ &&
        backend_directory_name_ == rhs.backend_directory_name_ &&
        tests_directory_name_ == rhs.tests_directory_name_ &&
        templates_directory_name_ == rhs.templates_directory_name_ &&
        templates_file_extension_ == rhs.templates_file_extension_ &&
        enable_unique_file_names_ == rhs.enable_unique_file_names_;
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

const std::string& project_path_properties::backend_directory_name() const {
    return backend_directory_name_;
}

std::string& project_path_properties::backend_directory_name() {
    return backend_directory_name_;
}

void project_path_properties::backend_directory_name(const std::string& v) {
    backend_directory_name_ = v;
}

void project_path_properties::backend_directory_name(const std::string&& v) {
    backend_directory_name_ = std::move(v);
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

}
