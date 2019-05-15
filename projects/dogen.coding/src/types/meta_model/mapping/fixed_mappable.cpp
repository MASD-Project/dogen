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
#include "dogen.coding/io/meta_model/element_io.hpp"
#include "dogen.coding/io/meta_model/name_tree_io.hpp"
#include "dogen.coding/types/meta_model/element_visitor.hpp"
#include "dogen.coding/types/meta_model/mapping/fixed_mappable.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::coding::meta_model::mapping {

fixed_mappable::fixed_mappable(
    const dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const dogen::coding::meta_model::origin_types origin_type,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::coding::meta_model::name& meta_name,
    const dogen::coding::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const bool is_element_extension,
    const std::unordered_map<std::string, dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<dogen::coding::meta_model::decoration::element_properties>& decoration,
    const std::string& unparsed_destination,
    const dogen::coding::meta_model::name_tree& destination)
    : dogen::coding::meta_model::element(
      name,
      documentation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      is_element_extension,
      artefact_properties,
      archetype_location_properties,
      decoration),
      unparsed_destination_(unparsed_destination),
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
      << "\"__type__\": " << "\"dogen::coding::meta_model::mapping::fixed_mappable\"" << ", "
      << "\"__parent_0__\": ";
    dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"unparsed_destination\": " << "\"" << tidy_up_string(unparsed_destination_) << "\"" << ", "
      << "\"destination\": " << destination_
      << " }";
}

void fixed_mappable::swap(fixed_mappable& other) noexcept {
    dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(unparsed_destination_, other.unparsed_destination_);
    swap(destination_, other.destination_);
}

bool fixed_mappable::equals(const dogen::coding::meta_model::element& other) const {
    const fixed_mappable* const p(dynamic_cast<const fixed_mappable* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool fixed_mappable::operator==(const fixed_mappable& rhs) const {
    return dogen::coding::meta_model::element::compare(rhs) &&
        unparsed_destination_ == rhs.unparsed_destination_ &&
        destination_ == rhs.destination_;
}

fixed_mappable& fixed_mappable::operator=(fixed_mappable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& fixed_mappable::unparsed_destination() const {
    return unparsed_destination_;
}

std::string& fixed_mappable::unparsed_destination() {
    return unparsed_destination_;
}

void fixed_mappable::unparsed_destination(const std::string& v) {
    unparsed_destination_ = v;
}

void fixed_mappable::unparsed_destination(const std::string&& v) {
    unparsed_destination_ = std::move(v);
}

const dogen::coding::meta_model::name_tree& fixed_mappable::destination() const {
    return destination_;
}

dogen::coding::meta_model::name_tree& fixed_mappable::destination() {
    return destination_;
}

void fixed_mappable::destination(const dogen::coding::meta_model::name_tree& v) {
    destination_ = v;
}

void fixed_mappable::destination(const dogen::coding::meta_model::name_tree&& v) {
    destination_ = std::move(v);
}

}
