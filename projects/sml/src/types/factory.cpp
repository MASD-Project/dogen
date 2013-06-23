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
#include "dogen/sml/io/typed_element_io.hpp"
#include "dogen/sml/types/factory.hpp"

namespace dogen {
namespace sml {

factory::factory(
    const dogen::sml::qname& name,
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const dogen::sml::generation_types& generation_type,
    const std::list<dogen::sml::property>& properties,
    const boost::optional<dogen::sml::qname>& parent_name,
    const boost::optional<dogen::sml::qname>& original_parent_name,
    const std::list<dogen::sml::qname>& leaves,
    const unsigned int number_of_type_arguments,
    const bool is_parent,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_versioned,
    const bool is_comparable,
    const bool is_fluent,
    const std::list<dogen::sml::qname>& modeled_concepts)
    : dogen::sml::typed_element(name,
      documentation,
      implementation_specific_parameters,
      generation_type,
      properties,
      parent_name,
      original_parent_name,
      leaves,
      number_of_type_arguments,
      is_parent,
      is_visitable,
      is_immutable,
      is_versioned,
      is_comparable,
      is_fluent,
      modeled_concepts) { }

void factory::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::factory\"" << ", "
      << "\"__parent_0__\": ";
    typed_element::to_stream(s);
    s << " }";
}

void factory::swap(factory& other) noexcept {
    typed_element::swap(other);

}

bool factory::equals(const dogen::sml::model_element& other) const {
    const factory* const p(dynamic_cast<const factory* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool factory::operator==(const factory& rhs) const {
    return typed_element::compare(rhs);
}

factory& factory::operator=(factory other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }