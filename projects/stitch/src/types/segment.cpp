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
#include "dogen/stitch/types/segment.hpp"

namespace dogen {
namespace stitch {

segment::segment()
    : segment_type_(static_cast<dogen::stitch::segment_types>(0)) { }

segment::segment(
    const dogen::stitch::segment_types& segment_type,
    const std::string& content)
    : segment_type_(segment_type),
      content_(content) { }

void segment::swap(segment& other) noexcept {
    using std::swap;
    swap(segment_type_, other.segment_type_);
    swap(content_, other.content_);
}

bool segment::operator==(const segment& rhs) const {
    return segment_type_ == rhs.segment_type_ &&
        content_ == rhs.content_;
}

segment& segment::operator=(segment other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::stitch::segment_types segment::segment_type() const {
    return segment_type_;
}

void segment::segment_type(const dogen::stitch::segment_types& v) {
    segment_type_ = v;
}

const std::string& segment::content() const {
    return content_;
}

std::string& segment::content() {
    return content_;
}

void segment::content(const std::string& v) {
    content_ = v;
}

void segment::content(const std::string&& v) {
    content_ = std::move(v);
}

} }