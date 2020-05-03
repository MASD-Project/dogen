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
#include "dogen.text.cpp/types/formattables/directive_group.hpp"

namespace dogen::text::cpp::formattables {

directive_group::directive_group(
    const std::string& primary,
    const std::list<std::string>& secondary)
    : primary_(primary),
      secondary_(secondary) { }

void directive_group::swap(directive_group& other) noexcept {
    using std::swap;
    swap(primary_, other.primary_);
    swap(secondary_, other.secondary_);
}

bool directive_group::operator==(const directive_group& rhs) const {
    return primary_ == rhs.primary_ &&
        secondary_ == rhs.secondary_;
}

directive_group& directive_group::operator=(directive_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& directive_group::primary() const {
    return primary_;
}

std::string& directive_group::primary() {
    return primary_;
}

void directive_group::primary(const std::string& v) {
    primary_ = v;
}

void directive_group::primary(const std::string&& v) {
    primary_ = std::move(v);
}

const std::list<std::string>& directive_group::secondary() const {
    return secondary_;
}

std::list<std::string>& directive_group::secondary() {
    return secondary_;
}

void directive_group::secondary(const std::list<std::string>& v) {
    secondary_ = v;
}

void directive_group::secondary(const std::list<std::string>&& v) {
    secondary_ = std::move(v);
}

}
