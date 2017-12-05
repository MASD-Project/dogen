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
#include "dogen/yarn/types/meta_model/exomodel.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

exomodel::exomodel(
    const std::string& documentation,
    const std::list<std::pair<std::string, std::string> >& tagged_values,
    const std::string& id,
    const std::list<dogen::yarn::meta_model::exoelement>& elements,
    const std::list<std::string>& stereotypes)
    : documentation_(documentation),
      tagged_values_(tagged_values),
      id_(id),
      elements_(elements),
      stereotypes_(stereotypes) { }

void exomodel::swap(exomodel& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(tagged_values_, other.tagged_values_);
    swap(id_, other.id_);
    swap(elements_, other.elements_);
    swap(stereotypes_, other.stereotypes_);
}

bool exomodel::operator==(const exomodel& rhs) const {
    return documentation_ == rhs.documentation_ &&
        tagged_values_ == rhs.tagged_values_ &&
        id_ == rhs.id_ &&
        elements_ == rhs.elements_ &&
        stereotypes_ == rhs.stereotypes_;
}

exomodel& exomodel::operator=(exomodel other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& exomodel::documentation() const {
    return documentation_;
}

std::string& exomodel::documentation() {
    return documentation_;
}

void exomodel::documentation(const std::string& v) {
    documentation_ = v;
}

void exomodel::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::list<std::pair<std::string, std::string> >& exomodel::tagged_values() const {
    return tagged_values_;
}

std::list<std::pair<std::string, std::string> >& exomodel::tagged_values() {
    return tagged_values_;
}

void exomodel::tagged_values(const std::list<std::pair<std::string, std::string> >& v) {
    tagged_values_ = v;
}

void exomodel::tagged_values(const std::list<std::pair<std::string, std::string> >&& v) {
    tagged_values_ = std::move(v);
}

const std::string& exomodel::id() const {
    return id_;
}

std::string& exomodel::id() {
    return id_;
}

void exomodel::id(const std::string& v) {
    id_ = v;
}

void exomodel::id(const std::string&& v) {
    id_ = std::move(v);
}

const std::list<dogen::yarn::meta_model::exoelement>& exomodel::elements() const {
    return elements_;
}

std::list<dogen::yarn::meta_model::exoelement>& exomodel::elements() {
    return elements_;
}

void exomodel::elements(const std::list<dogen::yarn::meta_model::exoelement>& v) {
    elements_ = v;
}

void exomodel::elements(const std::list<dogen::yarn::meta_model::exoelement>&& v) {
    elements_ = std::move(v);
}

const std::list<std::string>& exomodel::stereotypes() const {
    return stereotypes_;
}

std::list<std::string>& exomodel::stereotypes() {
    return stereotypes_;
}

void exomodel::stereotypes(const std::list<std::string>& v) {
    stereotypes_ = v;
}

void exomodel::stereotypes(const std::list<std::string>&& v) {
    stereotypes_ = std::move(v);
}

} } }
