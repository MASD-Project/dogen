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
#include "dogen/stitch/types/line.hpp"

namespace dogen {
namespace stitch {

line::line(const std::list<dogen::stitch::block>& blocks)
    : blocks_(blocks) { }

void line::swap(line& other) noexcept {
    using std::swap;
    swap(blocks_, other.blocks_);
}

bool line::operator==(const line& rhs) const {
    return blocks_ == rhs.blocks_;
}

line& line::operator=(line other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::stitch::block>& line::blocks() const {
    return blocks_;
}

std::list<dogen::stitch::block>& line::blocks() {
    return blocks_;
}

void line::blocks(const std::list<dogen::stitch::block>& v) {
    blocks_ = v;
}

void line::blocks(const std::list<dogen::stitch::block>&& v) {
    blocks_ = std::move(v);
}

} }
