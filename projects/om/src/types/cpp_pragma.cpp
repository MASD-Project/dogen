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
#include <ostream>
#include "dogen/om/io/cpp_feature_io.hpp"
#include "dogen/om/types/cpp_pragma.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace om {

cpp_pragma::cpp_pragma(
    const std::string& name,
    const std::string& value)
    : dogen::om::cpp_feature(name),
      value_(value) { }

void cpp_pragma::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_pragma\"" << ", "
      << "\"__parent_0__\": ";
    cpp_feature::to_stream(s);
    s << ", "
      << "\"value\": " << "\"" << tidy_up_string(value_) << "\""
      << " }";
}

void cpp_pragma::swap(cpp_pragma& other) noexcept {
    cpp_feature::swap(other);

    using std::swap;
    swap(value_, other.value_);
}

bool cpp_pragma::equals(const dogen::om::cpp_feature& other) const {
    const cpp_pragma* const p(dynamic_cast<const cpp_pragma* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cpp_pragma::operator==(const cpp_pragma& rhs) const {
    return cpp_feature::compare(rhs) &&
        value_ == rhs.value_;
}

cpp_pragma& cpp_pragma::operator=(cpp_pragma other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& cpp_pragma::value() const {
    return value_;
}

std::string& cpp_pragma::value() {
    return value_;
}

void cpp_pragma::value(const std::string& v) {
    value_ = v;
}

void cpp_pragma::value(const std::string&& v) {
    value_ = std::move(v);
}

} }