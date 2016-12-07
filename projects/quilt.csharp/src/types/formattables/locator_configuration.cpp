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
#include "dogen/quilt.csharp/types/formattables/locator_configuration.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

locator_configuration::locator_configuration()
    : disable_facet_directories_(static_cast<bool>(0)) { }

locator_configuration::locator_configuration(
    const std::unordered_map<std::string, std::string>& facet_directories,
    const bool disable_facet_directories,
    const std::string& kernel_directory_name)
    : facet_directories_(facet_directories),
      disable_facet_directories_(disable_facet_directories),
      kernel_directory_name_(kernel_directory_name) { }

void locator_configuration::swap(locator_configuration& other) noexcept {
    using std::swap;
    swap(facet_directories_, other.facet_directories_);
    swap(disable_facet_directories_, other.disable_facet_directories_);
    swap(kernel_directory_name_, other.kernel_directory_name_);
}

bool locator_configuration::operator==(const locator_configuration& rhs) const {
    return facet_directories_ == rhs.facet_directories_ &&
        disable_facet_directories_ == rhs.disable_facet_directories_ &&
        kernel_directory_name_ == rhs.kernel_directory_name_;
}

locator_configuration& locator_configuration::operator=(locator_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::string>& locator_configuration::facet_directories() const {
    return facet_directories_;
}

std::unordered_map<std::string, std::string>& locator_configuration::facet_directories() {
    return facet_directories_;
}

void locator_configuration::facet_directories(const std::unordered_map<std::string, std::string>& v) {
    facet_directories_ = v;
}

void locator_configuration::facet_directories(const std::unordered_map<std::string, std::string>&& v) {
    facet_directories_ = std::move(v);
}

bool locator_configuration::disable_facet_directories() const {
    return disable_facet_directories_;
}

void locator_configuration::disable_facet_directories(const bool v) {
    disable_facet_directories_ = v;
}

const std::string& locator_configuration::kernel_directory_name() const {
    return kernel_directory_name_;
}

std::string& locator_configuration::kernel_directory_name() {
    return kernel_directory_name_;
}

void locator_configuration::kernel_directory_name(const std::string& v) {
    kernel_directory_name_ = v;
}

void locator_configuration::kernel_directory_name(const std::string&& v) {
    kernel_directory_name_ = std::move(v);
}

} } } }
