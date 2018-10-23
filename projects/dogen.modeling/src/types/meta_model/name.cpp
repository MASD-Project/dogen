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
#include "dogen.modeling/types/meta_model/name.hpp"

namespace dogen::modeling::meta_model {

name::name(
    const std::string& id,
    const std::string& simple,
    const std::map<dogen::modeling::meta_model::languages, std::string>& qualified,
    const dogen::modeling::meta_model::location& location,
    const std::string& identifiable)
    : id_(id),
      simple_(simple),
      qualified_(qualified),
      location_(location),
      identifiable_(identifiable) { }

void name::swap(name& other) noexcept {
    using std::swap;
    swap(id_, other.id_);
    swap(simple_, other.simple_);
    swap(qualified_, other.qualified_);
    swap(location_, other.location_);
    swap(identifiable_, other.identifiable_);
}

bool name::operator==(const name& rhs) const {
    return id_ == rhs.id_ &&
        simple_ == rhs.simple_ &&
        qualified_ == rhs.qualified_ &&
        location_ == rhs.location_ &&
        identifiable_ == rhs.identifiable_;
}

name& name::operator=(name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& name::id() const {
    return id_;
}

std::string& name::id() {
    return id_;
}

void name::id(const std::string& v) {
    id_ = v;
}

void name::id(const std::string&& v) {
    id_ = std::move(v);
}

const std::string& name::simple() const {
    return simple_;
}

std::string& name::simple() {
    return simple_;
}

void name::simple(const std::string& v) {
    simple_ = v;
}

void name::simple(const std::string&& v) {
    simple_ = std::move(v);
}

const std::map<dogen::modeling::meta_model::languages, std::string>& name::qualified() const {
    return qualified_;
}

std::map<dogen::modeling::meta_model::languages, std::string>& name::qualified() {
    return qualified_;
}

void name::qualified(const std::map<dogen::modeling::meta_model::languages, std::string>& v) {
    qualified_ = v;
}

void name::qualified(const std::map<dogen::modeling::meta_model::languages, std::string>&& v) {
    qualified_ = std::move(v);
}

const dogen::modeling::meta_model::location& name::location() const {
    return location_;
}

dogen::modeling::meta_model::location& name::location() {
    return location_;
}

void name::location(const dogen::modeling::meta_model::location& v) {
    location_ = v;
}

void name::location(const dogen::modeling::meta_model::location&& v) {
    location_ = std::move(v);
}

const std::string& name::identifiable() const {
    return identifiable_;
}

std::string& name::identifiable() {
    return identifiable_;
}

void name::identifiable(const std::string& v) {
    identifiable_ = v;
}

void name::identifiable(const std::string&& v) {
    identifiable_ = std::move(v);
}

}
