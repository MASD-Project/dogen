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
#include "dogen/enumeration/domain/a_class.hpp"

namespace dogen {
namespace enumeration {

a_class::a_class(
    const dogen::enumeration::colour_types& colour_type,
    const dogen::enumeration::book_types& book_type,
    const dogen::enumeration::pkg1::shape_types& shape_type)
    : colour_type_(colour_type),
      book_type_(book_type),
      shape_type_(shape_type) { }

void a_class::swap(a_class& other) noexcept {
    using std::swap;
    swap(colour_type_, other.colour_type_);
    swap(book_type_, other.book_type_);
    swap(shape_type_, other.shape_type_);
}

bool a_class::operator==(const a_class& rhs) const {
    return colour_type_ == rhs.colour_type_ &&
        book_type_ == rhs.book_type_ &&
        shape_type_ == rhs.shape_type_;
}

a_class& a_class::operator=(a_class other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }