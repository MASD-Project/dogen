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
#include <ostream>
#include "dogen/tack/io/type_io.hpp"
#include "dogen/tack/types/primitive.hpp"

namespace dogen {
namespace tack {

primitive::primitive(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::tack::name& name,
    const dogen::tack::generation_types generation_type,
    const dogen::tack::origin_types origin_type,
    const boost::optional<dogen::tack::name>& containing_module)
    : dogen::tack::type(
      documentation,
      extensions,
      name,
      generation_type,
      origin_type,
      containing_module) { }

void primitive::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::tack::primitive\"" << ", "
      << "\"__parent_0__\": ";
    type::to_stream(s);
    s << " }";
}

void primitive::swap(primitive& other) noexcept {
    type::swap(other);

}

bool primitive::equals(const dogen::tack::type& other) const {
    const primitive* const p(dynamic_cast<const primitive* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool primitive::operator==(const primitive& rhs) const {
    return type::compare(rhs);
}

primitive& primitive::operator=(primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }
