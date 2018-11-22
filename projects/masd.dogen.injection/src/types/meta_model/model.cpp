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
#include "masd.dogen.injection/types/meta_model/model.hpp"

namespace masd::dogen::injection::meta_model {

model::model(
    const std::string& name,
    const std::string& documentation,
    const std::list<std::pair<std::string, std::string> >& tagged_values,
    const std::list<std::string>& stereotypes,
    const std::list<masd::dogen::injection::meta_model::element>& elements)
    : name_(name),
      documentation_(documentation),
      tagged_values_(tagged_values),
      stereotypes_(stereotypes),
      elements_(elements) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(documentation_, other.documentation_);
    swap(tagged_values_, other.tagged_values_);
    swap(stereotypes_, other.stereotypes_);
    swap(elements_, other.elements_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        documentation_ == rhs.documentation_ &&
        tagged_values_ == rhs.tagged_values_ &&
        stereotypes_ == rhs.stereotypes_ &&
        elements_ == rhs.elements_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& model::name() const {
    return name_;
}

std::string& model::name() {
    return name_;
}

void model::name(const std::string& v) {
    name_ = v;
}

void model::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& model::documentation() const {
    return documentation_;
}

std::string& model::documentation() {
    return documentation_;
}

void model::documentation(const std::string& v) {
    documentation_ = v;
}

void model::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::list<std::pair<std::string, std::string> >& model::tagged_values() const {
    return tagged_values_;
}

std::list<std::pair<std::string, std::string> >& model::tagged_values() {
    return tagged_values_;
}

void model::tagged_values(const std::list<std::pair<std::string, std::string> >& v) {
    tagged_values_ = v;
}

void model::tagged_values(const std::list<std::pair<std::string, std::string> >&& v) {
    tagged_values_ = std::move(v);
}

const std::list<std::string>& model::stereotypes() const {
    return stereotypes_;
}

std::list<std::string>& model::stereotypes() {
    return stereotypes_;
}

void model::stereotypes(const std::list<std::string>& v) {
    stereotypes_ = v;
}

void model::stereotypes(const std::list<std::string>&& v) {
    stereotypes_ = std::move(v);
}

const std::list<masd::dogen::injection::meta_model::element>& model::elements() const {
    return elements_;
}

std::list<masd::dogen::injection::meta_model::element>& model::elements() {
    return elements_;
}

void model::elements(const std::list<masd::dogen::injection::meta_model::element>& v) {
    elements_ = v;
}

void model::elements(const std::list<masd::dogen::injection::meta_model::element>&& v) {
    elements_ = std::move(v);
}

}
