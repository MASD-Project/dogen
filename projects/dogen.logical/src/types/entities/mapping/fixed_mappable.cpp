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
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/mapping/fixed_mappable.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::logical::entities::mapping {

fixed_mappable::fixed_mappable(
    const dogen::logical::entities::name& name,
    const std::string& documentation,
    const dogen::logical::entities::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
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
    const std::string& destination)
    : dogen::logical::entities::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      origin_element_id,
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
      destination_(destination) { }

void fixed_mappable::accept(const element_visitor& v) const {
    v.visit(*this);
}

void fixed_mappable::accept(element_visitor& v) const {
    v.visit(*this);
    }

void fixed_mappable::accept(const element_visitor& v) {
    v.visit(*this);
}

void fixed_mappable::accept(element_visitor& v) {
    v.visit(*this);
}

void fixed_mappable::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::mapping::fixed_mappable\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"destination\": " << "\"" << tidy_up_string(destination_) << "\""
      << " }";
}

void fixed_mappable::swap(fixed_mappable& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(destination_, other.destination_);
}

bool fixed_mappable::equals(const dogen::logical::entities::element& other) const {
    const fixed_mappable* const p(dynamic_cast<const fixed_mappable* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool fixed_mappable::operator==(const fixed_mappable& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        destination_ == rhs.destination_;
}

fixed_mappable& fixed_mappable::operator=(fixed_mappable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& fixed_mappable::destination() const {
    return destination_;
}

std::string& fixed_mappable::destination() {
    return destination_;
}

void fixed_mappable::destination(const std::string& v) {
    destination_ = v;
}

void fixed_mappable::destination(const std::string&& v) {
    destination_ = std::move(v);
}

}
