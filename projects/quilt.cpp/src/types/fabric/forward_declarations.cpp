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
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

forward_declarations::forward_declarations()
    : is_enum_(static_cast<bool>(0)),
      is_exception_(static_cast<bool>(0)) { }

forward_declarations::forward_declarations(
    const std::string& documentation,
    const dogen::annotations::object& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::generation_types generation_type,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::unordered_set<dogen::yarn::stereotypes>& stereotypes,
    const bool is_element_extension,
    const bool is_enum,
    const dogen::yarn::name& underlying_type,
    const bool is_exception)
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
      is_enum_(is_enum),
      underlying_type_(underlying_type),
      is_exception_(is_exception) { }

void forward_declarations::accept(const dogen::yarn::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void forward_declarations::accept(dogen::yarn::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void forward_declarations::accept(const dogen::yarn::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void forward_declarations::accept(dogen::yarn::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}


void forward_declarations::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::fabric::forward_declarations\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << ", "
      << "\"is_enum\": " << is_enum_ << ", "
      << "\"underlying_type\": " << underlying_type_ << ", "
      << "\"is_exception\": " << is_exception_
      << " }";
}

void forward_declarations::swap(forward_declarations& other) noexcept {
    element::swap(other);

    using std::swap;
    swap(is_enum_, other.is_enum_);
    swap(underlying_type_, other.underlying_type_);
    swap(is_exception_, other.is_exception_);
}

bool forward_declarations::equals(const dogen::yarn::element& other) const {
    const forward_declarations* const p(dynamic_cast<const forward_declarations* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool forward_declarations::operator==(const forward_declarations& rhs) const {
    return element::compare(rhs) &&
        is_enum_ == rhs.is_enum_ &&
        underlying_type_ == rhs.underlying_type_ &&
        is_exception_ == rhs.is_exception_;
}

forward_declarations& forward_declarations::operator=(forward_declarations other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool forward_declarations::is_enum() const {
    return is_enum_;
}

void forward_declarations::is_enum(const bool v) {
    is_enum_ = v;
}

const dogen::yarn::name& forward_declarations::underlying_type() const {
    return underlying_type_;
}

dogen::yarn::name& forward_declarations::underlying_type() {
    return underlying_type_;
}

void forward_declarations::underlying_type(const dogen::yarn::name& v) {
    underlying_type_ = v;
}

void forward_declarations::underlying_type(const dogen::yarn::name&& v) {
    underlying_type_ = std::move(v);
}

bool forward_declarations::is_exception() const {
    return is_exception_;
}

void forward_declarations::is_exception(const bool v) {
    is_exception_ = v;
}

} } } }
