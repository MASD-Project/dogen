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
#include "dogen/sml/io/object_types_io.hpp"
#include "dogen/sml/io/operation_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/relationship_types_io.hpp"
#include "dogen/sml/io/type_io.hpp"
#include "dogen/sml/types/object.hpp"

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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::operation>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::qname>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace dogen {
namespace sml {

object::object()
    : is_parent_(static_cast<bool>(0)),
      number_of_type_arguments_(static_cast<unsigned int>(0)),
      is_visitable_(static_cast<bool>(0)),
      is_immutable_(static_cast<bool>(0)),
      is_versioned_(static_cast<bool>(0)),
      is_comparable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)),
      is_child_(static_cast<bool>(0)),
      is_original_parent_visitable_(static_cast<bool>(0)),
      is_inheritance_root_(static_cast<bool>(0)),
      object_type_(static_cast<dogen::sml::object_types>(0)),
      is_aggregate_root_(static_cast<bool>(0)) { }

object::object(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::sml::qname& name,
    const dogen::sml::generation_types& generation_type,
    const dogen::sml::origin_types& origin_type,
    const boost::optional<dogen::sml::qname>& containing_module,
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
    const bool is_original_parent_visitable,
    const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& relationships,
    const bool is_inheritance_root,
    const dogen::sml::object_types& object_type,
    const bool is_aggregate_root,
    const std::list<dogen::sml::property>& identity)
    : dogen::sml::type(documentation,
      extensions,
      name,
      generation_type,
      origin_type,
      containing_module),
      all_properties_(all_properties),
      local_properties_(local_properties),
      inherited_properties_(inherited_properties),
      operations_(operations),
      is_parent_(is_parent),
      number_of_type_arguments_(number_of_type_arguments),
      is_visitable_(is_visitable),
      is_immutable_(is_immutable),
      is_versioned_(is_versioned),
      is_comparable_(is_comparable),
      is_fluent_(is_fluent),
      is_child_(is_child),
      is_original_parent_visitable_(is_original_parent_visitable),
      relationships_(relationships),
      is_inheritance_root_(is_inheritance_root),
      object_type_(object_type),
      is_aggregate_root_(is_aggregate_root),
      identity_(identity) { }

void object::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::sml::object\"" << ", "
      << "\"__parent_0__\": ";
    type::to_stream(s);
    s << ", "
      << "\"all_properties\": " << all_properties_ << ", "
      << "\"local_properties\": " << local_properties_ << ", "
      << "\"inherited_properties\": " << inherited_properties_ << ", "
      << "\"operations\": " << operations_ << ", "
      << "\"is_parent\": " << is_parent_ << ", "
      << "\"number_of_type_arguments\": " << number_of_type_arguments_ << ", "
      << "\"is_visitable\": " << is_visitable_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_versioned\": " << is_versioned_ << ", "
      << "\"is_comparable\": " << is_comparable_ << ", "
      << "\"is_fluent\": " << is_fluent_ << ", "
      << "\"is_child\": " << is_child_ << ", "
      << "\"is_original_parent_visitable\": " << is_original_parent_visitable_ << ", "
      << "\"relationships\": " << relationships_ << ", "
      << "\"is_inheritance_root\": " << is_inheritance_root_ << ", "
      << "\"object_type\": " << object_type_ << ", "
      << "\"is_aggregate_root\": " << is_aggregate_root_ << ", "
      << "\"identity\": " << identity_
      << " }";
}

void object::swap(object& other) noexcept {
    type::swap(other);

    using std::swap;
    swap(all_properties_, other.all_properties_);
    swap(local_properties_, other.local_properties_);
    swap(inherited_properties_, other.inherited_properties_);
    swap(operations_, other.operations_);
    swap(is_parent_, other.is_parent_);
    swap(number_of_type_arguments_, other.number_of_type_arguments_);
    swap(is_visitable_, other.is_visitable_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_versioned_, other.is_versioned_);
    swap(is_comparable_, other.is_comparable_);
    swap(is_fluent_, other.is_fluent_);
    swap(is_child_, other.is_child_);
    swap(is_original_parent_visitable_, other.is_original_parent_visitable_);
    swap(relationships_, other.relationships_);
    swap(is_inheritance_root_, other.is_inheritance_root_);
    swap(object_type_, other.object_type_);
    swap(is_aggregate_root_, other.is_aggregate_root_);
    swap(identity_, other.identity_);
}

