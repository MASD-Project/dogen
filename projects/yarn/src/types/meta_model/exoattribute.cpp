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
#include "dogen/yarn/types/meta_model/exoattribute.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

exoattribute::exoattribute(
    const std::string& documentation,
    const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes,
    const std::vector<std::string>& unknown_stereotypes,
    const std::list<std::pair<std::string, std::string> >& tagged_values,
    const std::string& name,
    const std::string& type)
    : documentation_(documentation),
      well_known_stereotypes_(well_known_stereotypes),
      unknown_stereotypes_(unknown_stereotypes),
      tagged_values_(tagged_values),
      name_(name),
      type_(type) { }

void exoattribute::swap(exoattribute& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(well_known_stereotypes_, other.well_known_stereotypes_);
    swap(unknown_stereotypes_, other.unknown_stereotypes_);
    swap(tagged_values_, other.tagged_values_);
    swap(name_, other.name_);
    swap(type_, other.type_);
}

bool exoattribute::operator==(const exoattribute& rhs) const {
    return documentation_ == rhs.documentation_ &&
        well_known_stereotypes_ == rhs.well_known_stereotypes_ &&
        unknown_stereotypes_ == rhs.unknown_stereotypes_ &&
        tagged_values_ == rhs.tagged_values_ &&
        name_ == rhs.name_ &&
        type_ == rhs.type_;
}

exoattribute& exoattribute::operator=(exoattribute other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& exoattribute::documentation() const {
    return documentation_;
}

std::string& exoattribute::documentation() {
    return documentation_;
}

void exoattribute::documentation(const std::string& v) {
    documentation_ = v;
}

void exoattribute::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& exoattribute::well_known_stereotypes() const {
    return well_known_stereotypes_;
}

std::vector<dogen::yarn::meta_model::well_known_stereotypes>& exoattribute::well_known_stereotypes() {
    return well_known_stereotypes_;
}

void exoattribute::well_known_stereotypes(const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& v) {
    well_known_stereotypes_ = v;
}

void exoattribute::well_known_stereotypes(const std::vector<dogen::yarn::meta_model::well_known_stereotypes>&& v) {
    well_known_stereotypes_ = std::move(v);
}

const std::vector<std::string>& exoattribute::unknown_stereotypes() const {
    return unknown_stereotypes_;
}

std::vector<std::string>& exoattribute::unknown_stereotypes() {
    return unknown_stereotypes_;
}

void exoattribute::unknown_stereotypes(const std::vector<std::string>& v) {
    unknown_stereotypes_ = v;
}

void exoattribute::unknown_stereotypes(const std::vector<std::string>&& v) {
    unknown_stereotypes_ = std::move(v);
}

const std::list<std::pair<std::string, std::string> >& exoattribute::tagged_values() const {
    return tagged_values_;
}

std::list<std::pair<std::string, std::string> >& exoattribute::tagged_values() {
    return tagged_values_;
}

void exoattribute::tagged_values(const std::list<std::pair<std::string, std::string> >& v) {
    tagged_values_ = v;
}

void exoattribute::tagged_values(const std::list<std::pair<std::string, std::string> >&& v) {
    tagged_values_ = std::move(v);
}

const std::string& exoattribute::name() const {
    return name_;
}

std::string& exoattribute::name() {
    return name_;
}

void exoattribute::name(const std::string& v) {
    name_ = v;
}

void exoattribute::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& exoattribute::type() const {
    return type_;
}

std::string& exoattribute::type() {
    return type_;
}

void exoattribute::type(const std::string& v) {
    type_ = v;
}

void exoattribute::type(const std::string&& v) {
    type_ = std::move(v);
}

} } }
