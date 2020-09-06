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
#include "dogen.text.cpp/types/formattables/directive_group_repository.hpp"

namespace dogen::text::cpp::formattables {

directive_group_repository::directive_group_repository(const std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >& by_id)
    : by_id_(by_id) { }

void directive_group_repository::swap(directive_group_repository& other) noexcept {
    using std::swap;
    swap(by_id_, other.by_id_);
}

bool directive_group_repository::operator==(const directive_group_repository& rhs) const {
    return by_id_ == rhs.by_id_;
}

directive_group_repository& directive_group_repository::operator=(directive_group_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >& directive_group_repository::by_id() const {
    return by_id_;
}

std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >& directive_group_repository::by_id() {
    return by_id_;
}

void directive_group_repository::by_id(const std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >& v) {
    by_id_ = v;
}

void directive_group_repository::by_id(const std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >&& v) {
    by_id_ = std::move(v);
}

}
