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
#include "dogen/sml/io/service_types_io.hpp"
#include "dogen/sml/types/service.hpp"

namespace dogen {
namespace sml {

service::service()
    : type_(static_cast<dogen::sml::service_types>(0)) { }

service::service(
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
    const dogen::sml::service_types& type)
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
      is_inheritance_root),
      type_(type) { }

void service::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::service\"" << ", "
      << "\"__parent_0__\": ";
    abstract_object::to_stream(s);
    s << ", "
      << "\"type\": " << type_
      << " }";
}

void service::swap(service& other) noexcept {
    abstract_object::swap(other);

    using std::swap;
    swap(type_, other.type_);
}

bool service::equals(const dogen::sml::type& other) const {
    const service* const p(dynamic_cast<const service* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool service::operator==(const service& rhs) const {
    return abstract_object::compare(rhs) &&
        type_ == rhs.type_;
}

service& service::operator=(service other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::sml::service_types service::type() const {
    return type_;
}

void service::type(const dogen::sml::service_types& v) {
    type_ = v;
}

} }