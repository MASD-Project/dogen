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
#include <boost/algorithm/string.hpp>
#include "dogen/test_models/cpp_model/types/base_with_object_template.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen {
namespace test_models {
namespace cpp_model {

base_with_object_template::base_with_object_template()
    : prop_2_(static_cast<int>(0)) { }

base_with_object_template::base_with_object_template(
    const int prop_2,
    const std::string& prop_0)
    : prop_2_(prop_2),
      prop_0_(prop_0) { }

void base_with_object_template::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::base_with_object_template\"" << ", "
      << "\"prop_2\": " << prop_2_ << ", "
      << "\"prop_0\": " << "\"" << tidy_up_string(prop_0_) << "\""
      << " }";
}

void base_with_object_template::swap(base_with_object_template& other) noexcept {
    using std::swap;
    swap(prop_2_, other.prop_2_);
    swap(prop_0_, other.prop_0_);
}

bool base_with_object_template::compare(const base_with_object_template& rhs) const {
    return prop_2_ == rhs.prop_2_ &&
        prop_0_ == rhs.prop_0_;
}

int base_with_object_template::prop_2() const {
    return prop_2_;
}

void base_with_object_template::prop_2(const int v) {
    prop_2_ = v;
}

const std::string& base_with_object_template::prop_0() const {
    return prop_0_;
}

std::string& base_with_object_template::prop_0() {
    return prop_0_;
}

void base_with_object_template::prop_0(const std::string& v) {
    prop_0_ = v;
}

void base_with_object_template::prop_0(const std::string&& v) {
    prop_0_ = std::move(v);
}

} } }
