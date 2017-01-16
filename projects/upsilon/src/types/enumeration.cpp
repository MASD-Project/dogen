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
#include "dogen/upsilon/io/type_io.hpp"
#include "dogen/upsilon/types/enumeration.hpp"
#include "dogen/upsilon/types/type_visitor.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
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
namespace upsilon {

enumeration::enumeration(
    const dogen::upsilon::name& name,
    const dogen::upsilon::name& extends,
    const std::string& comment,
    const std::vector<std::string>& tag_refs,
    const std::string& pof_id,
    const std::vector<std::string>& values,
    const std::string& default_value)
    : dogen::upsilon::type(
      name,
      extends,
      comment,
      tag_refs,
      pof_id),
      values_(values),
      default_value_(default_value) { }

void enumeration::accept(const type_visitor& v) const {
    v.visit(*this);
}

void enumeration::accept(type_visitor& v) const {
    v.visit(*this);
    }

void enumeration::accept(const type_visitor& v) {
    v.visit(*this);
}

void enumeration::accept(type_visitor& v) {
    v.visit(*this);
}

void enumeration::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::upsilon::enumeration\"" << ", "
      << "\"__parent_0__\": ";
    dogen::upsilon::type::to_stream(s);
    s << ", "
      << "\"values\": " << values_ << ", "
      << "\"default_value\": " << "\"" << tidy_up_string(default_value_) << "\""
      << " }";
}

void enumeration::swap(enumeration& other) noexcept {
    dogen::upsilon::type::swap(other);

    using std::swap;
    swap(values_, other.values_);
    swap(default_value_, other.default_value_);
}

bool enumeration::equals(const dogen::upsilon::type& other) const {
    const enumeration* const p(dynamic_cast<const enumeration* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool enumeration::operator==(const enumeration& rhs) const {
    return dogen::upsilon::type::compare(rhs) &&
        values_ == rhs.values_ &&
        default_value_ == rhs.default_value_;
}

enumeration& enumeration::operator=(enumeration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<std::string>& enumeration::values() const {
    return values_;
}

std::vector<std::string>& enumeration::values() {
    return values_;
}

void enumeration::values(const std::vector<std::string>& v) {
    values_ = v;
}

void enumeration::values(const std::vector<std::string>&& v) {
    values_ = std::move(v);
}

const std::string& enumeration::default_value() const {
    return default_value_;
}

std::string& enumeration::default_value() {
    return default_value_;
}

void enumeration::default_value(const std::string& v) {
    default_value_ = v;
}

void enumeration::default_value(const std::string&& v) {
    default_value_ = std::move(v);
}

} }
