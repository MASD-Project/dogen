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
#include "dogen.logical/types/entities/orm/attribute_properties.hpp"

namespace dogen::logical::entities::orm {

attribute_properties::attribute_properties()
    : is_primary_key_(static_cast<bool>(0)),
      is_composite_(static_cast<bool>(0)) { }

attribute_properties::attribute_properties(attribute_properties&& rhs)
    : type_overrides_(std::move(rhs.type_overrides_)),
      odb_pragmas_(std::move(rhs.odb_pragmas_)),
      column_name_(std::move(rhs.column_name_)),
      is_primary_key_(std::move(rhs.is_primary_key_)),
      is_nullable_(std::move(rhs.is_nullable_)),
      is_composite_(std::move(rhs.is_composite_)) { }

attribute_properties::attribute_properties(
    const std::unordered_map<dogen::logical::entities::orm::database_system, std::string>& type_overrides,
    const std::list<std::string>& odb_pragmas,
    const std::string& column_name,
    const bool is_primary_key,
    const boost::optional<bool>& is_nullable,
    const bool is_composite)
    : type_overrides_(type_overrides),
      odb_pragmas_(odb_pragmas),
      column_name_(column_name),
      is_primary_key_(is_primary_key),
      is_nullable_(is_nullable),
      is_composite_(is_composite) { }

void attribute_properties::swap(attribute_properties& other) noexcept {
    using std::swap;
    swap(type_overrides_, other.type_overrides_);
    swap(odb_pragmas_, other.odb_pragmas_);
    swap(column_name_, other.column_name_);
    swap(is_primary_key_, other.is_primary_key_);
    swap(is_nullable_, other.is_nullable_);
    swap(is_composite_, other.is_composite_);
}

bool attribute_properties::operator==(const attribute_properties& rhs) const {
    return type_overrides_ == rhs.type_overrides_ &&
        odb_pragmas_ == rhs.odb_pragmas_ &&
        column_name_ == rhs.column_name_ &&
        is_primary_key_ == rhs.is_primary_key_ &&
        is_nullable_ == rhs.is_nullable_ &&
        is_composite_ == rhs.is_composite_;
}

attribute_properties& attribute_properties::operator=(attribute_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::logical::entities::orm::database_system, std::string>& attribute_properties::type_overrides() const {
    return type_overrides_;
}

std::unordered_map<dogen::logical::entities::orm::database_system, std::string>& attribute_properties::type_overrides() {
    return type_overrides_;
}

void attribute_properties::type_overrides(const std::unordered_map<dogen::logical::entities::orm::database_system, std::string>& v) {
    type_overrides_ = v;
}

void attribute_properties::type_overrides(const std::unordered_map<dogen::logical::entities::orm::database_system, std::string>&& v) {
    type_overrides_ = std::move(v);
}

const std::list<std::string>& attribute_properties::odb_pragmas() const {
    return odb_pragmas_;
}

std::list<std::string>& attribute_properties::odb_pragmas() {
    return odb_pragmas_;
}

void attribute_properties::odb_pragmas(const std::list<std::string>& v) {
    odb_pragmas_ = v;
}

void attribute_properties::odb_pragmas(const std::list<std::string>&& v) {
    odb_pragmas_ = std::move(v);
}

const std::string& attribute_properties::column_name() const {
    return column_name_;
}

std::string& attribute_properties::column_name() {
    return column_name_;
}

void attribute_properties::column_name(const std::string& v) {
    column_name_ = v;
}

void attribute_properties::column_name(const std::string&& v) {
    column_name_ = std::move(v);
}

bool attribute_properties::is_primary_key() const {
    return is_primary_key_;
}

void attribute_properties::is_primary_key(const bool v) {
    is_primary_key_ = v;
}

const boost::optional<bool>& attribute_properties::is_nullable() const {
    return is_nullable_;
}

boost::optional<bool>& attribute_properties::is_nullable() {
    return is_nullable_;
}

void attribute_properties::is_nullable(const boost::optional<bool>& v) {
    is_nullable_ = v;
}

void attribute_properties::is_nullable(const boost::optional<bool>&& v) {
    is_nullable_ = std::move(v);
}

bool attribute_properties::is_composite() const {
    return is_composite_;
}

void attribute_properties::is_composite(const bool v) {
    is_composite_ = v;
}

}
