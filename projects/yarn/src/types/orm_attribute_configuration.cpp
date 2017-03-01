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
#include "dogen/yarn/types/orm_attribute_configuration.hpp"

namespace dogen {
namespace yarn {

orm_attribute_configuration::orm_attribute_configuration()
    : is_primary_key_(static_cast<bool>(0)),
      is_nullable_(static_cast<bool>(0)) { }

orm_attribute_configuration::orm_attribute_configuration(
    const std::string& column_name,
    const bool is_primary_key,
    const bool is_nullable,
    const std::unordered_map<dogen::yarn::orm_database_systems, std::string>& type_overrides)
    : column_name_(column_name),
      is_primary_key_(is_primary_key),
      is_nullable_(is_nullable),
      type_overrides_(type_overrides) { }

void orm_attribute_configuration::swap(orm_attribute_configuration& other) noexcept {
    using std::swap;
    swap(column_name_, other.column_name_);
    swap(is_primary_key_, other.is_primary_key_);
    swap(is_nullable_, other.is_nullable_);
    swap(type_overrides_, other.type_overrides_);
}

bool orm_attribute_configuration::operator==(const orm_attribute_configuration& rhs) const {
    return column_name_ == rhs.column_name_ &&
        is_primary_key_ == rhs.is_primary_key_ &&
        is_nullable_ == rhs.is_nullable_ &&
        type_overrides_ == rhs.type_overrides_;
}

orm_attribute_configuration& orm_attribute_configuration::operator=(orm_attribute_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& orm_attribute_configuration::column_name() const {
    return column_name_;
}

std::string& orm_attribute_configuration::column_name() {
    return column_name_;
}

void orm_attribute_configuration::column_name(const std::string& v) {
    column_name_ = v;
}

void orm_attribute_configuration::column_name(const std::string&& v) {
    column_name_ = std::move(v);
}

bool orm_attribute_configuration::is_primary_key() const {
    return is_primary_key_;
}

void orm_attribute_configuration::is_primary_key(const bool v) {
    is_primary_key_ = v;
}

bool orm_attribute_configuration::is_nullable() const {
    return is_nullable_;
}

void orm_attribute_configuration::is_nullable(const bool v) {
    is_nullable_ = v;
}

const std::unordered_map<dogen::yarn::orm_database_systems, std::string>& orm_attribute_configuration::type_overrides() const {
    return type_overrides_;
}

std::unordered_map<dogen::yarn::orm_database_systems, std::string>& orm_attribute_configuration::type_overrides() {
    return type_overrides_;
}

void orm_attribute_configuration::type_overrides(const std::unordered_map<dogen::yarn::orm_database_systems, std::string>& v) {
    type_overrides_ = v;
}

void orm_attribute_configuration::type_overrides(const std::unordered_map<dogen::yarn::orm_database_systems, std::string>&& v) {
    type_overrides_ = std::move(v);
}

} }
