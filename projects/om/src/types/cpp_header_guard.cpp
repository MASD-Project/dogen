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
#include <boost/algorithm/string.hpp>
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/types/cpp_header_guard.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace om {

cpp_header_guard::cpp_header_guard()
    : use_pragma_once_(static_cast<bool>(0)) { }

cpp_header_guard::cpp_header_guard(
    const std::string& name,
    const std::string& guard_name,
    const bool use_pragma_once)
    : dogen::om::cpp_feature(name),
      guard_name_(guard_name),
      use_pragma_once_(use_pragma_once) { }

void cpp_header_guard::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_header_guard\"" << ", "
      << "\"__parent_0__\": ";
    cpp_feature::to_stream(s);
    s << ", "
      << "\"guard_name\": " << "\"" << tidy_up_string(guard_name_) << "\"" << ", "
      << "\"use_pragma_once\": " << use_pragma_once_
      << " }";
}

void cpp_header_guard::swap(cpp_header_guard& other) noexcept {
    cpp_feature::swap(other);

    using std::swap;
    swap(guard_name_, other.guard_name_);
    swap(use_pragma_once_, other.use_pragma_once_);
}

bool cpp_header_guard::equals(const dogen::om::cpp_feature& other) const {
    const cpp_header_guard* const p(dynamic_cast<const cpp_header_guard* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_header_guard::operator==(const cpp_header_guard& rhs) const {
    return cpp_feature::compare(rhs) &&
        guard_name_ == rhs.guard_name_ &&
        use_pragma_once_ == rhs.use_pragma_once_;
}

cpp_header_guard& cpp_header_guard::operator=(cpp_header_guard other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& cpp_header_guard::guard_name() const {
    return guard_name_;
}

std::string& cpp_header_guard::guard_name() {
    return guard_name_;
}

void cpp_header_guard::guard_name(const std::string& v) {
    guard_name_ = v;
}

void cpp_header_guard::guard_name(const std::string&& v) {
    guard_name_ = std::move(v);
}

bool cpp_header_guard::use_pragma_once() const {
    return use_pragma_once_;
}

void cpp_header_guard::use_pragma_once(const bool v) {
    use_pragma_once_ = v;
}

} }