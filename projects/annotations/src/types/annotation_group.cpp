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
#include "dogen/annotations/types/annotation_group.hpp"

namespace dogen {
namespace annotations {

annotation_group::annotation_group(
    const dogen::annotations::annotation& parent,
    const std::unordered_map<std::string, dogen::annotations::annotation>& children)
    : parent_(parent),
      children_(children) { }

void annotation_group::swap(annotation_group& other) noexcept {
    using std::swap;
    swap(parent_, other.parent_);
    swap(children_, other.children_);
}

bool annotation_group::operator==(const annotation_group& rhs) const {
    return parent_ == rhs.parent_ &&
        children_ == rhs.children_;
}

annotation_group& annotation_group::operator=(annotation_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::annotations::annotation& annotation_group::parent() const {
    return parent_;
}

dogen::annotations::annotation& annotation_group::parent() {
    return parent_;
}

void annotation_group::parent(const dogen::annotations::annotation& v) {
    parent_ = v;
}

void annotation_group::parent(const dogen::annotations::annotation&& v) {
    parent_ = std::move(v);
}

const std::unordered_map<std::string, dogen::annotations::annotation>& annotation_group::children() const {
    return children_;
}

std::unordered_map<std::string, dogen::annotations::annotation>& annotation_group::children() {
    return children_;
}

void annotation_group::children(const std::unordered_map<std::string, dogen::annotations::annotation>& v) {
    children_ = v;
}

void annotation_group::children(const std::unordered_map<std::string, dogen::annotations::annotation>&& v) {
    children_ = std::move(v);
}

} }
