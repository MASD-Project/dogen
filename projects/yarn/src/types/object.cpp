/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <boost/io/ios_state.hpp>
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/yarn/io/attribute_io.hpp"
#include "dogen/yarn/io/object_types_io.hpp"
#include "dogen/yarn/io/type_parameters_io.hpp"
#include "dogen/yarn/types/element_visitor.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::yarn::attribute>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& v) {
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

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::yarn::name>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::yarn::name>& v) {
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
namespace yarn {

object::object()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)),
      is_parent_(static_cast<bool>(0)),
      is_child_(static_cast<bool>(0)),
      is_leaf_(static_cast<bool>(0)),
      is_final_(static_cast<bool>(0)),
      in_inheritance_relationship_(static_cast<bool>(0)),
      is_visitation_root_(static_cast<bool>(0)),
      is_visitation_leaf_(static_cast<bool>(0)),
      object_type_(static_cast<dogen::yarn::object_types>(0)),
      provides_opaqueness_(static_cast<bool>(0)) { }

object::object(object&& rhs)
    : dogen::yarn::element(
        std::forward<dogen::yarn::element>(rhs)),
      all_attributes_(std::move(rhs.all_attributes_)),
      local_attributes_(std::move(rhs.local_attributes_)),
      inherited_attributes_(std::move(rhs.inherited_attributes_)),
      is_immutable_(std::move(rhs.is_immutable_)),
      is_fluent_(std::move(rhs.is_fluent_)),
      is_parent_(std::move(rhs.is_parent_)),
      is_child_(std::move(rhs.is_child_)),
      is_leaf_(std::move(rhs.is_leaf_)),
      is_final_(std::move(rhs.is_final_)),
      root_parent_(std::move(rhs.root_parent_)),
      parent_(std::move(rhs.parent_)),
      leaves_(std::move(rhs.leaves_)),
      in_inheritance_relationship_(std::move(rhs.in_inheritance_relationship_)),
      transparent_associations_(std::move(rhs.transparent_associations_)),
      opaque_associations_(std::move(rhs.opaque_associations_)),
      base_visitor_(std::move(rhs.base_visitor_)),
      derived_visitor_(std::move(rhs.derived_visitor_)),
      is_visitation_root_(std::move(rhs.is_visitation_root_)),
      is_visitation_leaf_(std::move(rhs.is_visitation_leaf_)),
      type_parameters_(std::move(rhs.type_parameters_)),
      object_type_(std::move(rhs.object_type_)),
      modeled_concepts_(std::move(rhs.modeled_concepts_)),
      associative_container_keys_(std::move(rhs.associative_container_keys_)),
      provides_opaqueness_(std::move(rhs.provides_opaqueness_)) { }

object::object(
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::vector<std::string>& stereotypes,
    const bool is_element_extension,
    const std::list<dogen::yarn::attribute>& all_attributes,
    const std::list<dogen::yarn::attribute>& local_attributes,
    const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& inherited_attributes,
    const bool is_immutable,
    const bool is_fluent,
    const bool is_parent,
    const bool is_child,
    const bool is_leaf,
    const bool is_final,
    const boost::optional<dogen::yarn::name>& root_parent,
    const boost::optional<dogen::yarn::name>& parent,
    const std::list<dogen::yarn::name>& leaves,
    const bool in_inheritance_relationship,
    const std::list<dogen::yarn::name>& transparent_associations,
    const std::list<dogen::yarn::name>& opaque_associations,
    const boost::optional<dogen::yarn::name>& base_visitor,
    const boost::optional<dogen::yarn::name>& derived_visitor,
    const bool is_visitation_root,
    const bool is_visitation_leaf,
    const dogen::yarn::type_parameters& type_parameters,
    const dogen::yarn::object_types object_type,
    const std::list<dogen::yarn::name>& modeled_concepts,
    const std::list<dogen::yarn::name>& associative_container_keys,
    const bool provides_opaqueness)
    : dogen::yarn::element(
      documentation,
      annotation,
      name,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      is_element_extension),
      all_attributes_(all_attributes),
      local_attributes_(local_attributes),
      inherited_attributes_(inherited_attributes),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      is_parent_(is_parent),
      is_child_(is_child),
      is_leaf_(is_leaf),
      is_final_(is_final),
      root_parent_(root_parent),
      parent_(parent),
      leaves_(leaves),
      in_inheritance_relationship_(in_inheritance_relationship),
      transparent_associations_(transparent_associations),
      opaque_associations_(opaque_associations),
      base_visitor_(base_visitor),
      derived_visitor_(derived_visitor),
      is_visitation_root_(is_visitation_root),
      is_visitation_leaf_(is_visitation_leaf),
      type_parameters_(type_parameters),
      object_type_(object_type),
      modeled_concepts_(modeled_concepts),
      associative_container_keys_(associative_container_keys),
      provides_opaqueness_(provides_opaqueness) { }

