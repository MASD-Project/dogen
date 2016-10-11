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
#include "dogen/annotations/types/object_aggregate.hpp"

namespace dogen {
namespace annotations {

object_aggregate::object_aggregate(
    const dogen::annotations::object& element,
    const std::unordered_map<std::string, dogen::annotations::object>& attributes)
    : element_(element),
      attributes_(attributes) { }

void object_aggregate::swap(object_aggregate& other) noexcept {
    using std::swap;
    swap(element_, other.element_);
    swap(attributes_, other.attributes_);
}

bool object_aggregate::operator==(const object_aggregate& rhs) const {
    return element_ == rhs.element_ &&
        attributes_ == rhs.attributes_;
}

object_aggregate& object_aggregate::operator=(object_aggregate other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::annotations::object& object_aggregate::element() const {
    return element_;
}

dogen::annotations::object& object_aggregate::element() {
    return element_;
}

void object_aggregate::element(const dogen::annotations::object& v) {
    element_ = v;
}

void object_aggregate::element(const dogen::annotations::object&& v) {
    element_ = std::move(v);
}

const std::unordered_map<std::string, dogen::annotations::object>& object_aggregate::attributes() const {
    return attributes_;
}

std::unordered_map<std::string, dogen::annotations::object>& object_aggregate::attributes() {
    return attributes_;
}

void object_aggregate::attributes(const std::unordered_map<std::string, dogen::annotations::object>& v) {
    attributes_ = v;
}

void object_aggregate::attributes(const std::unordered_map<std::string, dogen::annotations::object>&& v) {
    attributes_ = std::move(v);
}

} }
