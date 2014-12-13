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
#include <ostream>
#include "dogen/dynamic/io/value_types_io.hpp"
#include "dogen/dynamic/types/value.hpp"

namespace dogen {
namespace dynamic {

value::value()
    : type_(static_cast<dogen::dynamic::value_types>(0)) { }

value::value(const dogen::dynamic::value_types& type)
    : type_(type) { }

void value::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::dynamic::value\"" << ", "
      << "\"type\": " << type_
      << " }";
}

void value::swap(value& other) noexcept {
    using std::swap;
    swap(type_, other.type_);
}

bool value::compare(const value& rhs) const {
    return type_ == rhs.type_;
}

dogen::dynamic::value_types value::type() const {
    return type_;
}

void value::type(const dogen::dynamic::value_types& v) {
    type_ = v;
}

} }