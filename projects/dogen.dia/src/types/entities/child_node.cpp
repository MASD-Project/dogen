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
#include "dogen.dia/types/entities/child_node.hpp"

namespace dogen::dia::entities {

child_node::child_node(const std::string& parent)
    : parent_(parent) { }

void child_node::swap(child_node& other) noexcept {
    using std::swap;
    swap(parent_, other.parent_);
}

bool child_node::operator==(const child_node& rhs) const {
    return parent_ == rhs.parent_;
}

child_node& child_node::operator=(child_node other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& child_node::parent() const {
    return parent_;
}

std::string& child_node::parent() {
    return parent_;
}

void child_node::parent(const std::string& v) {
    parent_ = v;
}

void child_node::parent(const std::string&& v) {
    parent_ = std::move(v);
}

}
