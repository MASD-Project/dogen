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
#include "dogen.identification/types/entities/codec_location.hpp"

namespace dogen::identification::entities {

codec_location::codec_location()
    : line_(static_cast<long>(0)),
      column_(static_cast<long>(0)) { }

codec_location::codec_location(
    const long line,
    const long column)
    : line_(line),
      column_(column) { }

void codec_location::swap(codec_location& other) noexcept {
    using std::swap;
    swap(line_, other.line_);
    swap(column_, other.column_);
}

bool codec_location::operator==(const codec_location& rhs) const {
    return line_ == rhs.line_ &&
        column_ == rhs.column_;
}

codec_location& codec_location::operator=(codec_location other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

long codec_location::line() const {
    return line_;
}

void codec_location::line(const long v) {
    line_ = v;
}

long codec_location::column() const {
    return column_;
}

void codec_location::column(const long v) {
    column_ = v;
}

}
