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
#include "dogen/quilt.cpp/types/properties/file_properties_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

file_properties_repository::file_properties_repository(const std::unordered_map<std::string, dogen::formatters::file_properties>& by_id)
    : by_id_(by_id) { }

void file_properties_repository::swap(file_properties_repository& other) noexcept {
    using std::swap;
    swap(by_id_, other.by_id_);
}

bool file_properties_repository::operator==(const file_properties_repository& rhs) const {
    return by_id_ == rhs.by_id_;
}

file_properties_repository& file_properties_repository::operator=(file_properties_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::formatters::file_properties>& file_properties_repository::by_id() const {
    return by_id_;
}

std::unordered_map<std::string, dogen::formatters::file_properties>& file_properties_repository::by_id() {
    return by_id_;
}

void file_properties_repository::by_id(const std::unordered_map<std::string, dogen::formatters::file_properties>& v) {
    by_id_ = v;
}

void file_properties_repository::by_id(const std::unordered_map<std::string, dogen::formatters::file_properties>&& v) {
    by_id_ = std::move(v);
}

} } } }
