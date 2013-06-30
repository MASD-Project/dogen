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
#include "dogen/sml/types/operation.hpp"

namespace dogen {
namespace sml {

operation::operation(operation&& rhs)
    : documentation_(std::move(rhs.documentation_)),
      implementation_specific_parameters_(std::move(rhs.implementation_specific_parameters_)),
      name_(std::move(rhs.name_)),
      arguments_(std::move(rhs.arguments_)),
      return_type_(std::move(rhs.return_type_)) { }

operation::operation(
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
    const std::string& name,
    const std::list<dogen::sml::nested_qname>& arguments,
    const boost::optional<dogen::sml::nested_qname>& return_type)
    : documentation_(documentation),
      implementation_specific_parameters_(implementation_specific_parameters),
      name_(name),
      arguments_(arguments),
      return_type_(return_type) { }

void operation::swap(operation& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(implementation_specific_parameters_, other.implementation_specific_parameters_);
    swap(name_, other.name_);
    swap(arguments_, other.arguments_);
    swap(return_type_, other.return_type_);
}

bool operation::operator==(const operation& rhs) const {
    return documentation_ == rhs.documentation_ &&
        implementation_specific_parameters_ == rhs.implementation_specific_parameters_ &&
        name_ == rhs.name_ &&
        arguments_ == rhs.arguments_ &&
        return_type_ == rhs.return_type_;
}

operation& operation::operator=(operation other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& operation::documentation() const {
    return documentation_;
}

std::string& operation::documentation() {
    return documentation_;
}

void operation::documentation(const std::string& v) {
    documentation_ = v;
}

void operation::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::vector<std::pair<std::string, std::string> >& operation::implementation_specific_parameters() const {
    return implementation_specific_parameters_;
}

std::vector<std::pair<std::string, std::string> >& operation::implementation_specific_parameters() {
    return implementation_specific_parameters_;
}

void operation::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v) {
    implementation_specific_parameters_ = v;
}

void operation::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v) {
    implementation_specific_parameters_ = std::move(v);
}

const std::string& operation::name() const {
    return name_;
}

std::string& operation::name() {
    return name_;
}

void operation::name(const std::string& v) {
    name_ = v;
}

void operation::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::list<dogen::sml::nested_qname>& operation::arguments() const {
    return arguments_;
}

std::list<dogen::sml::nested_qname>& operation::arguments() {
    return arguments_;
}

void operation::arguments(const std::list<dogen::sml::nested_qname>& v) {
    arguments_ = v;
}

void operation::arguments(const std::list<dogen::sml::nested_qname>&& v) {
    arguments_ = std::move(v);
}

const boost::optional<dogen::sml::nested_qname>& operation::return_type() const {
    return return_type_;
}

boost::optional<dogen::sml::nested_qname>& operation::return_type() {
    return return_type_;
}

void operation::return_type(const boost::optional<dogen::sml::nested_qname>& v) {
    return_type_ = v;
}

void operation::return_type(const boost::optional<dogen::sml::nested_qname>&& v) {
    return_type_ = std::move(v);
}

} }