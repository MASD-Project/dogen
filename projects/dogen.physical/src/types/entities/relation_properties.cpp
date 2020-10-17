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
#include "dogen.physical/types/entities/relation_properties.hpp"

namespace dogen::physical::entities {

relation_properties::relation_properties()
    : relation_status_(static_cast<dogen::physical::entities::relation_status>(0)) { }

relation_properties::relation_properties(
    const std::list<std::string>& relations,
    const dogen::physical::entities::relation_status relation_status)
    : relations_(relations),
      relation_status_(relation_status) { }

void relation_properties::swap(relation_properties& other) noexcept {
    using std::swap;
    swap(relations_, other.relations_);
    swap(relation_status_, other.relation_status_);
}

bool relation_properties::operator==(const relation_properties& rhs) const {
    return relations_ == rhs.relations_ &&
        relation_status_ == rhs.relation_status_;
}

relation_properties& relation_properties::operator=(relation_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& relation_properties::relations() const {
    return relations_;
}

std::list<std::string>& relation_properties::relations() {
    return relations_;
}

void relation_properties::relations(const std::list<std::string>& v) {
    relations_ = v;
}

void relation_properties::relations(const std::list<std::string>&& v) {
    relations_ = std::move(v);
}

dogen::physical::entities::relation_status relation_properties::relation_status() const {
    return relation_status_;
}

void relation_properties::relation_status(const dogen::physical::entities::relation_status v) {
    relation_status_ = v;
}

}
