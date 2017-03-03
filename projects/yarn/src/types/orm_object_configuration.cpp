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
#include "dogen/yarn/types/orm_object_configuration.hpp"

namespace dogen {
namespace yarn {

orm_object_configuration::orm_object_configuration()
    : generate_mapping_(static_cast<bool>(0)),
      is_value_(static_cast<bool>(0)),
      has_primary_key_(static_cast<bool>(0)) { }

orm_object_configuration::orm_object_configuration(
    const bool generate_mapping,
    const std::string& schema_name,
    const std::string& table_name,
    const bool is_value,
    const bool has_primary_key)
    : generate_mapping_(generate_mapping),
      schema_name_(schema_name),
      table_name_(table_name),
      is_value_(is_value),
      has_primary_key_(has_primary_key) { }

void orm_object_configuration::swap(orm_object_configuration& other) noexcept {
    using std::swap;
    swap(generate_mapping_, other.generate_mapping_);
    swap(schema_name_, other.schema_name_);
    swap(table_name_, other.table_name_);
    swap(is_value_, other.is_value_);
    swap(has_primary_key_, other.has_primary_key_);
}

bool orm_object_configuration::operator==(const orm_object_configuration& rhs) const {
    return generate_mapping_ == rhs.generate_mapping_ &&
        schema_name_ == rhs.schema_name_ &&
        table_name_ == rhs.table_name_ &&
        is_value_ == rhs.is_value_ &&
        has_primary_key_ == rhs.has_primary_key_;
}

orm_object_configuration& orm_object_configuration::operator=(orm_object_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool orm_object_configuration::generate_mapping() const {
    return generate_mapping_;
}

void orm_object_configuration::generate_mapping(const bool v) {
    generate_mapping_ = v;
}

const std::string& orm_object_configuration::schema_name() const {
    return schema_name_;
}

std::string& orm_object_configuration::schema_name() {
    return schema_name_;
}

void orm_object_configuration::schema_name(const std::string& v) {
    schema_name_ = v;
}

void orm_object_configuration::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

const std::string& orm_object_configuration::table_name() const {
    return table_name_;
}

std::string& orm_object_configuration::table_name() {
    return table_name_;
}

void orm_object_configuration::table_name(const std::string& v) {
    table_name_ = v;
}

void orm_object_configuration::table_name(const std::string&& v) {
    table_name_ = std::move(v);
}

bool orm_object_configuration::is_value() const {
    return is_value_;
}

void orm_object_configuration::is_value(const bool v) {
    is_value_ = v;
}

bool orm_object_configuration::has_primary_key() const {
    return has_primary_key_;
}

void orm_object_configuration::has_primary_key(const bool v) {
    has_primary_key_ = v;
}

} }
