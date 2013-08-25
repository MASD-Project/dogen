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
#include "dogen/om/types/cpp_feature.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace om {

cpp_feature::cpp_feature(const std::string& name)
    : name_(name) { }

void cpp_feature::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::cpp_feature\"" << ", "
      << "\"name\": " << "\"" << tidy_up_string(name_) << "\""
      << " }";
}

void cpp_feature::swap(cpp_feature& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
}

bool cpp_feature::compare(const cpp_feature& rhs) const {
    return name_ == rhs.name_;
}

const std::string& cpp_feature::name() const {
    return name_;
}

std::string& cpp_feature::name() {
    return name_;
}

void cpp_feature::name(const std::string& v) {
    name_ = v;
}

void cpp_feature::name(const std::string&& v) {
    name_ = std::move(v);
}

} }