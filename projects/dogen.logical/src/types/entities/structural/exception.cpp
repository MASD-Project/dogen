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
#include "dogen.logical/types/entities/structural/exception.hpp"

namespace dogen::logical::entities::structural {

exception::exception(
    const dogen::logical::entities::name& name,
    const std::string& documentation,
    const dogen::logical::entities::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::entities::name& meta_name,
    const dogen::logical::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& archetype_location_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration)
    : dogen::logical::entities::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      artefact_properties,
      archetype_location_properties,
      decoration) { }

void exception::accept(const element_visitor& v) const {
    v.visit(*this);
}

void exception::accept(element_visitor& v) const {
    v.visit(*this);
    }

void exception::accept(const element_visitor& v) {
    v.visit(*this);
}

void exception::accept(element_visitor& v) {
    v.visit(*this);
}

void exception::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::structural::exception\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << " }";
}

void exception::swap(exception& other) noexcept {
    dogen::logical::entities::element::swap(other);

}

bool exception::equals(const dogen::logical::entities::element& other) const {
    const exception* const p(dynamic_cast<const exception* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool exception::operator==(const exception& rhs) const {
    return dogen::logical::entities::element::compare(rhs);
}

exception& exception::operator=(exception other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

}
