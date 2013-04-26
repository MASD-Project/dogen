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
#include "dogen/cpp/types/view_models/property_view_model.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

property_view_model::property_view_model()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)) { }

property_view_model::property_view_model(
    const std::string& name,
    const dogen::cpp::view_models::nested_type_view_model& type,
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const bool is_immutable,
    const bool is_fluent)
    : name_(name),
      type_(type),
      documentation_(documentation),
      implementation_specific_parameters_(implementation_specific_parameters),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent) { }

void property_view_model::swap(property_view_model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(type_, other.type_);
    swap(documentation_, other.documentation_);
    swap(implementation_specific_parameters_, other.implementation_specific_parameters_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
}

bool property_view_model::operator==(const property_view_model& rhs) const {
    return name_ == rhs.name_ &&
        type_ == rhs.type_ &&
        documentation_ == rhs.documentation_ &&
        implementation_specific_parameters_ == rhs.implementation_specific_parameters_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_;
}

property_view_model& property_view_model::operator=(property_view_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& property_view_model::name() const {
    return name_;
}

std::string& property_view_model::name() {
    return name_;
}

void property_view_model::name(const std::string& v) {
    name_ = v;
}

void property_view_model::name(const std::string&& v) {
    name_ = std::move(v);
}

const dogen::cpp::view_models::nested_type_view_model& property_view_model::type() const {
    return type_;
}

dogen::cpp::view_models::nested_type_view_model& property_view_model::type() {
    return type_;
}

void property_view_model::type(const dogen::cpp::view_models::nested_type_view_model& v) {
    type_ = v;
}

void property_view_model::type(const dogen::cpp::view_models::nested_type_view_model&& v) {
    type_ = std::move(v);
}

const std::string& property_view_model::documentation() const {
    return documentation_;
}

std::string& property_view_model::documentation() {
    return documentation_;
}

void property_view_model::documentation(const std::string& v) {
    documentation_ = v;
}

void property_view_model::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::vector<std::pair<std::string, std::string> >& property_view_model::implementation_specific_parameters() const {
    return implementation_specific_parameters_;
}

std::vector<std::pair<std::string, std::string> >& property_view_model::implementation_specific_parameters() {
    return implementation_specific_parameters_;
}

void property_view_model::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v) {
    implementation_specific_parameters_ = v;
}

void property_view_model::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v) {
    implementation_specific_parameters_ = std::move(v);
}

bool property_view_model::is_immutable() const {
    return is_immutable_;
}

void property_view_model::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool property_view_model::is_fluent() const {
    return is_fluent_;
}

void property_view_model::is_fluent(const bool v) {
    is_fluent_ = v;
}

} } }