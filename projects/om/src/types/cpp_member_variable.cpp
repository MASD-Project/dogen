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
#include "dogen/om/io/cpp_abstract_instance_io.hpp"
#include "dogen/om/types/cpp_member_variable.hpp"

namespace dogen {
namespace om {

cpp_member_variable::cpp_member_variable()
    : is_mutable_(static_cast<bool>(0)),
      is_static_(static_cast<bool>(0)) { }

cpp_member_variable::cpp_member_variable(
    const std::string& name,
    const std::list<dogen::om::doxygen_command>& commands,
    const dogen::om::cpp_typeref& type,
    const std::string& default_value,
    const bool is_mutable,
    const bool is_static)
    : dogen::om::cpp_abstract_instance(name,
      commands,
      type,
      default_value),
      is_mutable_(is_mutable),
      is_static_(is_static) { }

void cpp_member_variable::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_member_variable\"" << ", "
      << "\"__parent_0__\": ";
    cpp_abstract_instance::to_stream(s);
    s << ", "
      << "\"is_mutable\": " << is_mutable_ << ", "
      << "\"is_static\": " << is_static_
      << " }";
}

void cpp_member_variable::swap(cpp_member_variable& other) noexcept {
    cpp_abstract_instance::swap(other);

    using std::swap;
    swap(is_mutable_, other.is_mutable_);
    swap(is_static_, other.is_static_);
}

bool cpp_member_variable::equals(const dogen::om::cpp_feature& other) const {
    const cpp_member_variable* const p(dynamic_cast<const cpp_member_variable* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_member_variable::operator==(const cpp_member_variable& rhs) const {
    return cpp_abstract_instance::compare(rhs) &&
        is_mutable_ == rhs.is_mutable_ &&
        is_static_ == rhs.is_static_;
}

cpp_member_variable& cpp_member_variable::operator=(cpp_member_variable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_member_variable::is_mutable() const {
    return is_mutable_;
}

void cpp_member_variable::is_mutable(const bool v) {
    is_mutable_ = v;
}

bool cpp_member_variable::is_static() const {
    return is_static_;
}

void cpp_member_variable::is_static(const bool v) {
    is_static_ = v;
}

} }