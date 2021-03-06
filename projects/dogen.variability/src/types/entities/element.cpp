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
#include "dogen.identification/io/entities/name_io.hpp"
#include "dogen.variability/types/entities/element.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::variability::entities {

element::element(
    const dogen::identification::entities::name& name,
    const std::string& description)
    : name_(name),
      description_(description) { }

void element::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::variability::entities::element\"" << ", "
      << "\"name\": " << name_ << ", "
      << "\"description\": " << "\"" << tidy_up_string(description_) << "\""
      << " }";
}

void element::swap(element& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(description_, other.description_);
}

bool element::compare(const element& rhs) const {
    return name_ == rhs.name_ &&
        description_ == rhs.description_;
}

const dogen::identification::entities::name& element::name() const {
    return name_;
}

dogen::identification::entities::name& element::name() {
    return name_;
}

void element::name(const dogen::identification::entities::name& v) {
    name_ = v;
}

void element::name(const dogen::identification::entities::name&& v) {
    name_ = std::move(v);
}

const std::string& element::description() const {
    return description_;
}

std::string& element::description() {
    return description_;
}

void element::description(const std::string& v) {
    description_ = v;
}

void element::description(const std::string&& v) {
    description_ = std::move(v);
}

}
