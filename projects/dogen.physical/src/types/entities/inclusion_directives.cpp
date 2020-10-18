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
#include "dogen.physical/types/entities/inclusion_directives.hpp"

namespace dogen::physical::entities {

inclusion_directives::inclusion_directives(
    const std::string& primary,
    const std::list<std::string>& secondary)
    : primary_(primary),
      secondary_(secondary) { }

void inclusion_directives::swap(inclusion_directives& other) noexcept {
    using std::swap;
    swap(primary_, other.primary_);
    swap(secondary_, other.secondary_);
}

bool inclusion_directives::operator==(const inclusion_directives& rhs) const {
    return primary_ == rhs.primary_ &&
        secondary_ == rhs.secondary_;
}

inclusion_directives& inclusion_directives::operator=(inclusion_directives other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& inclusion_directives::primary() const {
    return primary_;
}

std::string& inclusion_directives::primary() {
    return primary_;
}

void inclusion_directives::primary(const std::string& v) {
    primary_ = v;
}

void inclusion_directives::primary(const std::string&& v) {
    primary_ = std::move(v);
}

const std::list<std::string>& inclusion_directives::secondary() const {
    return secondary_;
}

std::list<std::string>& inclusion_directives::secondary() {
    return secondary_;
}

void inclusion_directives::secondary(const std::list<std::string>& v) {
    secondary_ = v;
}

void inclusion_directives::secondary(const std::list<std::string>&& v) {
    secondary_ = std::move(v);
}

}