void object::accept(const element_visitor& v) const {
    v.visit(*this);
}

void object::accept(element_visitor& v) const {
    v.visit(*this);
    }

void object::accept(const element_visitor& v) {
    v.visit(*this);
}

void object::accept(element_visitor& v) {
    v.visit(*this);
}


void object::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::object\"" << ", "
      << "\"__parent_0__\": ";
    element::to_stream(s);
    s << ", "
      << "\"all_attributes\": " << all_attributes_ << ", "
      << "\"local_attributes\": " << local_attributes_ << ", "
      << "\"inherited_attributes\": " << inherited_attributes_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_fluent\": " << is_fluent_ << ", "
      << "\"is_parent\": " << is_parent_ << ", "
      << "\"is_child\": " << is_child_ << ", "
      << "\"is_leaf\": " << is_leaf_ << ", "
      << "\"is_final\": " << is_final_ << ", "
      << "\"root_parent\": " << root_parent_ << ", "
      << "\"parent\": " << parent_ << ", "
      << "\"leaves\": " << leaves_ << ", "
      << "\"in_inheritance_relationship\": " << in_inheritance_relationship_ << ", "
      << "\"transparent_associations\": " << transparent_associations_ << ", "
      << "\"opaque_associations\": " << opaque_associations_ << ", "
      << "\"base_visitor\": " << base_visitor_ << ", "
      << "\"derived_visitor\": " << derived_visitor_ << ", "
      << "\"is_visitation_root\": " << is_visitation_root_ << ", "
      << "\"is_visitation_leaf\": " << is_visitation_leaf_ << ", "
      << "\"type_parameters\": " << type_parameters_ << ", "
      << "\"object_type\": " << object_type_ << ", "
      << "\"modeled_concepts\": " << modeled_concepts_ << ", "
      << "\"associative_container_keys\": " << associative_container_keys_ << ", "
      << "\"provides_opaqueness\": " << provides_opaqueness_
      << " }";
}

