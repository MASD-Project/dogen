/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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

line::line(const std::list<dogen::stitch::segment>& segments)
    : segments_(segments) { }

void line::swap(line& other) noexcept {
    using std::swap;
    swap(segments_, other.segments_);
}

bool line::operator==(const line& rhs) const {
    return segments_ == rhs.segments_;
}

line& line::operator=(line other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::stitch::segment>& line::segments() const {
    return segments_;
}

std::list<dogen::stitch::segment>& line::segments() {
    return segments_;
}

void line::segments(const std::list<dogen::stitch::segment>& v) {
    segments_ = v;
}

void line::segments(const std::list<dogen::stitch::segment>&& v) {
    segments_ = std::move(v);
}

} }