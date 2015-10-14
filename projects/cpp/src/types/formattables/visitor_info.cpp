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
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/types/formattables/visitor_info.hpp"
#include "dogen/cpp/io/formattables/visited_type_info_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::formattables::visited_type_info>& v) {
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
namespace formattables {

visitor_info::visitor_info(
    const std::string& identity,
    const dogen::cpp::formattables::origin_types origin_type,
    const std::string& name,
    const std::string& qualified_name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const dogen::cpp::settings::bundle& settings,
    const std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties>& formatter_properties,
    const std::list<dogen::cpp::formattables::visited_type_info>& types)
    : dogen::cpp::formattables::entity(
      identity,
      origin_type,
      name,
      qualified_name,
      documentation,
      namespaces,
      settings,
      formatter_properties),
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

const std::list<dogen::cpp::formattables::visited_type_info>& visitor_info::types() const {
    return types_;
}

std::list<dogen::cpp::formattables::visited_type_info>& visitor_info::types() {
    return types_;
}

void visitor_info::types(const std::list<dogen::cpp::formattables::visited_type_info>& v) {
    types_ = v;
}

void visitor_info::types(const std::list<dogen::cpp::formattables::visited_type_info>&& v) {
    types_ = std::move(v);
}

} } }
