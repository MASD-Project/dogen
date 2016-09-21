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
#include "dogen/quilt.cpp/types/annotations/element_annotations_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

element_annotations_repository::element_annotations_repository(const std::unordered_map<std::string, dogen::quilt::cpp::annotations::element_annotations>& by_id)
    : by_id_(by_id) { }

void element_annotations_repository::swap(element_annotations_repository& other) noexcept {
    using std::swap;
    swap(by_id_, other.by_id_);
}

bool element_annotations_repository::operator==(const element_annotations_repository& rhs) const {
    return by_id_ == rhs.by_id_;
}

element_annotations_repository& element_annotations_repository::operator=(element_annotations_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::quilt::cpp::annotations::element_annotations>& element_annotations_repository::by_id() const {
    return by_id_;
}

std::unordered_map<std::string, dogen::quilt::cpp::annotations::element_annotations>& element_annotations_repository::by_id() {
    return by_id_;
}

void element_annotations_repository::by_id(const std::unordered_map<std::string, dogen::quilt::cpp::annotations::element_annotations>& v) {
    by_id_ = v;
}

void element_annotations_repository::by_id(const std::unordered_map<std::string, dogen::quilt::cpp::annotations::element_annotations>&& v) {
    by_id_ = std::move(v);
}

} } } }
