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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/sml/io/abstract_object_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/types/abstract_entity.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::property>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace sml {

abstract_entity::abstract_entity()
    : is_aggregate_root_(static_cast<bool>(0)) { }

abstract_entity::abstract_entity(
    const dogen::sml::origin_types& origin_type,
    const std::string& documentation,
    const boost::property_tree::ptree& meta_data,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const std::list<dogen::sml::property>& all_properties,
    const std::list<dogen::sml::property>& local_properties,
    const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& inherited_properties,
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
    const bool is_child,
    const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& relationships,
    const bool is_inheritance_root,
    const bool is_aggregate_root,
    const std::list<dogen::sml::property>& identity)
    : dogen::sml::abstract_object(origin_type,
      documentation,
      meta_data,
      name,
      generation_type,
      all_properties,
      local_properties,
      inherited_properties,
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
      is_child,
      relationships,
      is_inheritance_root),
      is_aggregate_root_(is_aggregate_root),
      identity_(identity) { }

void abstract_entity::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::sml::abstract_entity\"" << ", "
      << "\"__parent_0__\": ";
    abstract_object::to_stream(s);
    s << ", "
      << "\"is_aggregate_root\": " << is_aggregate_root_ << ", "
      << "\"identity\": " << identity_
      << " }";
}

void abstract_entity::swap(abstract_entity& other) noexcept {
    abstract_object::swap(other);

    using std::swap;
    swap(is_aggregate_root_, other.is_aggregate_root_);
    swap(identity_, other.identity_);
}

bool abstract_entity::compare(const abstract_entity& rhs) const {
    return abstract_object::compare(rhs) &&
        is_aggregate_root_ == rhs.is_aggregate_root_ &&
        identity_ == rhs.identity_;
}

bool abstract_entity::is_aggregate_root() const {
    return is_aggregate_root_;
}

void abstract_entity::is_aggregate_root(const bool v) {
    is_aggregate_root_ = v;
}

const std::list<dogen::sml::property>& abstract_entity::identity() const {
    return identity_;
}

std::list<dogen::sml::property>& abstract_entity::identity() {
    return identity_;
}

void abstract_entity::identity(const std::list<dogen::sml::property>& v) {
    identity_ = v;
}

void abstract_entity::identity(const std::list<dogen::sml::property>&& v) {
    identity_ = std::move(v);
}

} }