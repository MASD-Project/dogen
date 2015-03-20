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
#include "dogen/cpp/io/settings/opaque_settings_io.hpp"
#include "dogen/cpp/types/settings/odb_settings.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<std::string, std::string>& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << "\"" << tidy_up_string(v.first) << "\"" << ", ";
    s << "\"second\": " << "\"" << tidy_up_string(v.second) << "\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<std::string, std::string> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace cpp {
namespace settings {

odb_settings::odb_settings(const std::list<std::pair<std::string, std::string> >& pragmas)
    : dogen::cpp::settings::opaque_settings(),
      pragmas_(pragmas) { }

void odb_settings::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::settings::odb_settings\"" << ", "
      << "\"__parent_0__\": ";
    opaque_settings::to_stream(s);
    s << ", "
      << "\"pragmas\": " << pragmas_
      << " }";
}

void odb_settings::swap(odb_settings& other) noexcept {
    opaque_settings::swap(other);

    using std::swap;
    swap(pragmas_, other.pragmas_);
}

bool odb_settings::equals(const dogen::cpp::settings::opaque_settings& other) const {
    const odb_settings* const p(dynamic_cast<const odb_settings* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool odb_settings::operator==(const odb_settings& rhs) const {
    return opaque_settings::compare(rhs) &&
        pragmas_ == rhs.pragmas_;
}

odb_settings& odb_settings::operator=(odb_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::pair<std::string, std::string> >& odb_settings::pragmas() const {
    return pragmas_;
}

std::list<std::pair<std::string, std::string> >& odb_settings::pragmas() {
    return pragmas_;
}

void odb_settings::pragmas(const std::list<std::pair<std::string, std::string> >& v) {
    pragmas_ = v;
}

void odb_settings::pragmas(const std::list<std::pair<std::string, std::string> >&& v) {
    pragmas_ = std::move(v);
}

} } }