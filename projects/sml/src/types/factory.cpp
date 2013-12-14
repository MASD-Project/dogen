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
#include "dogen/sml/io/abstract_object_io.hpp"
#include "dogen/sml/types/factory.hpp"

namespace dogen {
namespace sml {

factory::factory(
    const dogen::sml::origin_types& origin_type,
    const std::string& documentation,
    const boost::property_tree::ptree& meta_data,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const std::list<dogen::sml::property>& all_properties,
    const std::list<dogen::sml::property>& local_properties,
    const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& inherited_properties,
    const std::list<dogen::sml::operation>& operations,
    const bool is_parent,
    const unsigned int number_of_type_arguments,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_versioned,
    const bool is_comparable,
    const bool is_fluent,
    const bool is_child,
    const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& relationships,
    const bool is_inheritance_root,
    const dogen::sml::object_types& object_type)
    : dogen::sml::abstract_object(origin_type,
      documentation,
      meta_data,
      name,
      generation_type,
      all_properties,
      local_properties,
      inherited_properties,
      operations,
      is_parent,
      number_of_type_arguments,
      is_visitable,
      is_immutable,
      is_versioned,
      is_comparable,
      is_fluent,
      is_child,
      relationships,
      is_inheritance_root,
      object_type) { }

void factory::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::factory\"" << ", "
      << "\"__parent_0__\": ";
    abstract_object::to_stream(s);
    s << " }";
}

void factory::swap(factory& other) noexcept {
    abstract_object::swap(other);

}

bool factory::equals(const dogen::sml::type& other) const {
    const factory* const p(dynamic_cast<const factory* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool factory::operator==(const factory& rhs) const {
    return abstract_object::compare(rhs);
}

factory& factory::operator=(factory other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }