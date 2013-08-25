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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/om/io/cpp_abstract_function_io.hpp"
#include "dogen/om/io/cpp_member_function_types_io.hpp"
#include "dogen/om/types/cpp_member_function.hpp"

namespace dogen {
namespace om {

cpp_member_function::cpp_member_function()
    : is_virtual_(static_cast<bool>(0)),
      is_explicit_(static_cast<bool>(0)),
      is_pure_(static_cast<bool>(0)),
      is_override_(static_cast<bool>(0)),
      is_final_(static_cast<bool>(0)),
      is_default_(static_cast<bool>(0)),
      is_static_(static_cast<bool>(0)),
      type_(static_cast<dogen::om::cpp_member_function_types>(0)) { }

cpp_member_function::cpp_member_function(
    const std::string& name,
    const std::list<dogen::om::doxygen_command>& commands,
    const dogen::om::cpp_representation_types& representation_type,
    const bool is_inline,
    const dogen::om::cpp_instance_typeref& return_type,
    const std::list<dogen::om::cpp_argument>& arguments,
    const bool is_friend,
    const bool is_virtual,
    const bool is_explicit,
    const bool is_pure,
    const bool is_override,
    const bool is_final,
    const bool is_default,
    const bool is_static,
    const dogen::om::cpp_member_function_types& type)
    : dogen::om::cpp_abstract_function(name,
      commands,
      representation_type,
      is_inline,
      return_type,
      arguments,
      is_friend),
      is_virtual_(is_virtual),
      is_explicit_(is_explicit),
      is_pure_(is_pure),
      is_override_(is_override),
      is_final_(is_final),
      is_default_(is_default),
      is_static_(is_static),
      type_(type) { }

void cpp_member_function::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_member_function\"" << ", "
      << "\"__parent_0__\": ";
    cpp_abstract_function::to_stream(s);
    s << ", "
      << "\"is_virtual\": " << is_virtual_ << ", "
      << "\"is_explicit\": " << is_explicit_ << ", "
      << "\"is_pure\": " << is_pure_ << ", "
      << "\"is_override\": " << is_override_ << ", "
      << "\"is_final\": " << is_final_ << ", "
      << "\"is_default\": " << is_default_ << ", "
      << "\"is_static\": " << is_static_ << ", "
      << "\"type\": " << type_
      << " }";
}

void cpp_member_function::swap(cpp_member_function& other) noexcept {
    cpp_abstract_function::swap(other);

    using std::swap;
    swap(is_virtual_, other.is_virtual_);
    swap(is_explicit_, other.is_explicit_);
    swap(is_pure_, other.is_pure_);
    swap(is_override_, other.is_override_);
    swap(is_final_, other.is_final_);
    swap(is_default_, other.is_default_);
    swap(is_static_, other.is_static_);
    swap(type_, other.type_);
}

bool cpp_member_function::equals(const dogen::om::cpp_feature& other) const {
    const cpp_member_function* const p(dynamic_cast<const cpp_member_function* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_member_function::operator==(const cpp_member_function& rhs) const {
    return cpp_abstract_function::compare(rhs) &&
        is_virtual_ == rhs.is_virtual_ &&
        is_explicit_ == rhs.is_explicit_ &&
        is_pure_ == rhs.is_pure_ &&
        is_override_ == rhs.is_override_ &&
        is_final_ == rhs.is_final_ &&
        is_default_ == rhs.is_default_ &&
        is_static_ == rhs.is_static_ &&
        type_ == rhs.type_;
}

cpp_member_function& cpp_member_function::operator=(cpp_member_function other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_member_function::is_virtual() const {
    return is_virtual_;
}

void cpp_member_function::is_virtual(const bool v) {
    is_virtual_ = v;
}

bool cpp_member_function::is_explicit() const {
    return is_explicit_;
}

void cpp_member_function::is_explicit(const bool v) {
    is_explicit_ = v;
}

bool cpp_member_function::is_pure() const {
    return is_pure_;
}

void cpp_member_function::is_pure(const bool v) {
    is_pure_ = v;
}

bool cpp_member_function::is_override() const {
    return is_override_;
}

void cpp_member_function::is_override(const bool v) {
    is_override_ = v;
}

bool cpp_member_function::is_final() const {
    return is_final_;
}

void cpp_member_function::is_final(const bool v) {
    is_final_ = v;
}

bool cpp_member_function::is_default() const {
    return is_default_;
}

void cpp_member_function::is_default(const bool v) {
    is_default_ = v;
}

bool cpp_member_function::is_static() const {
    return is_static_;
}

void cpp_member_function::is_static(const bool v) {
    is_static_ = v;
}

dogen::om::cpp_member_function_types cpp_member_function::type() const {
    return type_;
}

void cpp_member_function::type(const dogen::om::cpp_member_function_types& v) {
    type_ = v;
}

} }