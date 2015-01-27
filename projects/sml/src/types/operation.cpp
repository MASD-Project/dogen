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
      extensions_(std::move(rhs.extensions_)),
      name_(std::move(rhs.name_)),
      parameters_(std::move(rhs.parameters_)),
      type_(std::move(rhs.type_)) { }

operation::operation(
    const std::string& documentation,
    const dogen::dynamic::object& extensions,
    const std::string& name,
    const std::list<dogen::sml::parameter>& parameters,
    const boost::optional<dogen::sml::nested_qname>& type)
    : documentation_(documentation),
      extensions_(extensions),
      name_(name),
      parameters_(parameters),
      type_(type) { }

void operation::swap(operation& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(extensions_, other.extensions_);
    swap(name_, other.name_);
    swap(parameters_, other.parameters_);
    swap(type_, other.type_);
}

bool operation::operator==(const operation& rhs) const {
    return documentation_ == rhs.documentation_ &&
        extensions_ == rhs.extensions_ &&
        name_ == rhs.name_ &&
        parameters_ == rhs.parameters_ &&
        type_ == rhs.type_;
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

const dogen::dynamic::object& operation::extensions() const {
    return extensions_;
}

dogen::dynamic::object& operation::extensions() {
    return extensions_;
}

void operation::extensions(const dogen::dynamic::object& v) {
    extensions_ = v;
}

void operation::extensions(const dogen::dynamic::object&& v) {
    extensions_ = std::move(v);
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

const std::list<dogen::sml::parameter>& operation::parameters() const {
    return parameters_;
}

std::list<dogen::sml::parameter>& operation::parameters() {
    return parameters_;
}

void operation::parameters(const std::list<dogen::sml::parameter>& v) {
    parameters_ = v;
}

void operation::parameters(const std::list<dogen::sml::parameter>&& v) {
    parameters_ = std::move(v);
}

const boost::optional<dogen::sml::nested_qname>& operation::type() const {
    return type_;
}

boost::optional<dogen::sml::nested_qname>& operation::type() {
    return type_;
}

void operation::type(const boost::optional<dogen::sml::nested_qname>& v) {
    type_ = v;
}

void operation::type(const boost::optional<dogen::sml::nested_qname>&& v) {
    type_ = std::move(v);
}

} }