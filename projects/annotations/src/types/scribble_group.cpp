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
#include "dogen/annotations/types/scribble_group.hpp"

namespace dogen {
namespace annotations {

scribble_group::scribble_group(
    const dogen::annotations::scribble& parent,
    const std::unordered_map<std::string, dogen::annotations::scribble>& children)
    : parent_(parent),
      children_(children) { }

void scribble_group::swap(scribble_group& other) noexcept {
    using std::swap;
    swap(parent_, other.parent_);
    swap(children_, other.children_);
}

bool scribble_group::operator==(const scribble_group& rhs) const {
    return parent_ == rhs.parent_ &&
        children_ == rhs.children_;
}

scribble_group& scribble_group::operator=(scribble_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::annotations::scribble& scribble_group::parent() const {
    return parent_;
}

dogen::annotations::scribble& scribble_group::parent() {
    return parent_;
}

void scribble_group::parent(const dogen::annotations::scribble& v) {
    parent_ = v;
}

void scribble_group::parent(const dogen::annotations::scribble&& v) {
    parent_ = std::move(v);
}

const std::unordered_map<std::string, dogen::annotations::scribble>& scribble_group::children() const {
    return children_;
}

std::unordered_map<std::string, dogen::annotations::scribble>& scribble_group::children() {
    return children_;
}

void scribble_group::children(const std::unordered_map<std::string, dogen::annotations::scribble>& v) {
    children_ = v;
}

void scribble_group::children(const std::unordered_map<std::string, dogen::annotations::scribble>&& v) {
    children_ = std::move(v);
}

} }
