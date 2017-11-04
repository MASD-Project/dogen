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
#include "dogen/yarn/types/meta_model/exoelement.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

exoelement::exoelement(
    const std::string& documentation,
    const std::vector<std::string>& stereotypes,
    const std::list<std::pair<std::string, std::string> >& tagged_values,
    const std::string& name,
    const std::string& contained_by,
    const std::list<dogen::yarn::meta_model::exoattribute>& attributes)
    : documentation_(documentation),
      stereotypes_(stereotypes),
      tagged_values_(tagged_values),
      name_(name),
      contained_by_(contained_by),
      attributes_(attributes) { }

void exoelement::swap(exoelement& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(stereotypes_, other.stereotypes_);
    swap(tagged_values_, other.tagged_values_);
    swap(name_, other.name_);
    swap(contained_by_, other.contained_by_);
    swap(attributes_, other.attributes_);
}

bool exoelement::operator==(const exoelement& rhs) const {
    return documentation_ == rhs.documentation_ &&
        stereotypes_ == rhs.stereotypes_ &&
        tagged_values_ == rhs.tagged_values_ &&
        name_ == rhs.name_ &&
        contained_by_ == rhs.contained_by_ &&
        attributes_ == rhs.attributes_;
}

exoelement& exoelement::operator=(exoelement other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& exoelement::documentation() const {
    return documentation_;
}

std::string& exoelement::documentation() {
    return documentation_;
}

void exoelement::documentation(const std::string& v) {
    documentation_ = v;
}

void exoelement::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::vector<std::string>& exoelement::stereotypes() const {
    return stereotypes_;
}

std::vector<std::string>& exoelement::stereotypes() {
    return stereotypes_;
}

void exoelement::stereotypes(const std::vector<std::string>& v) {
    stereotypes_ = v;
}

void exoelement::stereotypes(const std::vector<std::string>&& v) {
    stereotypes_ = std::move(v);
}

const std::list<std::pair<std::string, std::string> >& exoelement::tagged_values() const {
    return tagged_values_;
}

std::list<std::pair<std::string, std::string> >& exoelement::tagged_values() {
    return tagged_values_;
}

void exoelement::tagged_values(const std::list<std::pair<std::string, std::string> >& v) {
    tagged_values_ = v;
}

void exoelement::tagged_values(const std::list<std::pair<std::string, std::string> >&& v) {
    tagged_values_ = std::move(v);
}

const std::string& exoelement::name() const {
    return name_;
}

std::string& exoelement::name() {
    return name_;
}

void exoelement::name(const std::string& v) {
    name_ = v;
}

void exoelement::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& exoelement::contained_by() const {
    return contained_by_;
}

std::string& exoelement::contained_by() {
    return contained_by_;
}

void exoelement::contained_by(const std::string& v) {
    contained_by_ = v;
}

void exoelement::contained_by(const std::string&& v) {
    contained_by_ = std::move(v);
}

const std::list<dogen::yarn::meta_model::exoattribute>& exoelement::attributes() const {
    return attributes_;
}

std::list<dogen::yarn::meta_model::exoattribute>& exoelement::attributes() {
    return attributes_;
}

void exoelement::attributes(const std::list<dogen::yarn::meta_model::exoattribute>& v) {
    attributes_ = v;
}

void exoelement::attributes(const std::list<dogen::yarn::meta_model::exoattribute>&& v) {
    attributes_ = std::move(v);
}

} } }
