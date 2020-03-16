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
#include "dogen.logical/io/meta_model/name_io.hpp"
#include "dogen.logical/io/meta_model/element_io.hpp"
#include "dogen.logical/io/meta_model/attribute_io.hpp"
#include "dogen.logical/io/meta_model/type_parameters_io.hpp"
#include "dogen.logical/types/meta_model/element_visitor.hpp"
#include "dogen.logical/types/meta_model/structural/object.hpp"
#include "dogen.logical/io/meta_model/orm/object_properties_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::meta_model::attribute>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::logical::meta_model::name, std::list<dogen::logical::meta_model::attribute> >& v) {
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

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::logical::meta_model::name>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::meta_model::name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<bool>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::logical::meta_model::orm::object_properties>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::logical::meta_model::structural {

object::object()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)),
      is_visitation_root_(static_cast<bool>(0)),
      is_visitation_leaf_(static_cast<bool>(0)),
      is_parent_(static_cast<bool>(0)),
      is_child_(static_cast<bool>(0)),
      is_leaf_(static_cast<bool>(0)),
      is_final_(static_cast<bool>(0)),
      is_abstract_(static_cast<bool>(0)),
      in_inheritance_relationship_(static_cast<bool>(0)),
      is_associative_container_(static_cast<bool>(0)),
      provides_opaqueness_(static_cast<bool>(0)),
      can_be_primitive_underlier_(static_cast<bool>(0)) { }

object::object(object&& rhs)
    : dogen::logical::meta_model::element(
        std::forward<dogen::logical::meta_model::element>(rhs)),
      all_attributes_(std::move(rhs.all_attributes_)),
      local_attributes_(std::move(rhs.local_attributes_)),
      inherited_attributes_(std::move(rhs.inherited_attributes_)),
      is_immutable_(std::move(rhs.is_immutable_)),
      is_fluent_(std::move(rhs.is_fluent_)),
      base_visitor_(std::move(rhs.base_visitor_)),
      derived_visitor_(std::move(rhs.derived_visitor_)),
      is_visitation_root_(std::move(rhs.is_visitation_root_)),
      is_visitation_leaf_(std::move(rhs.is_visitation_leaf_)),
      transparent_associations_(std::move(rhs.transparent_associations_)),
      opaque_associations_(std::move(rhs.opaque_associations_)),
      associative_container_keys_(std::move(rhs.associative_container_keys_)),
      is_parent_(std::move(rhs.is_parent_)),
      is_child_(std::move(rhs.is_child_)),
      is_leaf_(std::move(rhs.is_leaf_)),
      is_final_(std::move(rhs.is_final_)),
      is_final_requested_(std::move(rhs.is_final_requested_)),
      is_abstract_(std::move(rhs.is_abstract_)),
      in_inheritance_relationship_(std::move(rhs.in_inheritance_relationship_)),
      root_parents_(std::move(rhs.root_parents_)),
      parents_(std::move(rhs.parents_)),
      leaves_(std::move(rhs.leaves_)),
      type_registrar_(std::move(rhs.type_registrar_)),
      type_parameters_(std::move(rhs.type_parameters_)),
      is_associative_container_(std::move(rhs.is_associative_container_)),
      object_templates_(std::move(rhs.object_templates_)),
      provides_opaqueness_(std::move(rhs.provides_opaqueness_)),
      can_be_primitive_underlier_(std::move(rhs.can_be_primitive_underlier_)),
      orm_properties_(std::move(rhs.orm_properties_)) { }

object::object(
    const dogen::logical::meta_model::name& name,
    const std::string& documentation,
    const dogen::logical::meta_model::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::meta_model::name& meta_name,
    const dogen::logical::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const std::unordered_map<std::string, dogen::logical::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<dogen::logical::meta_model::technical_space, boost::optional<dogen::logical::meta_model::decoration::element_properties> >& decoration,
    const std::list<dogen::logical::meta_model::attribute>& all_attributes,
    const std::list<dogen::logical::meta_model::attribute>& local_attributes,
    const std::unordered_map<dogen::logical::meta_model::name, std::list<dogen::logical::meta_model::attribute> >& inherited_attributes,
    const bool is_immutable,
    const bool is_fluent,
    const boost::optional<dogen::logical::meta_model::name>& base_visitor,
    const boost::optional<dogen::logical::meta_model::name>& derived_visitor,
    const bool is_visitation_root,
    const bool is_visitation_leaf,
    const std::list<dogen::logical::meta_model::name>& transparent_associations,
    const std::list<dogen::logical::meta_model::name>& opaque_associations,
    const std::list<dogen::logical::meta_model::name>& associative_container_keys,
    const bool is_parent,
    const bool is_child,
    const bool is_leaf,
    const bool is_final,
    const boost::optional<bool>& is_final_requested,
    const bool is_abstract,
    const bool in_inheritance_relationship,
    const std::list<dogen::logical::meta_model::name>& root_parents,
    const std::list<dogen::logical::meta_model::name>& parents,
    const std::list<dogen::logical::meta_model::name>& leaves,
    const boost::optional<dogen::logical::meta_model::name>& type_registrar,
    const dogen::logical::meta_model::type_parameters& type_parameters,
    const bool is_associative_container,
    const std::list<dogen::logical::meta_model::name>& object_templates,
    const bool provides_opaqueness,
    const bool can_be_primitive_underlier,
    const boost::optional<dogen::logical::meta_model::orm::object_properties>& orm_properties)
    : dogen::logical::meta_model::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      origin_element_id,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      artefact_properties,
      archetype_location_properties,
      decoration),
      all_attributes_(all_attributes),
      local_attributes_(local_attributes),
      inherited_attributes_(inherited_attributes),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      base_visitor_(base_visitor),
      derived_visitor_(derived_visitor),
      is_visitation_root_(is_visitation_root),
      is_visitation_leaf_(is_visitation_leaf),
      transparent_associations_(transparent_associations),
      opaque_associations_(opaque_associations),
      associative_container_keys_(associative_container_keys),
      is_parent_(is_parent),
      is_child_(is_child),
      is_leaf_(is_leaf),
      is_final_(is_final),
      is_final_requested_(is_final_requested),
      is_abstract_(is_abstract),
      in_inheritance_relationship_(in_inheritance_relationship),
      root_parents_(root_parents),
      parents_(parents),
      leaves_(leaves),
      type_registrar_(type_registrar),
      type_parameters_(type_parameters),
      is_associative_container_(is_associative_container),
      object_templates_(object_templates),
      provides_opaqueness_(provides_opaqueness),
      can_be_primitive_underlier_(can_be_primitive_underlier),
      orm_properties_(orm_properties) { }

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
      << "\"__type__\": " << "\"dogen::logical::meta_model::structural::object\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::meta_model::element::to_stream(s);
    s << ", "
      << "\"all_attributes\": " << all_attributes_ << ", "
      << "\"local_attributes\": " << local_attributes_ << ", "
      << "\"inherited_attributes\": " << inherited_attributes_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_fluent\": " << is_fluent_ << ", "
      << "\"base_visitor\": " << base_visitor_ << ", "
      << "\"derived_visitor\": " << derived_visitor_ << ", "
      << "\"is_visitation_root\": " << is_visitation_root_ << ", "
      << "\"is_visitation_leaf\": " << is_visitation_leaf_ << ", "
      << "\"transparent_associations\": " << transparent_associations_ << ", "
      << "\"opaque_associations\": " << opaque_associations_ << ", "
      << "\"associative_container_keys\": " << associative_container_keys_ << ", "
      << "\"is_parent\": " << is_parent_ << ", "
      << "\"is_child\": " << is_child_ << ", "
      << "\"is_leaf\": " << is_leaf_ << ", "
      << "\"is_final\": " << is_final_ << ", "
      << "\"is_final_requested\": " << is_final_requested_ << ", "
      << "\"is_abstract\": " << is_abstract_ << ", "
      << "\"in_inheritance_relationship\": " << in_inheritance_relationship_ << ", "
      << "\"root_parents\": " << root_parents_ << ", "
      << "\"parents\": " << parents_ << ", "
      << "\"leaves\": " << leaves_ << ", "
      << "\"type_registrar\": " << type_registrar_ << ", "
      << "\"type_parameters\": " << type_parameters_ << ", "
      << "\"is_associative_container\": " << is_associative_container_ << ", "
      << "\"object_templates\": " << object_templates_ << ", "
      << "\"provides_opaqueness\": " << provides_opaqueness_ << ", "
      << "\"can_be_primitive_underlier\": " << can_be_primitive_underlier_ << ", "
      << "\"orm_properties\": " << orm_properties_
      << " }";
}

void object::swap(object& other) noexcept {
    dogen::logical::meta_model::element::swap(other);

    using std::swap;
    swap(all_attributes_, other.all_attributes_);
    swap(local_attributes_, other.local_attributes_);
    swap(inherited_attributes_, other.inherited_attributes_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(base_visitor_, other.base_visitor_);
    swap(derived_visitor_, other.derived_visitor_);
    swap(is_visitation_root_, other.is_visitation_root_);
    swap(is_visitation_leaf_, other.is_visitation_leaf_);
    swap(transparent_associations_, other.transparent_associations_);
    swap(opaque_associations_, other.opaque_associations_);
    swap(associative_container_keys_, other.associative_container_keys_);
    swap(is_parent_, other.is_parent_);
    swap(is_child_, other.is_child_);
    swap(is_leaf_, other.is_leaf_);
    swap(is_final_, other.is_final_);
    swap(is_final_requested_, other.is_final_requested_);
    swap(is_abstract_, other.is_abstract_);
    swap(in_inheritance_relationship_, other.in_inheritance_relationship_);
    swap(root_parents_, other.root_parents_);
    swap(parents_, other.parents_);
    swap(leaves_, other.leaves_);
    swap(type_registrar_, other.type_registrar_);
    swap(type_parameters_, other.type_parameters_);
    swap(is_associative_container_, other.is_associative_container_);
    swap(object_templates_, other.object_templates_);
    swap(provides_opaqueness_, other.provides_opaqueness_);
    swap(can_be_primitive_underlier_, other.can_be_primitive_underlier_);
    swap(orm_properties_, other.orm_properties_);
}

bool object::equals(const dogen::logical::meta_model::element& other) const {
    const object* const p(dynamic_cast<const object* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool object::operator==(const object& rhs) const {
    return dogen::logical::meta_model::element::compare(rhs) &&
        all_attributes_ == rhs.all_attributes_ &&
        local_attributes_ == rhs.local_attributes_ &&
        inherited_attributes_ == rhs.inherited_attributes_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        base_visitor_ == rhs.base_visitor_ &&
        derived_visitor_ == rhs.derived_visitor_ &&
        is_visitation_root_ == rhs.is_visitation_root_ &&
        is_visitation_leaf_ == rhs.is_visitation_leaf_ &&
        transparent_associations_ == rhs.transparent_associations_ &&
        opaque_associations_ == rhs.opaque_associations_ &&
        associative_container_keys_ == rhs.associative_container_keys_ &&
        is_parent_ == rhs.is_parent_ &&
        is_child_ == rhs.is_child_ &&
        is_leaf_ == rhs.is_leaf_ &&
        is_final_ == rhs.is_final_ &&
        is_final_requested_ == rhs.is_final_requested_ &&
        is_abstract_ == rhs.is_abstract_ &&
        in_inheritance_relationship_ == rhs.in_inheritance_relationship_ &&
        root_parents_ == rhs.root_parents_ &&
        parents_ == rhs.parents_ &&
        leaves_ == rhs.leaves_ &&
        type_registrar_ == rhs.type_registrar_ &&
        type_parameters_ == rhs.type_parameters_ &&
        is_associative_container_ == rhs.is_associative_container_ &&
        object_templates_ == rhs.object_templates_ &&
        provides_opaqueness_ == rhs.provides_opaqueness_ &&
        can_be_primitive_underlier_ == rhs.can_be_primitive_underlier_ &&
        orm_properties_ == rhs.orm_properties_;
}

object& object::operator=(object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::logical::meta_model::attribute>& object::all_attributes() const {
    return all_attributes_;
}

std::list<dogen::logical::meta_model::attribute>& object::all_attributes() {
    return all_attributes_;
}

void object::all_attributes(const std::list<dogen::logical::meta_model::attribute>& v) {
    all_attributes_ = v;
}

void object::all_attributes(const std::list<dogen::logical::meta_model::attribute>&& v) {
    all_attributes_ = std::move(v);
}

const std::list<dogen::logical::meta_model::attribute>& object::local_attributes() const {
    return local_attributes_;
}

std::list<dogen::logical::meta_model::attribute>& object::local_attributes() {
    return local_attributes_;
}

void object::local_attributes(const std::list<dogen::logical::meta_model::attribute>& v) {
    local_attributes_ = v;
}

void object::local_attributes(const std::list<dogen::logical::meta_model::attribute>&& v) {
    local_attributes_ = std::move(v);
}

const std::unordered_map<dogen::logical::meta_model::name, std::list<dogen::logical::meta_model::attribute> >& object::inherited_attributes() const {
    return inherited_attributes_;
}

std::unordered_map<dogen::logical::meta_model::name, std::list<dogen::logical::meta_model::attribute> >& object::inherited_attributes() {
    return inherited_attributes_;
}

void object::inherited_attributes(const std::unordered_map<dogen::logical::meta_model::name, std::list<dogen::logical::meta_model::attribute> >& v) {
    inherited_attributes_ = v;
}

void object::inherited_attributes(const std::unordered_map<dogen::logical::meta_model::name, std::list<dogen::logical::meta_model::attribute> >&& v) {
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

const boost::optional<dogen::logical::meta_model::name>& object::base_visitor() const {
    return base_visitor_;
}

boost::optional<dogen::logical::meta_model::name>& object::base_visitor() {
    return base_visitor_;
}

void object::base_visitor(const boost::optional<dogen::logical::meta_model::name>& v) {
    base_visitor_ = v;
}

void object::base_visitor(const boost::optional<dogen::logical::meta_model::name>&& v) {
    base_visitor_ = std::move(v);
}

const boost::optional<dogen::logical::meta_model::name>& object::derived_visitor() const {
    return derived_visitor_;
}

boost::optional<dogen::logical::meta_model::name>& object::derived_visitor() {
    return derived_visitor_;
}

void object::derived_visitor(const boost::optional<dogen::logical::meta_model::name>& v) {
    derived_visitor_ = v;
}

void object::derived_visitor(const boost::optional<dogen::logical::meta_model::name>&& v) {
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

const std::list<dogen::logical::meta_model::name>& object::transparent_associations() const {
    return transparent_associations_;
}

std::list<dogen::logical::meta_model::name>& object::transparent_associations() {
    return transparent_associations_;
}

void object::transparent_associations(const std::list<dogen::logical::meta_model::name>& v) {
    transparent_associations_ = v;
}

void object::transparent_associations(const std::list<dogen::logical::meta_model::name>&& v) {
    transparent_associations_ = std::move(v);
}

const std::list<dogen::logical::meta_model::name>& object::opaque_associations() const {
    return opaque_associations_;
}

std::list<dogen::logical::meta_model::name>& object::opaque_associations() {
    return opaque_associations_;
}

void object::opaque_associations(const std::list<dogen::logical::meta_model::name>& v) {
    opaque_associations_ = v;
}

void object::opaque_associations(const std::list<dogen::logical::meta_model::name>&& v) {
    opaque_associations_ = std::move(v);
}

const std::list<dogen::logical::meta_model::name>& object::associative_container_keys() const {
    return associative_container_keys_;
}

std::list<dogen::logical::meta_model::name>& object::associative_container_keys() {
    return associative_container_keys_;
}

void object::associative_container_keys(const std::list<dogen::logical::meta_model::name>& v) {
    associative_container_keys_ = v;
}

void object::associative_container_keys(const std::list<dogen::logical::meta_model::name>&& v) {
    associative_container_keys_ = std::move(v);
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

const boost::optional<bool>& object::is_final_requested() const {
    return is_final_requested_;
}

boost::optional<bool>& object::is_final_requested() {
    return is_final_requested_;
}

void object::is_final_requested(const boost::optional<bool>& v) {
    is_final_requested_ = v;
}

void object::is_final_requested(const boost::optional<bool>&& v) {
    is_final_requested_ = std::move(v);
}

bool object::is_abstract() const {
    return is_abstract_;
}

void object::is_abstract(const bool v) {
    is_abstract_ = v;
}

bool object::in_inheritance_relationship() const {
    return in_inheritance_relationship_;
}

void object::in_inheritance_relationship(const bool v) {
    in_inheritance_relationship_ = v;
}

const std::list<dogen::logical::meta_model::name>& object::root_parents() const {
    return root_parents_;
}

std::list<dogen::logical::meta_model::name>& object::root_parents() {
    return root_parents_;
}

void object::root_parents(const std::list<dogen::logical::meta_model::name>& v) {
    root_parents_ = v;
}

void object::root_parents(const std::list<dogen::logical::meta_model::name>&& v) {
    root_parents_ = std::move(v);
}

const std::list<dogen::logical::meta_model::name>& object::parents() const {
    return parents_;
}

std::list<dogen::logical::meta_model::name>& object::parents() {
    return parents_;
}

void object::parents(const std::list<dogen::logical::meta_model::name>& v) {
    parents_ = v;
}

void object::parents(const std::list<dogen::logical::meta_model::name>&& v) {
    parents_ = std::move(v);
}

const std::list<dogen::logical::meta_model::name>& object::leaves() const {
    return leaves_;
}

std::list<dogen::logical::meta_model::name>& object::leaves() {
    return leaves_;
}

void object::leaves(const std::list<dogen::logical::meta_model::name>& v) {
    leaves_ = v;
}

void object::leaves(const std::list<dogen::logical::meta_model::name>&& v) {
    leaves_ = std::move(v);
}

const boost::optional<dogen::logical::meta_model::name>& object::type_registrar() const {
    return type_registrar_;
}

boost::optional<dogen::logical::meta_model::name>& object::type_registrar() {
    return type_registrar_;
}

void object::type_registrar(const boost::optional<dogen::logical::meta_model::name>& v) {
    type_registrar_ = v;
}

void object::type_registrar(const boost::optional<dogen::logical::meta_model::name>&& v) {
    type_registrar_ = std::move(v);
}

const dogen::logical::meta_model::type_parameters& object::type_parameters() const {
    return type_parameters_;
}

dogen::logical::meta_model::type_parameters& object::type_parameters() {
    return type_parameters_;
}

void object::type_parameters(const dogen::logical::meta_model::type_parameters& v) {
    type_parameters_ = v;
}

void object::type_parameters(const dogen::logical::meta_model::type_parameters&& v) {
    type_parameters_ = std::move(v);
}

bool object::is_associative_container() const {
    return is_associative_container_;
}

void object::is_associative_container(const bool v) {
    is_associative_container_ = v;
}

const std::list<dogen::logical::meta_model::name>& object::object_templates() const {
    return object_templates_;
}

std::list<dogen::logical::meta_model::name>& object::object_templates() {
    return object_templates_;
}

void object::object_templates(const std::list<dogen::logical::meta_model::name>& v) {
    object_templates_ = v;
}

void object::object_templates(const std::list<dogen::logical::meta_model::name>&& v) {
    object_templates_ = std::move(v);
}

bool object::provides_opaqueness() const {
    return provides_opaqueness_;
}

void object::provides_opaqueness(const bool v) {
    provides_opaqueness_ = v;
}

bool object::can_be_primitive_underlier() const {
    return can_be_primitive_underlier_;
}

void object::can_be_primitive_underlier(const bool v) {
    can_be_primitive_underlier_ = v;
}

const boost::optional<dogen::logical::meta_model::orm::object_properties>& object::orm_properties() const {
    return orm_properties_;
}

boost::optional<dogen::logical::meta_model::orm::object_properties>& object::orm_properties() {
    return orm_properties_;
}

void object::orm_properties(const boost::optional<dogen::logical::meta_model::orm::object_properties>& v) {
    orm_properties_ = v;
}

void object::orm_properties(const boost::optional<dogen::logical::meta_model::orm::object_properties>&& v) {
    orm_properties_ = std::move(v);
}

}
