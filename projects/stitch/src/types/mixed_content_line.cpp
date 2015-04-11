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
#include "dogen/stitch/types/mixed_content_line.hpp"

namespace dogen {
namespace stitch {

mixed_content_line::mixed_content_line(const std::list<dogen::stitch::segment>& segments)
    : segments_(segments) { }

void mixed_content_line::swap(mixed_content_line& other) noexcept {
    using std::swap;
    swap(segments_, other.segments_);
}

bool mixed_content_line::operator==(const mixed_content_line& rhs) const {
    return segments_ == rhs.segments_;
}

mixed_content_line& mixed_content_line::operator=(mixed_content_line other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::stitch::segment>& mixed_content_line::segments() const {
    return segments_;
}

std::list<dogen::stitch::segment>& mixed_content_line::segments() {
    return segments_;
}

void mixed_content_line::segments(const std::list<dogen::stitch::segment>& v) {
    segments_ = v;
}

void mixed_content_line::segments(const std::list<dogen::stitch::segment>&& v) {
    segments_ = std::move(v);
}

} }