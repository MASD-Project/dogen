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
#include "dogen/quilt.cpp/types/annotations/odb_annotations.hpp"
#include "dogen/quilt.cpp/io/annotations/opaque_annotations_io.hpp"

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
namespace quilt {
namespace cpp {
namespace annotations {

odb_annotations::odb_annotations(const std::list<std::string>& pragmas)
    : dogen::quilt::cpp::annotations::opaque_annotations(),
      pragmas_(pragmas) { }

void odb_annotations::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::annotations::odb_annotations\"" << ", "
      << "\"__parent_0__\": ";
    opaque_annotations::to_stream(s);
    s << ", "
      << "\"pragmas\": " << pragmas_
      << " }";
}

void odb_annotations::swap(odb_annotations& other) noexcept {
    opaque_annotations::swap(other);

    using std::swap;
    swap(pragmas_, other.pragmas_);
}

bool odb_annotations::equals(const dogen::quilt::cpp::annotations::opaque_annotations& other) const {
    const odb_annotations* const p(dynamic_cast<const odb_annotations* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool odb_annotations::operator==(const odb_annotations& rhs) const {
    return opaque_annotations::compare(rhs) &&
        pragmas_ == rhs.pragmas_;
}

odb_annotations& odb_annotations::operator=(odb_annotations other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& odb_annotations::pragmas() const {
    return pragmas_;
}

std::list<std::string>& odb_annotations::pragmas() {
    return pragmas_;
}

void odb_annotations::pragmas(const std::list<std::string>& v) {
    pragmas_ = v;
}

void odb_annotations::pragmas(const std::list<std::string>&& v) {
    pragmas_ = std::move(v);
}

} } } }
