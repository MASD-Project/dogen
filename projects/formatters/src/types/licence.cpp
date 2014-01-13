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
#include "dogen/formatters/types/licence.hpp"

namespace dogen {
namespace formatters {

licence::licence(
    const std::list<std::string>& copyright_holders,
    const std::string& text)
    : copyright_holders_(copyright_holders),
      text_(text) { }

void licence::swap(licence& other) noexcept {
    using std::swap;
    swap(copyright_holders_, other.copyright_holders_);
    swap(text_, other.text_);
}

bool licence::operator==(const licence& rhs) const {
    return copyright_holders_ == rhs.copyright_holders_ &&
        text_ == rhs.text_;
}

licence& licence::operator=(licence other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& licence::copyright_holders() const {
    return copyright_holders_;
}

std::list<std::string>& licence::copyright_holders() {
    return copyright_holders_;
}

void licence::copyright_holders(const std::list<std::string>& v) {
    copyright_holders_ = v;
}

void licence::copyright_holders(const std::list<std::string>&& v) {
    copyright_holders_ = std::move(v);
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

} }