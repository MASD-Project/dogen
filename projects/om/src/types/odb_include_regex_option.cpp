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
#include "dogen/om/io/odb_option_io.hpp"
#include "dogen/om/types/odb_include_regex_option.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
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
namespace om {

odb_include_regex_option::odb_include_regex_option(
    const std::string& comment,
    const std::list<std::string>& regex)
    : dogen::om::odb_option(comment),
      regex_(regex) { }

void odb_include_regex_option::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::om::odb_include_regex_option\"" << ", "
      << "\"__parent_0__\": ";
    odb_option::to_stream(s);
    s << ", "
      << "\"regex\": " << regex_
      << " }";
}

void odb_include_regex_option::swap(odb_include_regex_option& other) noexcept {
    odb_option::swap(other);

    using std::swap;
    swap(regex_, other.regex_);
}

bool odb_include_regex_option::equals(const dogen::om::odb_option& other) const {
    const odb_include_regex_option* const p(dynamic_cast<const odb_include_regex_option* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool odb_include_regex_option::operator==(const odb_include_regex_option& rhs) const {
    return odb_option::compare(rhs) &&
        regex_ == rhs.regex_;
}

odb_include_regex_option& odb_include_regex_option::operator=(odb_include_regex_option other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& odb_include_regex_option::regex() const {
    return regex_;
}

std::list<std::string>& odb_include_regex_option::regex() {
    return regex_;
}

void odb_include_regex_option::regex(const std::list<std::string>& v) {
    regex_ = v;
}

void odb_include_regex_option::regex(const std::list<std::string>&& v) {
    regex_ = std::move(v);
}

} }