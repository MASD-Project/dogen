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
#include "dogen/yarn/types/meta_model/kernel_properties.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

kernel_properties::kernel_properties()
    : enabled_(static_cast<bool>(0)),
      force_kernel_directory_(static_cast<bool>(0)) { }

kernel_properties::kernel_properties(
    const bool enabled,
    const std::string& directory,
    const bool force_kernel_directory)
    : enabled_(enabled),
      directory_(directory),
      force_kernel_directory_(force_kernel_directory) { }

void kernel_properties::swap(kernel_properties& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(directory_, other.directory_);
    swap(force_kernel_directory_, other.force_kernel_directory_);
}

bool kernel_properties::operator==(const kernel_properties& rhs) const {
    return enabled_ == rhs.enabled_ &&
        directory_ == rhs.directory_ &&
        force_kernel_directory_ == rhs.force_kernel_directory_;
}

kernel_properties& kernel_properties::operator=(kernel_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool kernel_properties::enabled() const {
    return enabled_;
}

void kernel_properties::enabled(const bool v) {
    enabled_ = v;
}

const std::string& kernel_properties::directory() const {
    return directory_;
}

std::string& kernel_properties::directory() {
    return directory_;
}

void kernel_properties::directory(const std::string& v) {
    directory_ = v;
}

void kernel_properties::directory(const std::string&& v) {
    directory_ = std::move(v);
}

bool kernel_properties::force_kernel_directory() const {
    return force_kernel_directory_;
}

void kernel_properties::force_kernel_directory(const bool v) {
    force_kernel_directory_ = v;
}

} } }
