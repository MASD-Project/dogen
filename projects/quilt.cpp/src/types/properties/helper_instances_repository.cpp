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
#include "dogen/quilt.cpp/types/properties/helper_instances_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

helper_instances_repository::helper_instances_repository(const std::unordered_map<std::string, std::list<dogen::quilt::cpp::properties::helper_instance> >& helper_instances_by_name)
    : helper_instances_by_name_(helper_instances_by_name) { }

void helper_instances_repository::swap(helper_instances_repository& other) noexcept {
    using std::swap;
    swap(helper_instances_by_name_, other.helper_instances_by_name_);
}

bool helper_instances_repository::operator==(const helper_instances_repository& rhs) const {
    return helper_instances_by_name_ == rhs.helper_instances_by_name_;
}

helper_instances_repository& helper_instances_repository::operator=(helper_instances_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::list<dogen::quilt::cpp::properties::helper_instance> >& helper_instances_repository::helper_instances_by_name() const {
    return helper_instances_by_name_;
}

std::unordered_map<std::string, std::list<dogen::quilt::cpp::properties::helper_instance> >& helper_instances_repository::helper_instances_by_name() {
    return helper_instances_by_name_;
}

void helper_instances_repository::helper_instances_by_name(const std::unordered_map<std::string, std::list<dogen::quilt::cpp::properties::helper_instance> >& v) {
    helper_instances_by_name_ = v;
}

void helper_instances_repository::helper_instances_by_name(const std::unordered_map<std::string, std::list<dogen::quilt::cpp::properties::helper_instance> >&& v) {
    helper_instances_by_name_ = std::move(v);
}

} } } }
