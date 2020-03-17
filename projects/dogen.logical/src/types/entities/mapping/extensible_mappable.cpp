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
#include "dogen.logical/io/entities/mapping/destination_io.hpp"
#include "dogen.logical/types/entities/mapping/extensible_mappable.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::mapping::destination>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::mapping {

extensible_mappable::extensible_mappable(
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
    const std::unordered_map<std::string, dogen::logical::entities::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::list<dogen::logical::entities::mapping::destination>& destinations)
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
      decoration),
      destinations_(destinations) { }

void extensible_mappable::accept(const element_visitor& v) const {
    v.visit(*this);
}

void extensible_mappable::accept(element_visitor& v) const {
    v.visit(*this);
    }

void extensible_mappable::accept(const element_visitor& v) {
    v.visit(*this);
}

void extensible_mappable::accept(element_visitor& v) {
    v.visit(*this);
}

void extensible_mappable::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::mapping::extensible_mappable\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"destinations\": " << destinations_
      << " }";
}

void extensible_mappable::swap(extensible_mappable& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(destinations_, other.destinations_);
}

bool extensible_mappable::equals(const dogen::logical::entities::element& other) const {
    const extensible_mappable* const p(dynamic_cast<const extensible_mappable* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool extensible_mappable::operator==(const extensible_mappable& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        destinations_ == rhs.destinations_;
}

extensible_mappable& extensible_mappable::operator=(extensible_mappable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::logical::entities::mapping::destination>& extensible_mappable::destinations() const {
    return destinations_;
}

std::list<dogen::logical::entities::mapping::destination>& extensible_mappable::destinations() {
    return destinations_;
}

void extensible_mappable::destinations(const std::list<dogen::logical::entities::mapping::destination>& v) {
    destinations_ = v;
}

void extensible_mappable::destinations(const std::list<dogen::logical::entities::mapping::destination>&& v) {
    destinations_ = std::move(v);
}

}
