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
#include "dogen/om/types/code_generation_marker.hpp"

namespace dogen {
namespace om {

code_generation_marker::code_generation_marker(const std::string& text)
    : text_(text) { }

void code_generation_marker::swap(code_generation_marker& other) noexcept {
    using std::swap;
    swap(text_, other.text_);
}

bool code_generation_marker::operator==(const code_generation_marker& rhs) const {
    return text_ == rhs.text_;
}

code_generation_marker& code_generation_marker::operator=(code_generation_marker other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& code_generation_marker::text() const {
    return text_;
}

std::string& code_generation_marker::text() {
    return text_;
}

void code_generation_marker::text(const std::string& v) {
    text_ = v;
}

void code_generation_marker::text(const std::string&& v) {
    text_ = std::move(v);
}

} }