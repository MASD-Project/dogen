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
#include "dogen/sml/io/value_types_io.hpp"
#include "dogen/sml/types/value.hpp"

namespace dogen {
namespace sml {

value::value()
    : type_(static_cast<dogen::sml::value_types>(0)) { }

value::value(
    const dogen::sml::qname& name,
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const bool is_external,
    const boost::optional<dogen::sml::qname>& parent_name,
    const boost::optional<dogen::sml::qname>& original_parent_name,
    const std::vector<dogen::sml::property>& properties,
    const std::list<dogen::sml::qname>& leaves,
    const unsigned int number_of_type_arguments,
    const bool is_visitable,
    const bool is_parent,
    const bool is_immutable,
    const bool is_versioned,
    const bool is_comparable,
    const bool is_fluent,
    const dogen::sml::value_types& type)
    : dogen::sml::typed_element(name,
      documentation,
      implementation_specific_parameters,
      is_external,
      parent_name,
      original_parent_name,
      properties,
      leaves,
      number_of_type_arguments,
      is_visitable,
      is_parent,
      is_immutable,
      is_versioned,
      is_comparable,
      is_fluent),
      type_(type) { }

void value::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::value\"" << ", "
      << "\"__parent_0__\": ";
    typed_element::to_stream(s);
    s << ", "
      << "\"type\": " << type_
      << " }";
}

void value::swap(value& other) noexcept {
    typed_element::swap(other);

    using std::swap;
    swap(type_, other.type_);
}

bool value::equals(const dogen::sml::model_element& other) const {
    const value* const p(dynamic_cast<const value* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool value::operator==(const value& rhs) const {
    return typed_element::compare(rhs) &&
        type_ == rhs.type_;
}

value& value::operator=(value other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::sml::value_types value::type() const {
    return type_;
}

void value::type(const dogen::sml::value_types& v) {
    type_ = v;
}

} }