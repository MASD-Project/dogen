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
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/typed_element_io.hpp"
#include "dogen/sml/types/entity.hpp"

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

entity::entity()
    : is_aggregate_root_(static_cast<bool>(0)) { }

entity::entity(entity&& rhs)
    : dogen::sml::typed_element(
        std::forward<dogen::sml::typed_element>(rhs)),
      is_aggregate_root_(std::move(rhs.is_aggregate_root_)),
      unversioned_key_(std::move(rhs.unversioned_key_)),
      versioned_key_(std::move(rhs.versioned_key_)) { }

entity::entity(
    const dogen::sml::qname& name,
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const dogen::sml::generation_types& generation_type,
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
    const bool is_fluent,
    const std::list<dogen::sml::qname>& modeled_concepts,
    const bool is_aggregate_root,
    const dogen::sml::qname& unversioned_key,
    const boost::optional<dogen::sml::qname>& versioned_key)
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
      modeled_concepts),
      is_aggregate_root_(is_aggregate_root),
      unversioned_key_(unversioned_key),
      versioned_key_(versioned_key) { }

void entity::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::sml::entity\"" << ", "
      << "\"__parent_0__\": ";
    typed_element::to_stream(s);
    s << ", "
      << "\"is_aggregate_root\": " << is_aggregate_root_ << ", "
      << "\"unversioned_key\": " << unversioned_key_ << ", "
      << "\"versioned_key\": " << versioned_key_
      << " }";
}

void entity::swap(entity& other) noexcept {
    typed_element::swap(other);

    using std::swap;
    swap(is_aggregate_root_, other.is_aggregate_root_);
    swap(unversioned_key_, other.unversioned_key_);
    swap(versioned_key_, other.versioned_key_);
}

bool entity::equals(const dogen::sml::model_element& other) const {
    const entity* const p(dynamic_cast<const entity* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool entity::operator==(const entity& rhs) const {
    return typed_element::compare(rhs) &&
        is_aggregate_root_ == rhs.is_aggregate_root_ &&
        unversioned_key_ == rhs.unversioned_key_ &&
        versioned_key_ == rhs.versioned_key_;
}

entity& entity::operator=(entity other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool entity::is_aggregate_root() const {
    return is_aggregate_root_;
}

void entity::is_aggregate_root(const bool v) {
    is_aggregate_root_ = v;
}

const dogen::sml::qname& entity::unversioned_key() const {
    return unversioned_key_;
}

dogen::sml::qname& entity::unversioned_key() {
    return unversioned_key_;
}

void entity::unversioned_key(const dogen::sml::qname& v) {
    unversioned_key_ = v;
}

void entity::unversioned_key(const dogen::sml::qname&& v) {
    unversioned_key_ = std::move(v);
}

const boost::optional<dogen::sml::qname>& entity::versioned_key() const {
    return versioned_key_;
}

boost::optional<dogen::sml::qname>& entity::versioned_key() {
    return versioned_key_;
}

void entity::versioned_key(const boost::optional<dogen::sml::qname>& v) {
    versioned_key_ = v;
}

void entity::versioned_key(const boost::optional<dogen::sml::qname>&& v) {
    versioned_key_ = std::move(v);
}

} }