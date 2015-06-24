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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/types/formattables/enum_info.hpp"
#include "dogen/cpp/io/formattables/enumerator_info_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::formattables::enumerator_info>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace cpp {
namespace formattables {

enum_info::enum_info(
    const std::string& identity,
    const dogen::cpp::formattables::origin_types origin_type,
    const std::string& name,
    const std::string& qualified_name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const dogen::cpp::settings::bundle& settings,
    const std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties>& formatter_properties,
    const std::list<dogen::cpp::formattables::enumerator_info>& enumerators,
    const std::string& type)
    : dogen::cpp::formattables::entity(
      identity,
      origin_type,
      name,
      qualified_name,
      documentation,
      namespaces,
      settings,
      formatter_properties),
      enumerators_(enumerators),
      type_(type) { }

void enum_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::enum_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << ", "
      << "\"enumerators\": " << enumerators_ << ", "
      << "\"type\": " << "\"" << tidy_up_string(type_) << "\""
      << " }";
}

void enum_info::swap(enum_info& other) noexcept {
    entity::swap(other);

    using std::swap;
    swap(enumerators_, other.enumerators_);
    swap(type_, other.type_);
}

bool enum_info::equals(const dogen::cpp::formattables::formattable& other) const {
    const enum_info* const p(dynamic_cast<const enum_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool enum_info::operator==(const enum_info& rhs) const {
    return entity::compare(rhs) &&
        enumerators_ == rhs.enumerators_ &&
        type_ == rhs.type_;
}

enum_info& enum_info::operator=(enum_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::cpp::formattables::enumerator_info>& enum_info::enumerators() const {
    return enumerators_;
}

std::list<dogen::cpp::formattables::enumerator_info>& enum_info::enumerators() {
    return enumerators_;
}

void enum_info::enumerators(const std::list<dogen::cpp::formattables::enumerator_info>& v) {
    enumerators_ = v;
}

void enum_info::enumerators(const std::list<dogen::cpp::formattables::enumerator_info>&& v) {
    enumerators_ = std::move(v);
}

const std::string& enum_info::type() const {
    return type_;
}

std::string& enum_info::type() {
    return type_;
}

void enum_info::type(const std::string& v) {
    type_ = v;
}

void enum_info::type(const std::string&& v) {
    type_ = std::move(v);
}

} } }
