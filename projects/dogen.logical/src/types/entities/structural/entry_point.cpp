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
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/structural/entry_point.hpp"

namespace dogen::logical::entities::structural {

entry_point::entry_point(
    const dogen::identification::entities::logical_name& name,
    const std::string& documentation,
    const dogen::identification::entities::injection_provenance& provenance,
    const dogen::identification::entities::logical_id& contained_by,
    const bool in_global_module,
    const dogen::logical::entities::stereotypes& stereotypes,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::identification::entities::label>& labels,
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration)
    : dogen::logical::entities::element(
      name,
      documentation,
      provenance,
      contained_by,
      in_global_module,
      stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      generability_status,
      decoration) { }

void entry_point::accept(const element_visitor& v) const {
    v.visit(*this);
}

void entry_point::accept(element_visitor& v) const {
    v.visit(*this);
    }

void entry_point::accept(const element_visitor& v) {
    v.visit(*this);
}

void entry_point::accept(element_visitor& v) {
    v.visit(*this);
}

void entry_point::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::structural::entry_point\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << " }";
}

void entry_point::swap(entry_point& other) noexcept {
    dogen::logical::entities::element::swap(other);

}

bool entry_point::equals(const dogen::logical::entities::element& other) const {
    const entry_point* const p(dynamic_cast<const entry_point* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool entry_point::operator==(const entry_point& rhs) const {
    return dogen::logical::entities::element::compare(rhs);
}

entry_point& entry_point::operator=(entry_point other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

}
