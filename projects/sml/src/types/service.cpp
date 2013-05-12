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
#include "dogen/sml/types/service.hpp"

namespace dogen {
namespace sml {

service::service()
    : generation_type_(static_cast<dogen::sml::generation_types>(0)),
      is_parent_(static_cast<bool>(0)),
      service_type_(static_cast<dogen::sml::service_types>(0)),
      number_of_type_arguments_(static_cast<unsigned int>(0)),
      is_visitable_(static_cast<bool>(0)) { }

service::service(service&& rhs)
    : name_(std::move(rhs.name_)),
      properties_(std::move(rhs.properties_)),
      parent_name_(std::move(rhs.parent_name_)),
      original_parent_name_(std::move(rhs.original_parent_name_)),
      leaves_(std::move(rhs.leaves_)),
      generation_type_(std::move(rhs.generation_type_)),
      is_parent_(std::move(rhs.is_parent_)),
      service_type_(std::move(rhs.service_type_)),
      documentation_(std::move(rhs.documentation_)),
      number_of_type_arguments_(std::move(rhs.number_of_type_arguments_)),
      implementation_specific_parameters_(std::move(rhs.implementation_specific_parameters_)),
      is_visitable_(std::move(rhs.is_visitable_)) { }

service::service(
    const dogen::sml::qname& name,
    const std::vector<dogen::sml::property>& properties,
    const boost::optional<dogen::sml::qname>& parent_name,
    const boost::optional<dogen::sml::qname>& original_parent_name,
    const std::list<dogen::sml::qname>& leaves,
    const dogen::sml::generation_types& generation_type,
    const bool is_parent,
    const dogen::sml::service_types& service_type,
    const std::string& documentation,
    const unsigned int number_of_type_arguments,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const bool is_visitable)
    : name_(name),
      properties_(properties),
      parent_name_(parent_name),
      original_parent_name_(original_parent_name),
      leaves_(leaves),
      generation_type_(generation_type),
      is_parent_(is_parent),
      service_type_(service_type),
      documentation_(documentation),
      number_of_type_arguments_(number_of_type_arguments),
      implementation_specific_parameters_(implementation_specific_parameters),
      is_visitable_(is_visitable) { }

void service::swap(service& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(properties_, other.properties_);
    swap(parent_name_, other.parent_name_);
    swap(original_parent_name_, other.original_parent_name_);
    swap(leaves_, other.leaves_);
    swap(generation_type_, other.generation_type_);
    swap(is_parent_, other.is_parent_);
    swap(service_type_, other.service_type_);
    swap(documentation_, other.documentation_);
    swap(number_of_type_arguments_, other.number_of_type_arguments_);
    swap(implementation_specific_parameters_, other.implementation_specific_parameters_);
    swap(is_visitable_, other.is_visitable_);
}

bool service::operator==(const service& rhs) const {
    return name_ == rhs.name_ &&
        properties_ == rhs.properties_ &&
        parent_name_ == rhs.parent_name_ &&
        original_parent_name_ == rhs.original_parent_name_ &&
        leaves_ == rhs.leaves_ &&
        generation_type_ == rhs.generation_type_ &&
        is_parent_ == rhs.is_parent_ &&
        service_type_ == rhs.service_type_ &&
        documentation_ == rhs.documentation_ &&
        number_of_type_arguments_ == rhs.number_of_type_arguments_ &&
        implementation_specific_parameters_ == rhs.implementation_specific_parameters_ &&
        is_visitable_ == rhs.is_visitable_;
}

service& service::operator=(service other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::sml::qname& service::name() const {
    return name_;
}

dogen::sml::qname& service::name() {
    return name_;
}

void service::name(const dogen::sml::qname& v) {
    name_ = v;
}

void service::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

const std::vector<dogen::sml::property>& service::properties() const {
    return properties_;
}

std::vector<dogen::sml::property>& service::properties() {
    return properties_;
}

void service::properties(const std::vector<dogen::sml::property>& v) {
    properties_ = v;
}

void service::properties(const std::vector<dogen::sml::property>&& v) {
    properties_ = std::move(v);
}

const boost::optional<dogen::sml::qname>& service::parent_name() const {
    return parent_name_;
}

boost::optional<dogen::sml::qname>& service::parent_name() {
    return parent_name_;
}

void service::parent_name(const boost::optional<dogen::sml::qname>& v) {
    parent_name_ = v;
}

void service::parent_name(const boost::optional<dogen::sml::qname>&& v) {
    parent_name_ = std::move(v);
}

const boost::optional<dogen::sml::qname>& service::original_parent_name() const {
    return original_parent_name_;
}

boost::optional<dogen::sml::qname>& service::original_parent_name() {
    return original_parent_name_;
}

void service::original_parent_name(const boost::optional<dogen::sml::qname>& v) {
    original_parent_name_ = v;
}

void service::original_parent_name(const boost::optional<dogen::sml::qname>&& v) {
    original_parent_name_ = std::move(v);
}

const std::list<dogen::sml::qname>& service::leaves() const {
    return leaves_;
}

std::list<dogen::sml::qname>& service::leaves() {
    return leaves_;
}

void service::leaves(const std::list<dogen::sml::qname>& v) {
    leaves_ = v;
}

void service::leaves(const std::list<dogen::sml::qname>&& v) {
    leaves_ = std::move(v);
}

dogen::sml::generation_types service::generation_type() const {
    return generation_type_;
}

void service::generation_type(const dogen::sml::generation_types& v) {
    generation_type_ = v;
}

bool service::is_parent() const {
    return is_parent_;
}

void service::is_parent(const bool v) {
    is_parent_ = v;
}

dogen::sml::service_types service::service_type() const {
    return service_type_;
}

void service::service_type(const dogen::sml::service_types& v) {
    service_type_ = v;
}

const std::string& service::documentation() const {
    return documentation_;
}

std::string& service::documentation() {
    return documentation_;
}

void service::documentation(const std::string& v) {
    documentation_ = v;
}

void service::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

unsigned int service::number_of_type_arguments() const {
    return number_of_type_arguments_;
}

void service::number_of_type_arguments(const unsigned int v) {
    number_of_type_arguments_ = v;
}

const std::vector<std::pair<std::string, std::string> >& service::implementation_specific_parameters() const {
    return implementation_specific_parameters_;
}

std::vector<std::pair<std::string, std::string> >& service::implementation_specific_parameters() {
    return implementation_specific_parameters_;
}

void service::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v) {
    implementation_specific_parameters_ = v;
}

void service::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v) {
    implementation_specific_parameters_ = std::move(v);
}

bool service::is_visitable() const {
    return is_visitable_;
}

void service::is_visitable(const bool v) {
    is_visitable_ = v;
}

} }