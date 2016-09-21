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
#include "dogen/quilt.cpp/types/annotations/aspect_annotations_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

aspect_annotations_repository::aspect_annotations_repository(const std::unordered_map<std::string, dogen::quilt::cpp::annotations::aspect_annotations>& by_id)
    : by_id_(by_id) { }

void aspect_annotations_repository::swap(aspect_annotations_repository& other) noexcept {
    using std::swap;
    swap(by_id_, other.by_id_);
}

bool aspect_annotations_repository::operator==(const aspect_annotations_repository& rhs) const {
    return by_id_ == rhs.by_id_;
}

aspect_annotations_repository& aspect_annotations_repository::operator=(aspect_annotations_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::quilt::cpp::annotations::aspect_annotations>& aspect_annotations_repository::by_id() const {
    return by_id_;
}

std::unordered_map<std::string, dogen::quilt::cpp::annotations::aspect_annotations>& aspect_annotations_repository::by_id() {
    return by_id_;
}

void aspect_annotations_repository::by_id(const std::unordered_map<std::string, dogen::quilt::cpp::annotations::aspect_annotations>& v) {
    by_id_ = v;
}

void aspect_annotations_repository::by_id(const std::unordered_map<std::string, dogen::quilt::cpp::annotations::aspect_annotations>&& v) {
    by_id_ = std::move(v);
}

} } } }
