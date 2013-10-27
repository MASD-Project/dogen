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
#include "dogen/sml/io/abstract_entity_io.hpp"
#include "dogen/sml/types/entity.hpp"

namespace dogen {
namespace sml {

entity::entity(
    const std::string& documentation,
    const boost::property_tree::ptree& tags,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const dogen::sml::origin_types& origin_type,
    const std::list<dogen::sml::property>& properties,
    const std::list<dogen::sml::operation>& operations,
    const boost::optional<dogen::sml::qname>& parent_name,
    const boost::optional<dogen::sml::qname>& original_parent_name,
    const std::list<dogen::sml::qname>& leaves,
    const bool is_parent,
    const unsigned int number_of_type_arguments,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_versioned,
    const bool is_comparable,
    const bool is_fluent,
    const std::list<dogen::sml::qname>& modeled_concepts,
    const bool is_aggregate_root,
    const std::list<dogen::sml::property>& identity)
    : dogen::sml::abstract_entity(documentation,
      tags,
      name,
      generation_type,
      origin_type,
      properties,
      operations,
      parent_name,
      original_parent_name,
      leaves,
      is_parent,
      number_of_type_arguments,
      is_visitable,
      is_immutable,
      is_versioned,
      is_comparable,
      is_fluent,
      modeled_concepts,
      is_aggregate_root,
      identity) { }

void entity::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::entity\"" << ", "
      << "\"__parent_0__\": ";
    abstract_entity::to_stream(s);
    s << " }";
}

void entity::swap(entity& other) noexcept {
    abstract_entity::swap(other);

}

bool entity::equals(const dogen::sml::type& other) const {
    const entity* const p(dynamic_cast<const entity* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool entity::operator==(const entity& rhs) const {
    return abstract_entity::compare(rhs);
}

entity& entity::operator=(entity other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }