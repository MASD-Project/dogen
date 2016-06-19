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
#include "dogen/yarn/types/name.hpp"

namespace dogen {
namespace yarn {

name::name(
    const std::string& id,
    const std::string& simple,
    const std::map<dogen::yarn::language, std::string>& qualified_for,
    const std::string& identifiable,
    const dogen::yarn::location& location)
    : id_(id),
      simple_(simple),
      qualified_for_(qualified_for),
      identifiable_(identifiable),
      location_(location) { }

void name::swap(name& other) noexcept {
    using std::swap;
    swap(id_, other.id_);
    swap(simple_, other.simple_);
    swap(qualified_for_, other.qualified_for_);
    swap(identifiable_, other.identifiable_);
    swap(location_, other.location_);
}

bool name::operator==(const name& rhs) const {
    return id_ == rhs.id_ &&
        simple_ == rhs.simple_ &&
        qualified_for_ == rhs.qualified_for_ &&
        identifiable_ == rhs.identifiable_ &&
        location_ == rhs.location_;
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

const std::map<dogen::yarn::language, std::string>& name::qualified_for() const {
    return qualified_for_;
}

std::map<dogen::yarn::language, std::string>& name::qualified_for() {
    return qualified_for_;
}

void name::qualified_for(const std::map<dogen::yarn::language, std::string>& v) {
    qualified_for_ = v;
}

void name::qualified_for(const std::map<dogen::yarn::language, std::string>&& v) {
    qualified_for_ = std::move(v);
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

const dogen::yarn::location& name::location() const {
    return location_;
}

dogen::yarn::location& name::location() {
    return location_;
}

void name::location(const dogen::yarn::location& v) {
    location_ = v;
}

void name::location(const dogen::yarn::location&& v) {
    location_ = std::move(v);
}

} }
