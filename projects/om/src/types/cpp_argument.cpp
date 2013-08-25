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
#include "dogen/om/types/cpp_argument.hpp"

namespace dogen {
namespace om {

cpp_argument::cpp_argument()
    : is_extern_(static_cast<bool>(0)),
      is_static_(static_cast<bool>(0)) { }

cpp_argument::cpp_argument(
    const std::string& name,
    const std::list<dogen::om::doxygen_command>& commands,
    const dogen::om::cpp_typeref& type,
    const std::string& default_value,
    const bool is_extern,
    const bool is_static)
    : dogen::om::cpp_abstract_instance(name,
      commands,
      type,
      default_value),
      is_extern_(is_extern),
      is_static_(is_static) { }

void cpp_argument::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_argument\"" << ", "
      << "\"__parent_0__\": ";
    cpp_abstract_instance::to_stream(s);
    s << ", "
      << "\"is_extern\": " << is_extern_ << ", "
      << "\"is_static\": " << is_static_
      << " }";
}

void cpp_argument::swap(cpp_argument& other) noexcept {
    cpp_abstract_instance::swap(other);

    using std::swap;
    swap(is_extern_, other.is_extern_);
    swap(is_static_, other.is_static_);
}

bool cpp_argument::equals(const dogen::om::cpp_feature& other) const {
    const cpp_argument* const p(dynamic_cast<const cpp_argument* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_argument::operator==(const cpp_argument& rhs) const {
    return cpp_abstract_instance::compare(rhs) &&
        is_extern_ == rhs.is_extern_ &&
        is_static_ == rhs.is_static_;
}

cpp_argument& cpp_argument::operator=(cpp_argument other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_argument::is_extern() const {
    return is_extern_;
}

void cpp_argument::is_extern(const bool v) {
    is_extern_ = v;
}

bool cpp_argument::is_static() const {
    return is_static_;
}

void cpp_argument::is_static(const bool v) {
    is_static_ = v;
}

} }