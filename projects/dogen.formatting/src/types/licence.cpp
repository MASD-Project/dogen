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
#include "dogen.formatting/types/licence.hpp"

namespace dogen::formatting {

licence::licence(
    const std::list<std::string>& copyright_notices,
    const std::string& text)
    : copyright_notices_(copyright_notices),
      text_(text) { }

void licence::swap(licence& other) noexcept {
    using std::swap;
    swap(copyright_notices_, other.copyright_notices_);
    swap(text_, other.text_);
}

bool licence::operator==(const licence& rhs) const {
    return copyright_notices_ == rhs.copyright_notices_ &&
        text_ == rhs.text_;
}

licence& licence::operator=(licence other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& licence::copyright_notices() const {
    return copyright_notices_;
}

std::list<std::string>& licence::copyright_notices() {
    return copyright_notices_;
}

void licence::copyright_notices(const std::list<std::string>& v) {
    copyright_notices_ = v;
}

void licence::copyright_notices(const std::list<std::string>&& v) {
    copyright_notices_ = std::move(v);
}

const std::string& licence::text() const {
    return text_;
}

std::string& licence::text() {
    return text_;
}

void licence::text(const std::string& v) {
    text_ = v;
}

void licence::text(const std::string&& v) {
    text_ = std::move(v);
}

}
