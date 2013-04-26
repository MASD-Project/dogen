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
#include "dogen/cpp/types/view_models/class_view_model.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

class_view_model::class_view_model()
    : has_primitive_properties_(static_cast<bool>(0)),
      requires_stream_manipulators_(static_cast<bool>(0)),
      requires_manual_move_constructor_(static_cast<bool>(0)),
      requires_manual_default_constructor_(static_cast<bool>(0)),
      is_parent_(static_cast<bool>(0)),
      is_comparable_(static_cast<bool>(0)),
      is_visitable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)) { }

class_view_model::class_view_model(
    const std::list<std::string>& namespaces,
    const std::string& name,
    const std::list<dogen::cpp::view_models::property_view_model>& properties,
    const std::list<dogen::cpp::view_models::property_view_model>& all_properties,
    const bool has_primitive_properties,
    const bool requires_stream_manipulators,
    const bool requires_manual_move_constructor,
    const bool requires_manual_default_constructor,
    const std::list<dogen::cpp::view_models::parent_view_model>& parents,
    const bool is_parent,
    const std::string& documentation,
    const std::string& original_parent_name,
    const std::list<std::string>& leaves,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const bool is_comparable,
    const bool is_visitable,
    const bool is_fluent)
    : namespaces_(namespaces),
      name_(name),
      properties_(properties),
      all_properties_(all_properties),
      has_primitive_properties_(has_primitive_properties),
      requires_stream_manipulators_(requires_stream_manipulators),
      requires_manual_move_constructor_(requires_manual_move_constructor),
      requires_manual_default_constructor_(requires_manual_default_constructor),
      parents_(parents),
      is_parent_(is_parent),
      documentation_(documentation),
      original_parent_name_(original_parent_name),
      leaves_(leaves),
      implementation_specific_parameters_(implementation_specific_parameters),
      is_comparable_(is_comparable),
      is_visitable_(is_visitable),
      is_fluent_(is_fluent) { }

void class_view_model::swap(class_view_model& other) noexcept {
    using std::swap;
    swap(namespaces_, other.namespaces_);
    swap(name_, other.name_);
    swap(properties_, other.properties_);
    swap(all_properties_, other.all_properties_);
    swap(has_primitive_properties_, other.has_primitive_properties_);
    swap(requires_stream_manipulators_, other.requires_stream_manipulators_);
    swap(requires_manual_move_constructor_, other.requires_manual_move_constructor_);
    swap(requires_manual_default_constructor_, other.requires_manual_default_constructor_);
    swap(parents_, other.parents_);
    swap(is_parent_, other.is_parent_);
    swap(documentation_, other.documentation_);
    swap(original_parent_name_, other.original_parent_name_);
    swap(leaves_, other.leaves_);
    swap(implementation_specific_parameters_, other.implementation_specific_parameters_);
    swap(is_comparable_, other.is_comparable_);
    swap(is_visitable_, other.is_visitable_);
    swap(is_fluent_, other.is_fluent_);
}

bool class_view_model::operator==(const class_view_model& rhs) const {
    return namespaces_ == rhs.namespaces_ &&
        name_ == rhs.name_ &&
        properties_ == rhs.properties_ &&
        all_properties_ == rhs.all_properties_ &&
        has_primitive_properties_ == rhs.has_primitive_properties_ &&
        requires_stream_manipulators_ == rhs.requires_stream_manipulators_ &&
        requires_manual_move_constructor_ == rhs.requires_manual_move_constructor_ &&
        requires_manual_default_constructor_ == rhs.requires_manual_default_constructor_ &&
        parents_ == rhs.parents_ &&
        is_parent_ == rhs.is_parent_ &&
        documentation_ == rhs.documentation_ &&
        original_parent_name_ == rhs.original_parent_name_ &&
        leaves_ == rhs.leaves_ &&
        implementation_specific_parameters_ == rhs.implementation_specific_parameters_ &&
        is_comparable_ == rhs.is_comparable_ &&
        is_visitable_ == rhs.is_visitable_ &&
        is_fluent_ == rhs.is_fluent_;
}

class_view_model& class_view_model::operator=(class_view_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& class_view_model::namespaces() const {
    return namespaces_;
}

std::list<std::string>& class_view_model::namespaces() {
    return namespaces_;
}

void class_view_model::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void class_view_model::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

const std::string& class_view_model::name() const {
    return name_;
}

std::string& class_view_model::name() {
    return name_;
}

void class_view_model::name(const std::string& v) {
    name_ = v;
}

void class_view_model::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<dogen::cpp::view_models::property_view_model>& class_view_model::properties() const {
    return properties_;
}

std::list<dogen::cpp::view_models::property_view_model>& class_view_model::properties() {
    return properties_;
}

void class_view_model::properties(const std::list<dogen::cpp::view_models::property_view_model>& v) {
    properties_ = v;
}

void class_view_model::properties(const std::list<dogen::cpp::view_models::property_view_model>&& v) {
    properties_ = std::move(v);
}

const std::list<dogen::cpp::view_models::property_view_model>& class_view_model::all_properties() const {
    return all_properties_;
}

std::list<dogen::cpp::view_models::property_view_model>& class_view_model::all_properties() {
    return all_properties_;
}

void class_view_model::all_properties(const std::list<dogen::cpp::view_models::property_view_model>& v) {
    all_properties_ = v;
}

void class_view_model::all_properties(const std::list<dogen::cpp::view_models::property_view_model>&& v) {
    all_properties_ = std::move(v);
}

bool class_view_model::has_primitive_properties() const {
    return has_primitive_properties_;
}

void class_view_model::has_primitive_properties(const bool v) {
    has_primitive_properties_ = v;
}

bool class_view_model::requires_stream_manipulators() const {
    return requires_stream_manipulators_;
}

void class_view_model::requires_stream_manipulators(const bool v) {
    requires_stream_manipulators_ = v;
}

bool class_view_model::requires_manual_move_constructor() const {
    return requires_manual_move_constructor_;
}

void class_view_model::requires_manual_move_constructor(const bool v) {
    requires_manual_move_constructor_ = v;
}

bool class_view_model::requires_manual_default_constructor() const {
    return requires_manual_default_constructor_;
}

void class_view_model::requires_manual_default_constructor(const bool v) {
    requires_manual_default_constructor_ = v;
}

const std::list<dogen::cpp::view_models::parent_view_model>& class_view_model::parents() const {
    return parents_;
}

std::list<dogen::cpp::view_models::parent_view_model>& class_view_model::parents() {
    return parents_;
}

void class_view_model::parents(const std::list<dogen::cpp::view_models::parent_view_model>& v) {
    parents_ = v;
}

void class_view_model::parents(const std::list<dogen::cpp::view_models::parent_view_model>&& v) {
    parents_ = std::move(v);
}

bool class_view_model::is_parent() const {
    return is_parent_;
}

void class_view_model::is_parent(const bool v) {
    is_parent_ = v;
}

const std::string& class_view_model::documentation() const {
    return documentation_;
}

std::string& class_view_model::documentation() {
    return documentation_;
}

void class_view_model::documentation(const std::string& v) {
    documentation_ = v;
}

void class_view_model::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::string& class_view_model::original_parent_name() const {
    return original_parent_name_;
}

std::string& class_view_model::original_parent_name() {
    return original_parent_name_;
}

void class_view_model::original_parent_name(const std::string& v) {
    original_parent_name_ = v;
}

void class_view_model::original_parent_name(const std::string&& v) {
    original_parent_name_ = std::move(v);
}

const std::list<std::string>& class_view_model::leaves() const {
    return leaves_;
}

std::list<std::string>& class_view_model::leaves() {
    return leaves_;
}

void class_view_model::leaves(const std::list<std::string>& v) {
    leaves_ = v;
}

void class_view_model::leaves(const std::list<std::string>&& v) {
    leaves_ = std::move(v);
}

const std::vector<std::pair<std::string, std::string> >& class_view_model::implementation_specific_parameters() const {
    return implementation_specific_parameters_;
}

std::vector<std::pair<std::string, std::string> >& class_view_model::implementation_specific_parameters() {
    return implementation_specific_parameters_;
}

void class_view_model::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v) {
    implementation_specific_parameters_ = v;
}

void class_view_model::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v) {
    implementation_specific_parameters_ = std::move(v);
}

bool class_view_model::is_comparable() const {
    return is_comparable_;
}

void class_view_model::is_comparable(const bool v) {
    is_comparable_ = v;
}

bool class_view_model::is_visitable() const {
    return is_visitable_;
}

void class_view_model::is_visitable(const bool v) {
    is_visitable_ = v;
}

bool class_view_model::is_fluent() const {
    return is_fluent_;
}

void class_view_model::is_fluent(const bool v) {
    is_fluent_ = v;
}

} } }