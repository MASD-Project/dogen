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
#include "dogen/sml/types/package.hpp"

namespace dogen {
namespace sml {

package::package(
    const dogen::sml::qname& name,
    const std::string& documentation,
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters)
    : name_(name),
      documentation_(documentation),
      implementation_specific_parameters_(implementation_specific_parameters) { }

void package::swap(package& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(documentation_, other.documentation_);
    swap(implementation_specific_parameters_, other.implementation_specific_parameters_);
}

bool package::operator==(const package& rhs) const {
    return name_ == rhs.name_ &&
        documentation_ == rhs.documentation_ &&
        implementation_specific_parameters_ == rhs.implementation_specific_parameters_;
}

package& package::operator=(package other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::sml::qname& package::name() const {
    return name_;
}

dogen::sml::qname& package::name() {
    return name_;
}

void package::name(const dogen::sml::qname& v) {
    name_ = v;
}

void package::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

const std::string& package::documentation() const {
    return documentation_;
}

std::string& package::documentation() {
    return documentation_;
}

void package::documentation(const std::string& v) {
    documentation_ = v;
}

void package::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::vector<std::pair<std::string, std::string> >& package::implementation_specific_parameters() const {
    return implementation_specific_parameters_;
}

std::vector<std::pair<std::string, std::string> >& package::implementation_specific_parameters() {
    return implementation_specific_parameters_;
}

void package::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v) {
    implementation_specific_parameters_ = v;
}

void package::implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v) {
    implementation_specific_parameters_ = std::move(v);
}

} }