void object::swap(object& other) noexcept {
    element::swap(other);

    using std::swap;
    swap(all_attributes_, other.all_attributes_);
    swap(local_attributes_, other.local_attributes_);
    swap(inherited_attributes_, other.inherited_attributes_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(is_parent_, other.is_parent_);
    swap(is_child_, other.is_child_);
    swap(is_leaf_, other.is_leaf_);
    swap(is_final_, other.is_final_);
    swap(root_parent_, other.root_parent_);
    swap(parent_, other.parent_);
    swap(leaves_, other.leaves_);
    swap(in_inheritance_relationship_, other.in_inheritance_relationship_);
    swap(transparent_associations_, other.transparent_associations_);
    swap(opaque_associations_, other.opaque_associations_);
    swap(base_visitor_, other.base_visitor_);
    swap(derived_visitor_, other.derived_visitor_);
    swap(is_visitation_root_, other.is_visitation_root_);
    swap(is_visitation_leaf_, other.is_visitation_leaf_);
    swap(type_parameters_, other.type_parameters_);
    swap(object_type_, other.object_type_);
    swap(modeled_concepts_, other.modeled_concepts_);
    swap(associative_container_keys_, other.associative_container_keys_);
    swap(provides_opaqueness_, other.provides_opaqueness_);
}

bool object::equals(const dogen::yarn::element& other) const {
    const object* const p(dynamic_cast<const object* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool object::operator==(const object& rhs) const {
    return element::compare(rhs) &&
        all_attributes_ == rhs.all_attributes_ &&
        local_attributes_ == rhs.local_attributes_ &&
        inherited_attributes_ == rhs.inherited_attributes_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        is_parent_ == rhs.is_parent_ &&
        is_child_ == rhs.is_child_ &&
        is_leaf_ == rhs.is_leaf_ &&
        is_final_ == rhs.is_final_ &&
        root_parent_ == rhs.root_parent_ &&
        parent_ == rhs.parent_ &&
        leaves_ == rhs.leaves_ &&
        in_inheritance_relationship_ == rhs.in_inheritance_relationship_ &&
        transparent_associations_ == rhs.transparent_associations_ &&
        opaque_associations_ == rhs.opaque_associations_ &&
        base_visitor_ == rhs.base_visitor_ &&
        derived_visitor_ == rhs.derived_visitor_ &&
        is_visitation_root_ == rhs.is_visitation_root_ &&
        is_visitation_leaf_ == rhs.is_visitation_leaf_ &&
        type_parameters_ == rhs.type_parameters_ &&
        object_type_ == rhs.object_type_ &&
        modeled_concepts_ == rhs.modeled_concepts_ &&
        associative_container_keys_ == rhs.associative_container_keys_ &&
        provides_opaqueness_ == rhs.provides_opaqueness_;
}

object& object::operator=(object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::yarn::attribute>& object::all_attributes() const {
    return all_attributes_;
}

std::list<dogen::yarn::attribute>& object::all_attributes() {
    return all_attributes_;
}

void object::all_attributes(const std::list<dogen::yarn::attribute>& v) {
    all_attributes_ = v;
}

void object::all_attributes(const std::list<dogen::yarn::attribute>&& v) {
    all_attributes_ = std::move(v);
}

const std::list<dogen::yarn::attribute>& object::local_attributes() const {
    return local_attributes_;
}

std::list<dogen::yarn::attribute>& object::local_attributes() {
    return local_attributes_;
}

void object::local_attributes(const std::list<dogen::yarn::attribute>& v) {
    local_attributes_ = v;
}

void object::local_attributes(const std::list<dogen::yarn::attribute>&& v) {
    local_attributes_ = std::move(v);
}

const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& object::inherited_attributes() const {
    return inherited_attributes_;
}

std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& object::inherited_attributes() {
    return inherited_attributes_;
}

void object::inherited_attributes(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& v) {
    inherited_attributes_ = v;
}

void object::inherited_attributes(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >&& v) {
    inherited_attributes_ = std::move(v);
}

bool object::is_immutable() const {
    return is_immutable_;
}

void object::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool object::is_fluent() const {
    return is_fluent_;
}

void object::is_fluent(const bool v) {
    is_fluent_ = v;
}

bool object::is_parent() const {
    return is_parent_;
}

void object::is_parent(const bool v) {
    is_parent_ = v;
}

bool object::is_child() const {
    return is_child_;
}

void object::is_child(const bool v) {
    is_child_ = v;
}

bool object::is_leaf() const {
    return is_leaf_;
}

void object::is_leaf(const bool v) {
    is_leaf_ = v;
}

bool object::is_final() const {
    return is_final_;
}

void object::is_final(const bool v) {
    is_final_ = v;
}

const boost::optional<dogen::yarn::name>& object::root_parent() const {
    return root_parent_;
}

boost::optional<dogen::yarn::name>& object::root_parent() {
    return root_parent_;
}

void object::root_parent(const boost::optional<dogen::yarn::name>& v) {
    root_parent_ = v;
}

void object::root_parent(const boost::optional<dogen::yarn::name>&& v) {
    root_parent_ = std::move(v);
}

const boost::optional<dogen::yarn::name>& object::parent() const {
    return parent_;
}

boost::optional<dogen::yarn::name>& object::parent() {
    return parent_;
}

void object::parent(const boost::optional<dogen::yarn::name>& v) {
    parent_ = v;
}

void object::parent(const boost::optional<dogen::yarn::name>&& v) {
    parent_ = std::move(v);
}

const std::list<dogen::yarn::name>& object::leaves() const {
    return leaves_;
}

std::list<dogen::yarn::name>& object::leaves() {
    return leaves_;
}

void object::leaves(const std::list<dogen::yarn::name>& v) {
    leaves_ = v;
}

void object::leaves(const std::list<dogen::yarn::name>&& v) {
    leaves_ = std::move(v);
}

bool object::in_inheritance_relationship() const {
    return in_inheritance_relationship_;
}

void object::in_inheritance_relationship(const bool v) {
    in_inheritance_relationship_ = v;
}

const std::list<dogen::yarn::name>& object::transparent_associations() const {
    return transparent_associations_;
}

std::list<dogen::yarn::name>& object::transparent_associations() {
    return transparent_associations_;
}

void object::transparent_associations(const std::list<dogen::yarn::name>& v) {
    transparent_associations_ = v;
}

void object::transparent_associations(const std::list<dogen::yarn::name>&& v) {
    transparent_associations_ = std::move(v);
}

const std::list<dogen::yarn::name>& object::opaque_associations() const {
    return opaque_associations_;
}

std::list<dogen::yarn::name>& object::opaque_associations() {
    return opaque_associations_;
}

void object::opaque_associations(const std::list<dogen::yarn::name>& v) {
    opaque_associations_ = v;
}

void object::opaque_associations(const std::list<dogen::yarn::name>&& v) {
    opaque_associations_ = std::move(v);
}

const boost::optional<dogen::yarn::name>& object::base_visitor() const {
    return base_visitor_;
}

boost::optional<dogen::yarn::name>& object::base_visitor() {
    return base_visitor_;
}

void object::base_visitor(const boost::optional<dogen::yarn::name>& v) {
    base_visitor_ = v;
}

void object::base_visitor(const boost::optional<dogen::yarn::name>&& v) {
    base_visitor_ = std::move(v);
}

const boost::optional<dogen::yarn::name>& object::derived_visitor() const {
    return derived_visitor_;
}

boost::optional<dogen::yarn::name>& object::derived_visitor() {
    return derived_visitor_;
}

void object::derived_visitor(const boost::optional<dogen::yarn::name>& v) {
    derived_visitor_ = v;
}

void object::derived_visitor(const boost::optional<dogen::yarn::name>&& v) {
    derived_visitor_ = std::move(v);
}

bool object::is_visitation_root() const {
    return is_visitation_root_;
}

void object::is_visitation_root(const bool v) {
    is_visitation_root_ = v;
}

bool object::is_visitation_leaf() const {
    return is_visitation_leaf_;
}

void object::is_visitation_leaf(const bool v) {
    is_visitation_leaf_ = v;
}

const dogen::yarn::type_parameters& object::type_parameters() const {
    return type_parameters_;
}

dogen::yarn::type_parameters& object::type_parameters() {
    return type_parameters_;
}

void object::type_parameters(const dogen::yarn::type_parameters& v) {
    type_parameters_ = v;
}

void object::type_parameters(const dogen::yarn::type_parameters&& v) {
    type_parameters_ = std::move(v);
}

dogen::yarn::object_types object::object_type() const {
    return object_type_;
}

void object::object_type(const dogen::yarn::object_types v) {
    object_type_ = v;
}

const std::list<dogen::yarn::name>& object::modeled_concepts() const {
    return modeled_concepts_;
}

std::list<dogen::yarn::name>& object::modeled_concepts() {
    return modeled_concepts_;
}

void object::modeled_concepts(const std::list<dogen::yarn::name>& v) {
    modeled_concepts_ = v;
}

void object::modeled_concepts(const std::list<dogen::yarn::name>&& v) {
    modeled_concepts_ = std::move(v);
}

const std::list<dogen::yarn::name>& object::associative_container_keys() const {
    return associative_container_keys_;
}

std::list<dogen::yarn::name>& object::associative_container_keys() {
    return associative_container_keys_;
}

void object::associative_container_keys(const std::list<dogen::yarn::name>& v) {
    associative_container_keys_ = v;
}

void object::associative_container_keys(const std::list<dogen::yarn::name>&& v) {
    associative_container_keys_ = std::move(v);
}

bool object::provides_opaqueness() const {
    return provides_opaqueness_;
}

void object::provides_opaqueness(const bool v) {
    provides_opaqueness_ = v;
}

} }
