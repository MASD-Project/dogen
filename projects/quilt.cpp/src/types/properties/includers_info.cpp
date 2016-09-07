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
#include "dogen/quilt.cpp/io/properties/entity_io.hpp"
#include "dogen/quilt.cpp/types/properties/includers_info.hpp"
#include "dogen/quilt.cpp/types/properties/formattable_visitor.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

includers_info::includers_info(
    const std::string& identity,
    const dogen::quilt::cpp::properties::origin_types origin_type,
    const std::string& id,
    const std::string& name,
    const std::string& qualified_name,
    const std::string& documentation,
    const std::list<std::string>& namespaces)
    : dogen::quilt::cpp::properties::entity(
      identity,
      origin_type,
      id,
      name,
      qualified_name,
      documentation,
      namespaces) { }

void includers_info::accept(const formattable_visitor& v) const {
    v.visit(*this);
}

void includers_info::accept(formattable_visitor& v) const {
    v.visit(*this);
    }

void includers_info::accept(const formattable_visitor& v) {
    v.visit(*this);
}

void includers_info::accept(formattable_visitor& v) {
    v.visit(*this);
}


void includers_info::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::properties::includers_info\"" << ", "
      << "\"__parent_0__\": ";
    entity::to_stream(s);
    s << " }";
}

void includers_info::swap(includers_info& other) noexcept {
    entity::swap(other);

}

bool includers_info::equals(const dogen::quilt::cpp::properties::formattable& other) const {
    const includers_info* const p(dynamic_cast<const includers_info* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool includers_info::operator==(const includers_info& rhs) const {
    return entity::compare(rhs);
}

includers_info& includers_info::operator=(includers_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } } }
