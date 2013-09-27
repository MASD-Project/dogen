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
#include "dogen/sml/io/type_io.hpp"
#include "dogen/sml/types/primitive.hpp"

namespace dogen {
namespace sml {

primitive::primitive(
    const std::string& documentation,
    const std::unordered_map<std::string, std::string>& simple_tags,
    const std::unordered_map<std::string, std::list<std::string> >& complex_tags,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const dogen::sml::origin_types& origin_type)
    : dogen::sml::type(documentation,
      simple_tags,
      complex_tags,
      name,
      generation_type,
      origin_type) { }

void primitive::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::primitive\"" << ", "
      << "\"__parent_0__\": ";
    type::to_stream(s);
    s << " }";
}

void primitive::swap(primitive& other) noexcept {
    type::swap(other);

}

bool primitive::equals(const dogen::sml::type& other) const {
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