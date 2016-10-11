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
#include <boost/io/ios_state.hpp>
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/element_visitor.hpp"

namespace dogen {
namespace yarn {

primitive::primitive()
    : is_default_enumeration_type_(static_cast<bool>(0)) { }

primitive::primitive(
    const std::string& documentation,
    const dogen::annotations::object& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::generation_types generation_type,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::unordered_set<dogen::yarn::stereotypes>& stereotypes,
    const bool is_element_extension,
    const bool is_default_enumeration_type)
    : dogen::yarn::element(
      documentation,
      annotation,
      name,
      generation_type,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      is_element_extension),
      is_default_enumeration_type_(is_default_enumeration_type) { }

void primitive::accept(const element_visitor& v) const {
    v.visit(*this);
}

void primitive::accept(element_visitor& v) const {
    v.visit(*this);
    }

void primitive::accept(const element_visitor& v) {
    v.visit(*this);
}

void primitive::accept(element_visitor& v) {
    v.visit(*this);
}


void primitive::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::primitive\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << ", "
      << "\"is_default_enumeration_type\": " << is_default_enumeration_type_
      << " }";
}

void primitive::swap(primitive& other) noexcept {
    element::swap(other);

    using std::swap;
    swap(is_default_enumeration_type_, other.is_default_enumeration_type_);
}

bool primitive::equals(const dogen::yarn::element& other) const {
    const primitive* const p(dynamic_cast<const primitive* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool primitive::operator==(const primitive& rhs) const {
    return element::compare(rhs) &&
        is_default_enumeration_type_ == rhs.is_default_enumeration_type_;
}

primitive& primitive::operator=(primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool primitive::is_default_enumeration_type() const {
    return is_default_enumeration_type_;
}

void primitive::is_default_enumeration_type(const bool v) {
    is_default_enumeration_type_ = v;
}

} }
