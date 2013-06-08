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
#include "dogen/sml/types/repository.hpp"

namespace dogen {
namespace sml {

repository::repository(
    const dogen::sml::qname& name,
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const bool is_external,
    const std::vector<dogen::sml::property>& properties,
    const boost::optional<dogen::sml::qname>& parent_name,
    const boost::optional<dogen::sml::qname>& original_parent_name,
    const std::list<dogen::sml::qname>& leaves,
    const unsigned int number_of_type_arguments,
    const bool is_parent,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_versioned,
    const bool is_comparable,
    const bool is_fluent)
    : dogen::sml::typed_element(name,
      documentation,
      implementation_specific_parameters,
      is_external,
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
      is_fluent) { }

void repository::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::repository\"" << ", "
      << "\"__parent_0__\": ";
    typed_element::to_stream(s);
    s << " }";
}

void repository::swap(repository& other) noexcept {
    typed_element::swap(other);

}

bool repository::equals(const dogen::sml::model_element& other) const {
    const repository* const p(dynamic_cast<const repository* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool repository::operator==(const repository& rhs) const {
    return typed_element::compare(rhs);
}

repository& repository::operator=(repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }