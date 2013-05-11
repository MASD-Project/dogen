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
#include "dogen/sml/types/pod.hpp"

namespace dogen {
namespace sml {

pod::pod()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)),
      is_parent_(static_cast<bool>(0)),
      category_type_(static_cast<dogen::sml::category_types>(0)),
      pod_type_(static_cast<dogen::sml::pod_types>(0)),
      number_of_type_arguments_(static_cast<unsigned int>(0)),
      is_visitable_(static_cast<bool>(0)),
      is_immutable_(static_cast<bool>(0)),
      is_versioned_(static_cast<bool>(0)),
      is_keyed_(static_cast<bool>(0)),
      is_comparable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)),
      is_aggregate_root_(static_cast<bool>(0)) { }

pod::pod(pod&& rhs)
    : name_(std::move(rhs.name_)),
      properties_(std::move(rhs.properties_)),
      parent_name_(std::move(rhs.parent_name_)),
      original_parent_name_(std::move(rhs.original_parent_name_)),
      leaves_(std::move(rhs.leaves_)),
      generation_type_(std::move(rhs.generation_type_)),
      is_parent_(std::move(rhs.is_parent_)),
      category_type_(std::move(rhs.category_type_)),
      pod_type_(std::move(rhs.pod_type_)),
      documentation_(std::move(rhs.documentation_)),
      number_of_type_arguments_(std::move(rhs.number_of_type_arguments_)),
      implementation_specific_parameters_(std::move(rhs.implementation_specific_parameters_)),
      is_visitable_(std::move(rhs.is_visitable_)),
      is_immutable_(std::move(rhs.is_immutable_)),
      is_versioned_(std::move(rhs.is_versioned_)),
      is_keyed_(std::move(rhs.is_keyed_)),
      is_comparable_(std::move(rhs.is_comparable_)),
      is_fluent_(std::move(rhs.is_fluent_)),
      is_aggregate_root_(std::move(rhs.is_aggregate_root_)),
      versioned_key_(std::move(rhs.versioned_key_)),
      unversioned_key_(std::move(rhs.unversioned_key_)) { }

pod::pod(
    const dogen::sml::qname& name,
    const std::vector<dogen::sml::property>& properties,
    const boost::optional<dogen::sml::qname>& parent_name,
    const boost::optional<dogen::sml::qname>& original_parent_name,
    const std::list<dogen::sml::qname>& leaves,
    const dogen::sml::generation_types& generation_type,
    const bool is_parent,
    const dogen::sml::category_types& category_type,
    const dogen::sml::pod_types& pod_type,
    const std::string& documentation,
    const unsigned int number_of_type_arguments,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const bool is_visitable,
    const bool is_immutable,
    const bool is_versioned,
    const bool is_keyed,
    const bool is_comparable,
    const bool is_fluent,
    const bool is_aggregate_root,
    const boost::optional<dogen::sml::qname>& versioned_key,
    const boost::optional<dogen::sml::qname>& unversioned_key)
    : name_(name),
      properties_(properties),
      parent_name_(parent_name),
      original_parent_name_(original_parent_name),
      leaves_(leaves),
      generation_type_(generation_type),
      is_parent_(is_parent),
      category_type_(category_type),
      pod_type_(pod_type),
      documentation_(documentation),
      number_of_type_arguments_(number_of_type_arguments),
      implementation_specific_parameters_(implementation_specific_parameters),
      is_visitable_(is_visitable),
      is_immutable_(is_immutable),
      is_versioned_(is_versioned),
      is_keyed_(is_keyed),
      is_comparable_(is_comparable),
      is_fluent_(is_fluent),
      is_aggregate_root_(is_aggregate_root),
      versioned_key_(versioned_key),
      unversioned_key_(unversioned_key) { }

void pod::swap(pod& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(properties_, other.properties_);
    swap(parent_name_, other.parent_name_);
    swap(original_parent_name_, other.original_parent_name_);
    swap(leaves_, other.leaves_);
    swap(generation_type_, other.generation_type_);
    swap(is_parent_, other.is_parent_);
    swap(category_type_, other.category_type_);
    swap(pod_type_, other.pod_type_);
    swap(documentation_, other.documentation_);
    swap(number_of_type_arguments_, other.number_of_type_arguments_);
    swap(implementation_specific_parameters_, other.implementation_specific_parameters_);
    swap(is_visitable_, other.is_visitable_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_versioned_, other.is_versioned_);
    swap(is_keyed_, other.is_keyed_);
    swap(is_comparable_, other.is_comparable_);
    swap(is_fluent_, other.is_fluent_);
    swap(is_aggregate_root_, other.is_aggregate_root_);
    swap(versioned_key_, other.versioned_key_);
    swap(unversioned_key_, other.unversioned_key_);
}

bool pod::operator==(const pod& rhs) const {
    return name_ == rhs.name_ &&
        properties_ == rhs.properties_ &&
        parent_name_ == rhs.parent_name_ &&
        original_parent_name_ == rhs.original_parent_name_ &&
        leaves_ == rhs.leaves_ &&
        generation_type_ == rhs.generation_type_ &&
        is_parent_ == rhs.is_parent_ &&
        category_type_ == rhs.category_type_ &&
        pod_type_ == rhs.pod_type_ &&
        documentation_ == rhs.documentation_ &&
        number_of_type_arguments_ == rhs.number_of_type_arguments_ &&
        implementation_specific_parameters_ == rhs.implementation_specific_parameters_ &&
        is_visitable_ == rhs.is_visitable_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_versioned_ == rhs.is_versioned_ &&
        is_keyed_ == rhs.is_keyed_ &&
        is_comparable_ == rhs.is_comparable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        is_aggregate_root_ == rhs.is_aggregate_root_ &&
        versioned_key_ == rhs.versioned_key_ &&
        unversioned_key_ == rhs.unversioned_key_;
}

pod& pod::operator=(pod other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::sml::qname& pod::name() const {
    return name_;
}

dogen::sml::qname& pod::name() {
    return name_;
}

void pod::name(const dogen::sml::qname& v) {
    name_ = v;
}

void pod::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

const std::vector<dogen::sml::property>& pod::properties() const {
    return properties_;
}

std::vector<dogen::sml::property>& pod::properties() {
    return properties_;
}

void pod::properties(const std::vector<dogen::sml::property>& v) {
    properties_ = v;
}

void pod::properties(const std::vector<dogen::sml::property>&& v) {
    properties_ = std::move(v);
}

const boost::optional<dogen::sml::qname>& pod::parent_name() const {
    return parent_name_;
}

boost::optional<dogen::sml::qname>& pod::parent_name() {
    return parent_name_;
}

void pod::parent_name(const boost::optional<dogen::sml::qname>& v) {
    parent_name_ = v;
}

void pod::parent_name(const boost::optional<dogen::sml::qname>&& v) {
    parent_name_ = std::move(v);
}

const boost::optional<dogen::sml::qname>& pod::original_parent_name() const {
    return original_parent_name_;
}

boost::optional<dogen::sml::qname>& pod::original_parent_name() {
    return original_parent_name_;
}

void pod::original_parent_name(const boost::optional<dogen::sml::qname>& v) {
    original_parent_name_ = v;
}

void pod::original_parent_name(const boost::optional<dogen::sml::qname>&& v) {
    original_parent_name_ = std::move(v);
}

const std::list<dogen::sml::qname>& pod::leaves() const {
    return leaves_;
}

std::list<dogen::sml::qname>& pod::leaves() {
    return leaves_;
}

void pod::leaves(const std::list<dogen::sml::qname>& v) {
    leaves_ = v;
}

void pod::leaves(const std::list<dogen::sml::qname>&& v) {
    leaves_ = std::move(v);
}

dogen::sml::generation_types pod::generation_type() const {
    return generation_type_;
}

void pod::generation_type(const dogen::sml::generation_types& v) {
    generation_type_ = v;
}

bool pod::is_parent() const {
    return is_parent_;
}

void pod::is_parent(const bool v) {
    is_parent_ = v;
}

dogen::sml::category_types pod::category_type() const {
    return category_type_;
}

void pod::category_type(const dogen::sml::category_types& v) {
    category_type_ = v;
}

dogen::sml::pod_types pod::pod_type() const {
    return pod_type_;
}

void pod::pod_type(const dogen::sml::pod_types& v) {
    pod_type_ = v;
}

const std::string& pod::documentation() const {
    return documentation_;
}

std::string& pod::documentation() {
    return documentation_;
}

void pod::documentation(const std::string& v) {
    documentation_ = v;
}

void pod::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

unsigned int pod::number_of_type_arguments() const {
    return number_of_type_arguments_;
}

void pod::number_of_type_arguments(const unsigned int v) {
    number_of_type_arguments_ = v;
}

const std::vector<std::pair<std::string, std::string> >& pod::implementation_specific_parameters() const {
    return implementation_specific_parameters_;
}

std::vector<std::pair<std::string, std::string> >& pod::implementation_specific_parameters() {
    return implementation_specific_parameters_;
}

void pod::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v) {
    implementation_specific_parameters_ = v;
}

void pod::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v) {
    implementation_specific_parameters_ = std::move(v);
}

bool pod::is_visitable() const {
    return is_visitable_;
}

void pod::is_visitable(const bool v) {
    is_visitable_ = v;
}

bool pod::is_immutable() const {
    return is_immutable_;
}

void pod::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool pod::is_versioned() const {
    return is_versioned_;
}

void pod::is_versioned(const bool v) {
    is_versioned_ = v;
}

bool pod::is_keyed() const {
    return is_keyed_;
}

void pod::is_keyed(const bool v) {
    is_keyed_ = v;
}

bool pod::is_comparable() const {
    return is_comparable_;
}

void pod::is_comparable(const bool v) {
    is_comparable_ = v;
}

bool pod::is_fluent() const {
    return is_fluent_;
}

void pod::is_fluent(const bool v) {
    is_fluent_ = v;
}

bool pod::is_aggregate_root() const {
    return is_aggregate_root_;
}

void pod::is_aggregate_root(const bool v) {
    is_aggregate_root_ = v;
}

const boost::optional<dogen::sml::qname>& pod::versioned_key() const {
    return versioned_key_;
}

boost::optional<dogen::sml::qname>& pod::versioned_key() {
    return versioned_key_;
}

void pod::versioned_key(const boost::optional<dogen::sml::qname>& v) {
    versioned_key_ = v;
}

void pod::versioned_key(const boost::optional<dogen::sml::qname>&& v) {
    versioned_key_ = std::move(v);
}

const boost::optional<dogen::sml::qname>& pod::unversioned_key() const {
    return unversioned_key_;
}

boost::optional<dogen::sml::qname>& pod::unversioned_key() {
    return unversioned_key_;
}

void pod::unversioned_key(const boost::optional<dogen::sml::qname>& v) {
    unversioned_key_ = v;
}

void pod::unversioned_key(const boost::optional<dogen::sml::qname>&& v) {
    unversioned_key_ = std::move(v);
}

} }