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
#include "dogen/test_models/std_model/types/base.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace test_models {
namespace std_model {

base::base(const std::vector<std::string>& prop_0)
    : prop_0_(prop_0) { }

void base::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::std_model::base\"" << ", "
      << "\"prop_0\": " << prop_0_
      << " }";
}

void base::swap(base& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool base::compare(const base& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

const std::vector<std::string>& base::prop_0() const {
    return prop_0_;
}

std::vector<std::string>& base::prop_0() {
    return prop_0_;
}

void base::prop_0(const std::vector<std::string>& v) {
    prop_0_ = v;
}

void base::prop_0(const std::vector<std::string>&& v) {
    prop_0_ = std::move(v);
}

} } }
