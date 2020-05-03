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
#include "dogen.text.csharp/types/formattables/locator_configuration.hpp"

namespace dogen::text::csharp::formattables {

locator_configuration::locator_configuration()
    : disable_facet_directories_(static_cast<bool>(0)) { }

locator_configuration::locator_configuration(
    const std::unordered_map<std::string, dogen::text::csharp::formattables::locator_facet_configuration>& facet_configurations,
    const std::unordered_map<std::string, dogen::text::csharp::formattables::locator_archetype_configuration>& archetype_configurations,
    const bool disable_facet_directories,
    const std::string& backend_directory_name)
    : facet_configurations_(facet_configurations),
      archetype_configurations_(archetype_configurations),
      disable_facet_directories_(disable_facet_directories),
      backend_directory_name_(backend_directory_name) { }

void locator_configuration::swap(locator_configuration& other) noexcept {
    using std::swap;
    swap(facet_configurations_, other.facet_configurations_);
    swap(archetype_configurations_, other.archetype_configurations_);
    swap(disable_facet_directories_, other.disable_facet_directories_);
    swap(backend_directory_name_, other.backend_directory_name_);
}

bool locator_configuration::operator==(const locator_configuration& rhs) const {
    return facet_configurations_ == rhs.facet_configurations_ &&
        archetype_configurations_ == rhs.archetype_configurations_ &&
        disable_facet_directories_ == rhs.disable_facet_directories_ &&
        backend_directory_name_ == rhs.backend_directory_name_;
}

locator_configuration& locator_configuration::operator=(locator_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::text::csharp::formattables::locator_facet_configuration>& locator_configuration::facet_configurations() const {
    return facet_configurations_;
}

std::unordered_map<std::string, dogen::text::csharp::formattables::locator_facet_configuration>& locator_configuration::facet_configurations() {
    return facet_configurations_;
}

void locator_configuration::facet_configurations(const std::unordered_map<std::string, dogen::text::csharp::formattables::locator_facet_configuration>& v) {
    facet_configurations_ = v;
}

void locator_configuration::facet_configurations(const std::unordered_map<std::string, dogen::text::csharp::formattables::locator_facet_configuration>&& v) {
    facet_configurations_ = std::move(v);
}

const std::unordered_map<std::string, dogen::text::csharp::formattables::locator_archetype_configuration>& locator_configuration::archetype_configurations() const {
    return archetype_configurations_;
}

std::unordered_map<std::string, dogen::text::csharp::formattables::locator_archetype_configuration>& locator_configuration::archetype_configurations() {
    return archetype_configurations_;
}

void locator_configuration::archetype_configurations(const std::unordered_map<std::string, dogen::text::csharp::formattables::locator_archetype_configuration>& v) {
    archetype_configurations_ = v;
}

void locator_configuration::archetype_configurations(const std::unordered_map<std::string, dogen::text::csharp::formattables::locator_archetype_configuration>&& v) {
    archetype_configurations_ = std::move(v);
}

bool locator_configuration::disable_facet_directories() const {
    return disable_facet_directories_;
}

void locator_configuration::disable_facet_directories(const bool v) {
    disable_facet_directories_ = v;
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

}
