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
#include "dogen/cpp/types/formattables/formattable.hpp"
#include "dogen/cpp/io/formattables/origin_types_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace cpp {
namespace formattables {

formattable::formattable()
    : origin_type_(static_cast<dogen::cpp::formattables::origin_types>(0)) { }

formattable::formattable(
    const std::string& identity,
    const dogen::cpp::formattables::origin_types origin_type)
    : identity_(identity),
      origin_type_(origin_type) { }

void formattable::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::formattable\"" << ", "
      << "\"identity\": " << "\"" << tidy_up_string(identity_) << "\"" << ", "
      << "\"origin_type\": " << origin_type_
      << " }";
}

void formattable::swap(formattable& other) noexcept {
    using std::swap;
    swap(identity_, other.identity_);
    swap(origin_type_, other.origin_type_);
}

bool formattable::compare(const formattable& rhs) const {
    return identity_ == rhs.identity_ &&
        origin_type_ == rhs.origin_type_;
}

const std::string& formattable::identity() const {
    return identity_;
}

std::string& formattable::identity() {
    return identity_;
}

void formattable::identity(const std::string& v) {
    identity_ = v;
}

void formattable::identity(const std::string&& v) {
    identity_ = std::move(v);
}

dogen::cpp::formattables::origin_types formattable::origin_type() const {
    return origin_type_;
}

void formattable::origin_type(const dogen::cpp::formattables::origin_types v) {
    origin_type_ = v;
}

} } }
