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
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

model::model()
    : is_system_(static_cast<bool>(0)) { }

model::model(
    const std::string& name,
    const std::unordered_map<dogen::sml::qualified_name, dogen::sml::package>& packages,
    const std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod>& pods,
    const std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive>& primitives,
    const std::unordered_map<dogen::sml::qualified_name, dogen::sml::enumeration>& enumerations,
    const std::unordered_map<dogen::sml::qualified_name, dogen::sml::exception>& exceptions,
    const std::list<std::string>& external_package_path,
    const std::string& schema_name,
    const bool is_system,
    const std::unordered_map<std::string, dogen::sml::reference>& dependencies,
    const std::unordered_set<dogen::sml::qualified_name>& leaves)
    : name_(name),
      packages_(packages),
      pods_(pods),
      primitives_(primitives),
      enumerations_(enumerations),
      exceptions_(exceptions),
      external_package_path_(external_package_path),
      schema_name_(schema_name),
      is_system_(is_system),
      dependencies_(dependencies),
      leaves_(leaves) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(packages_, other.packages_);
    swap(pods_, other.pods_);
    swap(primitives_, other.primitives_);
    swap(enumerations_, other.enumerations_);
    swap(exceptions_, other.exceptions_);
    swap(external_package_path_, other.external_package_path_);
    swap(schema_name_, other.schema_name_);
    swap(is_system_, other.is_system_);
    swap(dependencies_, other.dependencies_);
    swap(leaves_, other.leaves_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        packages_ == rhs.packages_ &&
        pods_ == rhs.pods_ &&
        primitives_ == rhs.primitives_ &&
        enumerations_ == rhs.enumerations_ &&
        exceptions_ == rhs.exceptions_ &&
        external_package_path_ == rhs.external_package_path_ &&
        schema_name_ == rhs.schema_name_ &&
        is_system_ == rhs.is_system_ &&
        dependencies_ == rhs.dependencies_ &&
        leaves_ == rhs.leaves_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }