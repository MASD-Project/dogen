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
#include "dogen/cpp/types/formattables/namespace_info.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

namespace_info::namespace_info(
    const std::string& identity,
    const dogen::cpp::formattables::origin_types origin_type,
    const std::string& name,
    const std::string& qualified_name,
    const std::string& documentation,
    const std::list<std::string>& namespaces,
    const dogen::cpp::settings::bundle& settings,
    const std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties>& formatter_properties)
    : dogen::cpp::formattables::entity(
      identity,
      origin_type,
      name,
      qualified_name,
      documentation,
      namespaces,
      settings,
      formatter_properties) { }

void namespace_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::formattables::namespace_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << " }";
}

void namespace_info::swap(namespace_info& other) noexcept {
    entity::swap(other);

}

bool namespace_info::equals(const dogen::cpp::formattables::formattable& other) const {
    const namespace_info* const p(dynamic_cast<const namespace_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool namespace_info::operator==(const namespace_info& rhs) const {
    return entity::compare(rhs);
}

namespace_info& namespace_info::operator=(namespace_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }
