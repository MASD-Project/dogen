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
#include "dogen/yarn/io/property_io.hpp"
#include "dogen/yarn/io/object_types_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::yarn::property>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& v) {
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
      is_final_(static_cast<bool>(0)),
      is_visitable_(static_cast<bool>(0)),
      is_root_parent_visitable_(static_cast<bool>(0)),
      object_type_(static_cast<dogen::yarn::object_types>(0)) { }

object::object(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const dogen::yarn::name& name,
    const dogen::yarn::generation_types generation_type,
    const dogen::yarn::origin_types origin_type,
    const std::string& original_model_name,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::list<dogen::yarn::property>& all_properties,
    const std::list<dogen::yarn::property>& local_properties,
    const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& inherited_properties,
    const bool is_immutable,
    const bool is_fluent,
    const bool is_parent,
    const bool is_child,
    const bool is_final,
    const std::list<dogen::yarn::name>& root_parents,
    const std::list<dogen::yarn::name>& parents,
    const std::list<dogen::yarn::name>& leaves,
    const std::list<dogen::yarn::name>& regular_associations,
    const std::list<dogen::yarn::name>& weak_associations,
    const bool is_visitable,
    const bool is_root_parent_visitable,
    const std::list<dogen::yarn::name>& visitable_by,
    const dogen::yarn::object_types object_type,
    const std::list<dogen::yarn::name>& modeled_concepts,
    const std::list<dogen::yarn::name>& hash_container_keys)
    : dogen::yarn::element(
      documentation,
      extensions,
      name,
      generation_type,
      origin_type,
      original_model_name,
      contained_by,
      in_global_module),
      all_properties_(all_properties),
      local_properties_(local_properties),
      inherited_properties_(inherited_properties),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      is_parent_(is_parent),
      is_child_(is_child),
      is_final_(is_final),
      root_parents_(root_parents),
      parents_(parents),
      leaves_(leaves),
      regular_associations_(regular_associations),
      weak_associations_(weak_associations),
      is_visitable_(is_visitable),
      is_root_parent_visitable_(is_root_parent_visitable),
      visitable_by_(visitable_by),
      object_type_(object_type),
      modeled_concepts_(modeled_concepts),
      hash_container_keys_(hash_container_keys) { }

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
      << "\"all_properties\": " << all_properties_ << ", "
      << "\"local_properties\": " << local_properties_ << ", "
      << "\"inherited_properties\": " << inherited_properties_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_fluent\": " << is_fluent_ << ", "
      << "\"is_parent\": " << is_parent_ << ", "
      << "\"is_child\": " << is_child_ << ", "
      << "\"is_final\": " << is_final_ << ", "
      << "\"root_parents\": " << root_parents_ << ", "
      << "\"parents\": " << parents_ << ", "
      << "\"leaves\": " << leaves_ << ", "
      << "\"regular_associations\": " << regular_associations_ << ", "
      << "\"weak_associations\": " << weak_associations_ << ", "
      << "\"is_visitable\": " << is_visitable_ << ", "
      << "\"is_root_parent_visitable\": " << is_root_parent_visitable_ << ", "
      << "\"visitable_by\": " << visitable_by_ << ", "
      << "\"object_type\": " << object_type_ << ", "
      << "\"modeled_concepts\": " << modeled_concepts_ << ", "
      << "\"hash_container_keys\": " << hash_container_keys_
      << " }";
}

void object::swap(object& other) noexcept {
    element::swap(other);

    using std::swap;
    swap(all_properties_, other.all_properties_);
    swap(local_properties_, other.local_properties_);
    swap(inherited_properties_, other.inherited_properties_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(is_parent_, other.is_parent_);
    swap(is_child_, other.is_child_);
    swap(is_final_, other.is_final_);
    swap(root_parents_, other.root_parents_);
    swap(parents_, other.parents_);
    swap(leaves_, other.leaves_);
    swap(regular_associations_, other.regular_associations_);
    swap(weak_associations_, other.weak_associations_);
    swap(is_visitable_, other.is_visitable_);
    swap(is_root_parent_visitable_, other.is_root_parent_visitable_);
    swap(visitable_by_, other.visitable_by_);
    swap(object_type_, other.object_type_);
    swap(modeled_concepts_, other.modeled_concepts_);
    swap(hash_container_keys_, other.hash_container_keys_);
}

bool object::equals(const dogen::yarn::element& other) const {
    const object* const p(dynamic_cast<const object* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool object::operator==(const object& rhs) const {
    return element::compare(rhs) &&
        all_properties_ == rhs.all_properties_ &&
        local_properties_ == rhs.local_properties_ &&
        inherited_properties_ == rhs.inherited_properties_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        is_parent_ == rhs.is_parent_ &&
        is_child_ == rhs.is_child_ &&
        is_final_ == rhs.is_final_ &&
        root_parents_ == rhs.root_parents_ &&
        parents_ == rhs.parents_ &&
        leaves_ == rhs.leaves_ &&
        regular_associations_ == rhs.regular_associations_ &&
        weak_associations_ == rhs.weak_associations_ &&
        is_visitable_ == rhs.is_visitable_ &&
        is_root_parent_visitable_ == rhs.is_root_parent_visitable_ &&
        visitable_by_ == rhs.visitable_by_ &&
        object_type_ == rhs.object_type_ &&
        modeled_concepts_ == rhs.modeled_concepts_ &&
        hash_container_keys_ == rhs.hash_container_keys_;
}

object& object::operator=(object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::yarn::property>& object::all_properties() const {
    return all_properties_;
}

std::list<dogen::yarn::property>& object::all_properties() {
    return all_properties_;
}

void object::all_properties(const std::list<dogen::yarn::property>& v) {
    all_properties_ = v;
}

void object::all_properties(const std::list<dogen::yarn::property>&& v) {
    all_properties_ = std::move(v);
}

const std::list<dogen::yarn::property>& object::local_properties() const {
    return local_properties_;
}

std::list<dogen::yarn::property>& object::local_properties() {
    return local_properties_;
}

void object::local_properties(const std::list<dogen::yarn::property>& v) {
    local_properties_ = v;
}

void object::local_properties(const std::list<dogen::yarn::property>&& v) {
    local_properties_ = std::move(v);
}

const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& object::inherited_properties() const {
    return inherited_properties_;
}

std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& object::inherited_properties() {
    return inherited_properties_;
}

void object::inherited_properties(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& v) {
    inherited_properties_ = v;
}

void object::inherited_properties(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >&& v) {
    inherited_properties_ = std::move(v);
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

bool object::is_final() const {
    return is_final_;
}

void object::is_final(const bool v) {
    is_final_ = v;
}

const std::list<dogen::yarn::name>& object::root_parents() const {
    return root_parents_;
}

std::list<dogen::yarn::name>& object::root_parents() {
    return root_parents_;
}

void object::root_parents(const std::list<dogen::yarn::name>& v) {
    root_parents_ = v;
}

void object::root_parents(const std::list<dogen::yarn::name>&& v) {
    root_parents_ = std::move(v);
}

const std::list<dogen::yarn::name>& object::parents() const {
    return parents_;
}

std::list<dogen::yarn::name>& object::parents() {
    return parents_;
}

void object::parents(const std::list<dogen::yarn::name>& v) {
    parents_ = v;
}

void object::parents(const std::list<dogen::yarn::name>&& v) {
    parents_ = std::move(v);
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

const std::list<dogen::yarn::name>& object::regular_associations() const {
    return regular_associations_;
}

std::list<dogen::yarn::name>& object::regular_associations() {
    return regular_associations_;
}

void object::regular_associations(const std::list<dogen::yarn::name>& v) {
    regular_associations_ = v;
}

void object::regular_associations(const std::list<dogen::yarn::name>&& v) {
    regular_associations_ = std::move(v);
}

const std::list<dogen::yarn::name>& object::weak_associations() const {
    return weak_associations_;
}

std::list<dogen::yarn::name>& object::weak_associations() {
    return weak_associations_;
}

void object::weak_associations(const std::list<dogen::yarn::name>& v) {
    weak_associations_ = v;
}

void object::weak_associations(const std::list<dogen::yarn::name>&& v) {
    weak_associations_ = std::move(v);
}

bool object::is_visitable() const {
    return is_visitable_;
}

void object::is_visitable(const bool v) {
    is_visitable_ = v;
}

bool object::is_root_parent_visitable() const {
    return is_root_parent_visitable_;
}

void object::is_root_parent_visitable(const bool v) {
    is_root_parent_visitable_ = v;
}

const std::list<dogen::yarn::name>& object::visitable_by() const {
    return visitable_by_;
}

std::list<dogen::yarn::name>& object::visitable_by() {
    return visitable_by_;
}

void object::visitable_by(const std::list<dogen::yarn::name>& v) {
    visitable_by_ = v;
}

void object::visitable_by(const std::list<dogen::yarn::name>&& v) {
    visitable_by_ = std::move(v);
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

const std::list<dogen::yarn::name>& object::hash_container_keys() const {
    return hash_container_keys_;
}

std::list<dogen::yarn::name>& object::hash_container_keys() {
    return hash_container_keys_;
}

void object::hash_container_keys(const std::list<dogen::yarn::name>& v) {
    hash_container_keys_ = v;
}

void object::hash_container_keys(const std::list<dogen::yarn::name>&& v) {
    hash_container_keys_ = std::move(v);
}

} }
