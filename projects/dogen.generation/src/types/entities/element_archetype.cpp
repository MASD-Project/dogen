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
#include "dogen.generation/types/entities/element_archetype.hpp"

namespace dogen::generation::entities {

element_archetype::element_archetype(
    const std::string& element,
    const std::string& archetype)
    : element_(element),
      archetype_(archetype) { }

void element_archetype::swap(element_archetype& other) noexcept {
    using std::swap;
    swap(element_, other.element_);
    swap(archetype_, other.archetype_);
}

bool element_archetype::operator==(const element_archetype& rhs) const {
    return element_ == rhs.element_ &&
        archetype_ == rhs.archetype_;
}

element_archetype& element_archetype::operator=(element_archetype other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& element_archetype::element() const {
    return element_;
}

std::string& element_archetype::element() {
    return element_;
}

void element_archetype::element(const std::string& v) {
    element_ = v;
}

void element_archetype::element(const std::string&& v) {
    element_ = std::move(v);
}

const std::string& element_archetype::archetype() const {
    return archetype_;
}

std::string& element_archetype::archetype() {
    return archetype_;
}

void element_archetype::archetype(const std::string& v) {
    archetype_ = v;
}

void element_archetype::archetype(const std::string&& v) {
    archetype_ = std::move(v);
}

}
