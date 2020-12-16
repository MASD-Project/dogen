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
#include "dogen.org/types/entities/section.hpp"

namespace dogen::org::entities {

section::section(const std::list<dogen::org::entities::block>& blocks)
    : blocks_(blocks) { }

void section::swap(section& other) noexcept {
    using std::swap;
    swap(blocks_, other.blocks_);
}

bool section::operator==(const section& rhs) const {
    return blocks_ == rhs.blocks_;
}

section& section::operator=(section other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::org::entities::block>& section::blocks() const {
    return blocks_;
}

std::list<dogen::org::entities::block>& section::blocks() {
    return blocks_;
}

void section::blocks(const std::list<dogen::org::entities::block>& v) {
    blocks_ = v;
}

void section::blocks(const std::list<dogen::org::entities::block>&& v) {
    blocks_ = std::move(v);
}

}
