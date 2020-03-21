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
#include "dogen.m2t.cpp/types/formattables/locator_configuration.hpp"

namespace dogen::m2t::cpp::formattables {

locator_configuration::locator_configuration()
    : disable_facet_directories_(static_cast<bool>(0)) { }

locator_configuration::locator_configuration(
    const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>& facet_configurations,
    const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>& archetype_configurations,
    const std::string& include_directory_name,
    const std::string& source_directory_name,
    const bool disable_facet_directories,
    const std::string& header_file_extension,
    const std::string& implementation_file_extension,
    const std::string& backend_directory_name,
    const std::string& tests_directory_name,
    const std::string& templates_directory_name,
    const std::string& templates_file_extension)
    : facet_configurations_(facet_configurations),
      archetype_configurations_(archetype_configurations),
      include_directory_name_(include_directory_name),
      source_directory_name_(source_directory_name),
      disable_facet_directories_(disable_facet_directories),
      header_file_extension_(header_file_extension),
      implementation_file_extension_(implementation_file_extension),
      backend_directory_name_(backend_directory_name),
      tests_directory_name_(tests_directory_name),
      templates_directory_name_(templates_directory_name),
      templates_file_extension_(templates_file_extension) { }

void locator_configuration::swap(locator_configuration& other) noexcept {
    using std::swap;
    swap(facet_configurations_, other.facet_configurations_);
    swap(archetype_configurations_, other.archetype_configurations_);
    swap(include_directory_name_, other.include_directory_name_);
    swap(source_directory_name_, other.source_directory_name_);
    swap(disable_facet_directories_, other.disable_facet_directories_);
    swap(header_file_extension_, other.header_file_extension_);
    swap(implementation_file_extension_, other.implementation_file_extension_);
    swap(backend_directory_name_, other.backend_directory_name_);
    swap(tests_directory_name_, other.tests_directory_name_);
    swap(templates_directory_name_, other.templates_directory_name_);
    swap(templates_file_extension_, other.templates_file_extension_);
}

bool locator_configuration::operator==(const locator_configuration& rhs) const {
    return facet_configurations_ == rhs.facet_configurations_ &&
        archetype_configurations_ == rhs.archetype_configurations_ &&
        include_directory_name_ == rhs.include_directory_name_ &&
        source_directory_name_ == rhs.source_directory_name_ &&
        disable_facet_directories_ == rhs.disable_facet_directories_ &&
        header_file_extension_ == rhs.header_file_extension_ &&
        implementation_file_extension_ == rhs.implementation_file_extension_ &&
        backend_directory_name_ == rhs.backend_directory_name_ &&
        tests_directory_name_ == rhs.tests_directory_name_ &&
        templates_directory_name_ == rhs.templates_directory_name_ &&
        templates_file_extension_ == rhs.templates_file_extension_;
}

locator_configuration& locator_configuration::operator=(locator_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>& locator_configuration::facet_configurations() const {
    return facet_configurations_;
}

std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>& locator_configuration::facet_configurations() {
    return facet_configurations_;
}

void locator_configuration::facet_configurations(const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>& v) {
    facet_configurations_ = v;
}

void locator_configuration::facet_configurations(const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>&& v) {
    facet_configurations_ = std::move(v);
}

const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>& locator_configuration::archetype_configurations() const {
    return archetype_configurations_;
}

std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>& locator_configuration::archetype_configurations() {
    return archetype_configurations_;
}

void locator_configuration::archetype_configurations(const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>& v) {
    archetype_configurations_ = v;
}

void locator_configuration::archetype_configurations(const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>&& v) {
    archetype_configurations_ = std::move(v);
}

const std::string& locator_configuration::include_directory_name() const {
    return include_directory_name_;
}

std::string& locator_configuration::include_directory_name() {
    return include_directory_name_;
}

void locator_configuration::include_directory_name(const std::string& v) {
    include_directory_name_ = v;
}

void locator_configuration::include_directory_name(const std::string&& v) {
    include_directory_name_ = std::move(v);
}

const std::string& locator_configuration::source_directory_name() const {
    return source_directory_name_;
}

std::string& locator_configuration::source_directory_name() {
    return source_directory_name_;
}

void locator_configuration::source_directory_name(const std::string& v) {
    source_directory_name_ = v;
}

void locator_configuration::source_directory_name(const std::string&& v) {
    source_directory_name_ = std::move(v);
}

bool locator_configuration::disable_facet_directories() const {
    return disable_facet_directories_;
}

void locator_configuration::disable_facet_directories(const bool v) {
    disable_facet_directories_ = v;
}

const std::string& locator_configuration::header_file_extension() const {
    return header_file_extension_;
}

std::string& locator_configuration::header_file_extension() {
    return header_file_extension_;
}

void locator_configuration::header_file_extension(const std::string& v) {
    header_file_extension_ = v;
}

void locator_configuration::header_file_extension(const std::string&& v) {
    header_file_extension_ = std::move(v);
}

const std::string& locator_configuration::implementation_file_extension() const {
    return implementation_file_extension_;
}

std::string& locator_configuration::implementation_file_extension() {
    return implementation_file_extension_;
}

void locator_configuration::implementation_file_extension(const std::string& v) {
    implementation_file_extension_ = v;
}

void locator_configuration::implementation_file_extension(const std::string&& v) {
    implementation_file_extension_ = std::move(v);
}

const std::string& locator_configuration::backend_directory_name() const {
    return backend_directory_name_;
}

std::string& locator_configuration::backend_directory_name() {
    return backend_directory_name_;
}

void locator_configuration::backend_directory_name(const std::string& v) {
    backend_directory_name_ = v;
}

void locator_configuration::backend_directory_name(const std::string&& v) {
    backend_directory_name_ = std::move(v);
}

const std::string& locator_configuration::tests_directory_name() const {
    return tests_directory_name_;
}

std::string& locator_configuration::tests_directory_name() {
    return tests_directory_name_;
}

void locator_configuration::tests_directory_name(const std::string& v) {
    tests_directory_name_ = v;
}

void locator_configuration::tests_directory_name(const std::string&& v) {
    tests_directory_name_ = std::move(v);
}

const std::string& locator_configuration::templates_directory_name() const {
    return templates_directory_name_;
}

std::string& locator_configuration::templates_directory_name() {
    return templates_directory_name_;
}

void locator_configuration::templates_directory_name(const std::string& v) {
    templates_directory_name_ = v;
}

void locator_configuration::templates_directory_name(const std::string&& v) {
    templates_directory_name_ = std::move(v);
}

const std::string& locator_configuration::templates_file_extension() const {
    return templates_file_extension_;
}

std::string& locator_configuration::templates_file_extension() {
    return templates_file_extension_;
}

void locator_configuration::templates_file_extension(const std::string& v) {
    templates_file_extension_ = v;
}

void locator_configuration::templates_file_extension(const std::string&& v) {
    templates_file_extension_ = std::move(v);
}

}