bool object::equals(const dogen::sml::type& other) const {
    const object* const p(dynamic_cast<const object* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool object::operator==(const object& rhs) const {
    return type::compare(rhs) &&
        all_properties_ == rhs.all_properties_ &&
        local_properties_ == rhs.local_properties_ &&
        inherited_properties_ == rhs.inherited_properties_ &&
        operations_ == rhs.operations_ &&
        is_parent_ == rhs.is_parent_ &&
        number_of_type_arguments_ == rhs.number_of_type_arguments_ &&
        is_visitable_ == rhs.is_visitable_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_versioned_ == rhs.is_versioned_ &&
        is_comparable_ == rhs.is_comparable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        is_child_ == rhs.is_child_ &&
        is_original_parent_visitable_ == rhs.is_original_parent_visitable_ &&
        relationships_ == rhs.relationships_ &&
        is_inheritance_root_ == rhs.is_inheritance_root_ &&
        object_type_ == rhs.object_type_ &&
        is_aggregate_root_ == rhs.is_aggregate_root_ &&
        identity_ == rhs.identity_;
}

object& object::operator=(object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::sml::property>& object::all_properties() const {
    return all_properties_;
}

std::list<dogen::sml::property>& object::all_properties() {
    return all_properties_;
}

void object::all_properties(const std::list<dogen::sml::property>& v) {
    all_properties_ = v;
}

void object::all_properties(const std::list<dogen::sml::property>&& v) {
    all_properties_ = std::move(v);
}

const std::list<dogen::sml::property>& object::local_properties() const {
    return local_properties_;
}

std::list<dogen::sml::property>& object::local_properties() {
    return local_properties_;
}

void object::local_properties(const std::list<dogen::sml::property>& v) {
    local_properties_ = v;
}

void object::local_properties(const std::list<dogen::sml::property>&& v) {
    local_properties_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& object::inherited_properties() const {
    return inherited_properties_;
}

std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& object::inherited_properties() {
    return inherited_properties_;
}

void object::inherited_properties(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& v) {
    inherited_properties_ = v;
}

void object::inherited_properties(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >&& v) {
    inherited_properties_ = std::move(v);
}

const std::list<dogen::sml::operation>& object::operations() const {
    return operations_;
}

std::list<dogen::sml::operation>& object::operations() {
    return operations_;
}

void object::operations(const std::list<dogen::sml::operation>& v) {
    operations_ = v;
}

void object::operations(const std::list<dogen::sml::operation>&& v) {
    operations_ = std::move(v);
}

bool object::is_parent() const {
    return is_parent_;
}

void object::is_parent(const bool v) {
    is_parent_ = v;
}

unsigned int object::number_of_type_arguments() const {
    return number_of_type_arguments_;
}

void object::number_of_type_arguments(const unsigned int v) {
    number_of_type_arguments_ = v;
}

bool object::is_visitable() const {
    return is_visitable_;
}

void object::is_visitable(const bool v) {
    is_visitable_ = v;
}

bool object::is_immutable() const {
    return is_immutable_;
}

void object::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool object::is_versioned() const {
    return is_versioned_;
}

void object::is_versioned(const bool v) {
    is_versioned_ = v;
}

bool object::is_comparable() const {
    return is_comparable_;
}

void object::is_comparable(const bool v) {
    is_comparable_ = v;
}

bool object::is_fluent() const {
    return is_fluent_;
}

void object::is_fluent(const bool v) {
    is_fluent_ = v;
}

bool object::is_child() const {
    return is_child_;
}

void object::is_child(const bool v) {
    is_child_ = v;
}

bool object::is_original_parent_visitable() const {
    return is_original_parent_visitable_;
}

void object::is_original_parent_visitable(const bool v) {
    is_original_parent_visitable_ = v;
}

const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& object::relationships() const {
    return relationships_;
}

std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& object::relationships() {
    return relationships_;
}

void object::relationships(const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& v) {
    relationships_ = v;
}

void object::relationships(const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >&& v) {
    relationships_ = std::move(v);
}

bool object::is_inheritance_root() const {
    return is_inheritance_root_;
}

void object::is_inheritance_root(const bool v) {
    is_inheritance_root_ = v;
}

dogen::sml::object_types object::object_type() const {
    return object_type_;
}

void object::object_type(const dogen::sml::object_types& v) {
    object_type_ = v;
}

bool object::is_aggregate_root() const {
    return is_aggregate_root_;
}

void object::is_aggregate_root(const bool v) {
    is_aggregate_root_ = v;
}

const std::list<dogen::sml::property>& object::identity() const {
    return identity_;
}

std::list<dogen::sml::property>& object::identity() {
    return identity_;
}

void object::identity(const std::list<dogen::sml::property>& v) {
    identity_ = v;
}

void object::identity(const std::list<dogen::sml::property>&& v) {
    identity_ = std::move(v);
}

} }