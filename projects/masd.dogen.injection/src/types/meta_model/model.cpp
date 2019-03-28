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
    const std::list<std::pair<std::string, std::string> >& tagged_values,
    const std::list<std::string>& stereotypes,
    const std::string& documentation,
    const std::string& name,
    const masd::dogen::annotations::annotation& annotation,
    const std::list<masd::dogen::injection::meta_model::element>& elements,
    const std::string& input_technical_space,
    const std::list<std::string>& references)
    : tagged_values_(tagged_values),
      stereotypes_(stereotypes),
      documentation_(documentation),
      name_(name),
      annotation_(annotation),
      elements_(elements),
      input_technical_space_(input_technical_space),
      references_(references) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(tagged_values_, other.tagged_values_);
    swap(stereotypes_, other.stereotypes_);
    swap(documentation_, other.documentation_);
    swap(name_, other.name_);
    swap(annotation_, other.annotation_);
    swap(elements_, other.elements_);
    swap(input_technical_space_, other.input_technical_space_);
    swap(references_, other.references_);
}

bool model::operator==(const model& rhs) const {
    return tagged_values_ == rhs.tagged_values_ &&
        stereotypes_ == rhs.stereotypes_ &&
        documentation_ == rhs.documentation_ &&
        name_ == rhs.name_ &&
        annotation_ == rhs.annotation_ &&
        elements_ == rhs.elements_ &&
        input_technical_space_ == rhs.input_technical_space_ &&
        references_ == rhs.references_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
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

const masd::dogen::annotations::annotation& model::annotation() const {
    return annotation_;
}

masd::dogen::annotations::annotation& model::annotation() {
    return annotation_;
}

void model::annotation(const masd::dogen::annotations::annotation& v) {
    annotation_ = v;
}

void model::annotation(const masd::dogen::annotations::annotation&& v) {
    annotation_ = std::move(v);
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

const std::string& model::input_technical_space() const {
    return input_technical_space_;
}

std::string& model::input_technical_space() {
    return input_technical_space_;
}

void model::input_technical_space(const std::string& v) {
    input_technical_space_ = v;
}

void model::input_technical_space(const std::string&& v) {
    input_technical_space_ = std::move(v);
}

const std::list<std::string>& model::references() const {
    return references_;
}

std::list<std::string>& model::references() {
    return references_;
}

void model::references(const std::list<std::string>& v) {
    references_ = v;
}

void model::references(const std::list<std::string>&& v) {
    references_ = std::move(v);
}

}
