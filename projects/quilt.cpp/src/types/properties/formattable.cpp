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
#include "dogen/quilt.cpp/types/properties/formattable.hpp"
#include "dogen/quilt.cpp/io/properties/origin_types_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

formattable::formattable()
    : origin_type_(static_cast<dogen::quilt::cpp::properties::origin_types>(0)) { }

formattable::formattable(
    const std::string& identity,
    const dogen::quilt::cpp::properties::origin_types origin_type,
    const std::string& id)
    : identity_(identity),
      origin_type_(origin_type),
      id_(id) { }

void formattable::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::properties::formattable\"" << ", "
      << "\"identity\": " << "\"" << tidy_up_string(identity_) << "\"" << ", "
      << "\"origin_type\": " << origin_type_ << ", "
      << "\"id\": " << "\"" << tidy_up_string(id_) << "\""
      << " }";
}

void formattable::swap(formattable& other) noexcept {
    using std::swap;
    swap(identity_, other.identity_);
    swap(origin_type_, other.origin_type_);
    swap(id_, other.id_);
}

bool formattable::compare(const formattable& rhs) const {
    return identity_ == rhs.identity_ &&
        origin_type_ == rhs.origin_type_ &&
        id_ == rhs.id_;
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

dogen::quilt::cpp::properties::origin_types formattable::origin_type() const {
    return origin_type_;
}

void formattable::origin_type(const dogen::quilt::cpp::properties::origin_types v) {
    origin_type_ = v;
}

const std::string& formattable::id() const {
    return id_;
}

std::string& formattable::id() {
    return id_;
}

void formattable::id(const std::string& v) {
    id_ = v;
}

void formattable::id(const std::string&& v) {
    id_ = std::move(v);
}

} } } }
