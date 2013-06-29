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
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/keyed_entity.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::sml::qname>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s << " }";
    return s;
}

}

namespace dogen {
namespace sml {

keyed_entity::keyed_entity(keyed_entity&& rhs)
    : dogen::sml::abstract_entity(
        std::forward<dogen::sml::abstract_entity>(rhs)),
      unversioned_key_(std::move(rhs.unversioned_key_)),
      versioned_key_(std::move(rhs.versioned_key_)) { }

keyed_entity::keyed_entity(
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const std::list<dogen::sml::property>& properties,
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
    const std::list<dogen::sml::property>& identity,
    const dogen::sml::qname& unversioned_key,
    const boost::optional<dogen::sml::qname>& versioned_key)
    : dogen::sml::abstract_entity(documentation,
      implementation_specific_parameters,
      name,
      generation_type,
      properties,
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
      identity),
      unversioned_key_(unversioned_key),
      versioned_key_(versioned_key) { }

void keyed_entity::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::sml::keyed_entity\"" << ", "
      << "\"__parent_0__\": ";
    abstract_entity::to_stream(s);
    s << ", "
      << "\"unversioned_key\": " << unversioned_key_ << ", "
      << "\"versioned_key\": " << versioned_key_
      << " }";
}

void keyed_entity::swap(keyed_entity& other) noexcept {
    abstract_entity::swap(other);

    using std::swap;
    swap(unversioned_key_, other.unversioned_key_);
    swap(versioned_key_, other.versioned_key_);
}

bool keyed_entity::equals(const dogen::sml::type& other) const {
    const keyed_entity* const p(dynamic_cast<const keyed_entity* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool keyed_entity::operator==(const keyed_entity& rhs) const {
    return abstract_entity::compare(rhs) &&
        unversioned_key_ == rhs.unversioned_key_ &&
        versioned_key_ == rhs.versioned_key_;
}

keyed_entity& keyed_entity::operator=(keyed_entity other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::sml::qname& keyed_entity::unversioned_key() const {
    return unversioned_key_;
}

dogen::sml::qname& keyed_entity::unversioned_key() {
    return unversioned_key_;
}

void keyed_entity::unversioned_key(const dogen::sml::qname& v) {
    unversioned_key_ = v;
}

void keyed_entity::unversioned_key(const dogen::sml::qname&& v) {
    unversioned_key_ = std::move(v);
}

const boost::optional<dogen::sml::qname>& keyed_entity::versioned_key() const {
    return versioned_key_;
}

boost::optional<dogen::sml::qname>& keyed_entity::versioned_key() {
    return versioned_key_;
}

void keyed_entity::versioned_key(const boost::optional<dogen::sml::qname>& v) {
    versioned_key_ = v;
}

void keyed_entity::versioned_key(const boost::optional<dogen::sml::qname>&& v) {
    versioned_key_ = std::move(v);
}

} }