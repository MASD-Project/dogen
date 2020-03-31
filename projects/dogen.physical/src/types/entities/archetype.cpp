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
#include "dogen.physical/types/entities/archetype.hpp"

namespace dogen::physical::entities {

archetype::archetype(
    const dogen::physical::entities::location& location,
    const std::string& description,
    const dogen::physical::entities::name& name,
    const std::string& default_postfix,
    const std::string& override_postfix,
    const std::string& archetype_kind_id,
    const std::string& meta_element_id,
    const std::string& part)
    : location_(location),
      description_(description),
      name_(name),
      default_postfix_(default_postfix),
      override_postfix_(override_postfix),
      archetype_kind_id_(archetype_kind_id),
      meta_element_id_(meta_element_id),
      part_(part) { }

void archetype::swap(archetype& other) noexcept {
    using std::swap;
    swap(location_, other.location_);
    swap(description_, other.description_);
    swap(name_, other.name_);
    swap(default_postfix_, other.default_postfix_);
    swap(override_postfix_, other.override_postfix_);
    swap(archetype_kind_id_, other.archetype_kind_id_);
    swap(meta_element_id_, other.meta_element_id_);
    swap(part_, other.part_);
}

bool archetype::operator==(const archetype& rhs) const {
    return location_ == rhs.location_ &&
        description_ == rhs.description_ &&
        name_ == rhs.name_ &&
        default_postfix_ == rhs.default_postfix_ &&
        override_postfix_ == rhs.override_postfix_ &&
        archetype_kind_id_ == rhs.archetype_kind_id_ &&
        meta_element_id_ == rhs.meta_element_id_ &&
        part_ == rhs.part_;
}

archetype& archetype::operator=(archetype other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::physical::entities::location& archetype::location() const {
    return location_;
}

dogen::physical::entities::location& archetype::location() {
    return location_;
}

void archetype::location(const dogen::physical::entities::location& v) {
    location_ = v;
}

void archetype::location(const dogen::physical::entities::location&& v) {
    location_ = std::move(v);
}

const std::string& archetype::description() const {
    return description_;
}

std::string& archetype::description() {
    return description_;
}

void archetype::description(const std::string& v) {
    description_ = v;
}

void archetype::description(const std::string&& v) {
    description_ = std::move(v);
}

const dogen::physical::entities::name& archetype::name() const {
    return name_;
}

dogen::physical::entities::name& archetype::name() {
    return name_;
}

void archetype::name(const dogen::physical::entities::name& v) {
    name_ = v;
}

void archetype::name(const dogen::physical::entities::name&& v) {
    name_ = std::move(v);
}

const std::string& archetype::default_postfix() const {
    return default_postfix_;
}

std::string& archetype::default_postfix() {
    return default_postfix_;
}

void archetype::default_postfix(const std::string& v) {
    default_postfix_ = v;
}

void archetype::default_postfix(const std::string&& v) {
    default_postfix_ = std::move(v);
}

const std::string& archetype::override_postfix() const {
    return override_postfix_;
}

std::string& archetype::override_postfix() {
    return override_postfix_;
}

void archetype::override_postfix(const std::string& v) {
    override_postfix_ = v;
}

void archetype::override_postfix(const std::string&& v) {
    override_postfix_ = std::move(v);
}

const std::string& archetype::archetype_kind_id() const {
    return archetype_kind_id_;
}

std::string& archetype::archetype_kind_id() {
    return archetype_kind_id_;
}

void archetype::archetype_kind_id(const std::string& v) {
    archetype_kind_id_ = v;
}

void archetype::archetype_kind_id(const std::string&& v) {
    archetype_kind_id_ = std::move(v);
}

const std::string& archetype::meta_element_id() const {
    return meta_element_id_;
}

std::string& archetype::meta_element_id() {
    return meta_element_id_;
}

void archetype::meta_element_id(const std::string& v) {
    meta_element_id_ = v;
}

void archetype::meta_element_id(const std::string&& v) {
    meta_element_id_ = std::move(v);
}

const std::string& archetype::part() const {
    return part_;
}

std::string& archetype::part() {
    return part_;
}

void archetype::part(const std::string& v) {
    part_ = v;
}

void archetype::part(const std::string&& v) {
    part_ = std::move(v);
}

}
