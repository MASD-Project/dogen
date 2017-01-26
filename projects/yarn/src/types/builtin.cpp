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
#include "dogen/yarn/types/builtin.hpp"
#include "dogen/yarn/types/element_visitor.hpp"

namespace dogen {
namespace yarn {

builtin::builtin()
    : is_default_enumeration_type_(static_cast<bool>(0)),
      is_floating_point_(static_cast<bool>(0)) { }

builtin::builtin(
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::vector<std::string>& stereotypes,
    const bool is_element_extension,
    const bool is_default_enumeration_type,
    const bool is_floating_point)
    : dogen::yarn::element(
      documentation,
      annotation,
      name,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      is_element_extension),
      is_default_enumeration_type_(is_default_enumeration_type),
      is_floating_point_(is_floating_point) { }

void builtin::accept(const element_visitor& v) const {
    v.visit(*this);
}

void builtin::accept(element_visitor& v) const {
    v.visit(*this);
    }

void builtin::accept(const element_visitor& v) {
    v.visit(*this);
}

void builtin::accept(element_visitor& v) {
    v.visit(*this);
}

void builtin::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::builtin\"" << ", "
      << "\"__parent_0__\": ";
    dogen::yarn::element::to_stream(s);
    s << ", "
      << "\"is_default_enumeration_type\": " << is_default_enumeration_type_ << ", "
      << "\"is_floating_point\": " << is_floating_point_
      << " }";
}

void builtin::swap(builtin& other) noexcept {
    dogen::yarn::element::swap(other);

    using std::swap;
    swap(is_default_enumeration_type_, other.is_default_enumeration_type_);
    swap(is_floating_point_, other.is_floating_point_);
}

bool builtin::equals(const dogen::yarn::element& other) const {
    const builtin* const p(dynamic_cast<const builtin* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool builtin::operator==(const builtin& rhs) const {
    return dogen::yarn::element::compare(rhs) &&
        is_default_enumeration_type_ == rhs.is_default_enumeration_type_ &&
        is_floating_point_ == rhs.is_floating_point_;
}

builtin& builtin::operator=(builtin other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool builtin::is_default_enumeration_type() const {
    return is_default_enumeration_type_;
}

void builtin::is_default_enumeration_type(const bool v) {
    is_default_enumeration_type_ = v;
}

bool builtin::is_floating_point() const {
    return is_floating_point_;
}

void builtin::is_floating_point(const bool v) {
    is_floating_point_ = v;
}

} }
