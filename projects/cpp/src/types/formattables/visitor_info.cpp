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
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/types/formattables/visitor_info.hpp"


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
namespace cpp {
namespace formattables {

visitor_info::visitor_info(
    const std::string& identity,
    const std::unordered_map<std::string, boost::filesystem::path>& file_path_by_formatter_name,
    const std::string& name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const std::unordered_map<std::string, boost::filesystem::path>& include_path_by_formatter_name,
    const std::unordered_map<std::string, dogen::cpp::formattables::includes>& includes_by_formatter_name,
    const std::list<std::string>& types)
    : dogen::cpp::formattables::entity(identity,
      file_path_by_formatter_name,
      name,
      documentation,
      namespaces,
      include_path_by_formatter_name,
      includes_by_formatter_name),
      types_(types) { }

void visitor_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::visitor_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << ", "
      << "\"types\": " << types_
      << " }";
}

void visitor_info::swap(visitor_info& other) noexcept {
    entity::swap(other);

    using std::swap;
    swap(types_, other.types_);
}

bool visitor_info::equals(const dogen::cpp::formattables::formattable& other) const {
    const visitor_info* const p(dynamic_cast<const visitor_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool visitor_info::operator==(const visitor_info& rhs) const {
    return entity::compare(rhs) &&
        types_ == rhs.types_;
}

visitor_info& visitor_info::operator=(visitor_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& visitor_info::types() const {
    return types_;
}

std::list<std::string>& visitor_info::types() {
    return types_;
}

void visitor_info::types(const std::list<std::string>& v) {
    types_ = v;
}

void visitor_info::types(const std::list<std::string>&& v) {
    types_ = std::move(v);
}

} } }