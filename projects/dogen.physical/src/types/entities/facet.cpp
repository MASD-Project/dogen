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
#include "dogen.physical/types/entities/facet.hpp"

namespace dogen::physical::entities {

facet::facet(
    const std::string& directory_name,
    const dogen::physical::entities::location& location,
    const std::string& description,
    const std::string& postfix,
    const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes)
    : directory_name_(directory_name),
      location_(location),
      description_(description),
      postfix_(postfix),
      archetypes_(archetypes) { }

void facet::swap(facet& other) noexcept {
    using std::swap;
    swap(directory_name_, other.directory_name_);
    swap(location_, other.location_);
    swap(description_, other.description_);
    swap(postfix_, other.postfix_);
    swap(archetypes_, other.archetypes_);
}

bool facet::operator==(const facet& rhs) const {
    return directory_name_ == rhs.directory_name_ &&
        location_ == rhs.location_ &&
        description_ == rhs.description_ &&
        postfix_ == rhs.postfix_ &&
        archetypes_ == rhs.archetypes_;
}

facet& facet::operator=(facet other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& facet::directory_name() const {
    return directory_name_;
}

std::string& facet::directory_name() {
    return directory_name_;
}

void facet::directory_name(const std::string& v) {
    directory_name_ = v;
}

void facet::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

const dogen::physical::entities::location& facet::location() const {
    return location_;
}

dogen::physical::entities::location& facet::location() {
    return location_;
}

void facet::location(const dogen::physical::entities::location& v) {
    location_ = v;
}

void facet::location(const dogen::physical::entities::location&& v) {
    location_ = std::move(v);
}

const std::string& facet::description() const {
    return description_;
}

std::string& facet::description() {
    return description_;
}

void facet::description(const std::string& v) {
    description_ = v;
}

void facet::description(const std::string&& v) {
    description_ = std::move(v);
}

const std::string& facet::postfix() const {
    return postfix_;
}

std::string& facet::postfix() {
    return postfix_;
}

void facet::postfix(const std::string& v) {
    postfix_ = v;
}

void facet::postfix(const std::string&& v) {
    postfix_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::archetype>& facet::archetypes() const {
    return archetypes_;
}

std::unordered_map<std::string, dogen::physical::entities::archetype>& facet::archetypes() {
    return archetypes_;
}

void facet::archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v) {
    archetypes_ = v;
}

void facet::archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v) {
    archetypes_ = std::move(v);
}

}
