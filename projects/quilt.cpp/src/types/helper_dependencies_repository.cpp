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
#include "dogen/quilt.cpp/types/helper_dependencies_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {

helper_dependencies_repository::helper_dependencies_repository(const std::unordered_map<std::string, std::string>& helper_properties_by_name)
    : helper_properties_by_name_(helper_properties_by_name) { }

void helper_dependencies_repository::swap(helper_dependencies_repository& other) noexcept {
    using std::swap;
    swap(helper_properties_by_name_, other.helper_properties_by_name_);
}

bool helper_dependencies_repository::operator==(const helper_dependencies_repository& rhs) const {
    return helper_properties_by_name_ == rhs.helper_properties_by_name_;
}

helper_dependencies_repository& helper_dependencies_repository::operator=(helper_dependencies_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::string>& helper_dependencies_repository::helper_properties_by_name() const {
    return helper_properties_by_name_;
}

std::unordered_map<std::string, std::string>& helper_dependencies_repository::helper_properties_by_name() {
    return helper_properties_by_name_;
}

void helper_dependencies_repository::helper_properties_by_name(const std::unordered_map<std::string, std::string>& v) {
    helper_properties_by_name_ = v;
}

void helper_dependencies_repository::helper_properties_by_name(const std::unordered_map<std::string, std::string>&& v) {
    helper_properties_by_name_ = std::move(v);
}

} } }
