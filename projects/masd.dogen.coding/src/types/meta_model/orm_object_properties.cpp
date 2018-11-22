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
#include "masd.dogen.modeling/types/meta_model/orm_object_properties.hpp"

namespace masd::dogen::modeling::meta_model {

orm_object_properties::orm_object_properties()
    : generate_mapping_(static_cast<bool>(0)),
      is_value_(static_cast<bool>(0)),
      has_primary_key_(static_cast<bool>(0)) { }

orm_object_properties::orm_object_properties(orm_object_properties&& rhs)
    : generate_mapping_(std::move(rhs.generate_mapping_)),
      schema_name_(std::move(rhs.schema_name_)),
      table_name_(std::move(rhs.table_name_)),
      is_value_(std::move(rhs.is_value_)),
      has_primary_key_(std::move(rhs.has_primary_key_)),
      letter_case_(std::move(rhs.letter_case_)) { }

orm_object_properties::orm_object_properties(
    const bool generate_mapping,
    const std::string& schema_name,
    const std::string& table_name,
    const bool is_value,
    const bool has_primary_key,
    const boost::optional<masd::dogen::modeling::meta_model::letter_cases>& letter_case)
    : generate_mapping_(generate_mapping),
      schema_name_(schema_name),
      table_name_(table_name),
      is_value_(is_value),
      has_primary_key_(has_primary_key),
      letter_case_(letter_case) { }

void orm_object_properties::swap(orm_object_properties& other) noexcept {
    using std::swap;
    swap(generate_mapping_, other.generate_mapping_);
    swap(schema_name_, other.schema_name_);
    swap(table_name_, other.table_name_);
    swap(is_value_, other.is_value_);
    swap(has_primary_key_, other.has_primary_key_);
    swap(letter_case_, other.letter_case_);
}

bool orm_object_properties::operator==(const orm_object_properties& rhs) const {
    return generate_mapping_ == rhs.generate_mapping_ &&
        schema_name_ == rhs.schema_name_ &&
        table_name_ == rhs.table_name_ &&
        is_value_ == rhs.is_value_ &&
        has_primary_key_ == rhs.has_primary_key_ &&
        letter_case_ == rhs.letter_case_;
}

orm_object_properties& orm_object_properties::operator=(orm_object_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool orm_object_properties::generate_mapping() const {
    return generate_mapping_;
}

void orm_object_properties::generate_mapping(const bool v) {
    generate_mapping_ = v;
}

const std::string& orm_object_properties::schema_name() const {
    return schema_name_;
}

std::string& orm_object_properties::schema_name() {
    return schema_name_;
}

void orm_object_properties::schema_name(const std::string& v) {
    schema_name_ = v;
}

void orm_object_properties::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

const std::string& orm_object_properties::table_name() const {
    return table_name_;
}

std::string& orm_object_properties::table_name() {
    return table_name_;
}

void orm_object_properties::table_name(const std::string& v) {
    table_name_ = v;
}

void orm_object_properties::table_name(const std::string&& v) {
    table_name_ = std::move(v);
}

bool orm_object_properties::is_value() const {
    return is_value_;
}

void orm_object_properties::is_value(const bool v) {
    is_value_ = v;
}

bool orm_object_properties::has_primary_key() const {
    return has_primary_key_;
}

void orm_object_properties::has_primary_key(const bool v) {
    has_primary_key_ = v;
}

const boost::optional<masd::dogen::modeling::meta_model::letter_cases>& orm_object_properties::letter_case() const {
    return letter_case_;
}

boost::optional<masd::dogen::modeling::meta_model::letter_cases>& orm_object_properties::letter_case() {
    return letter_case_;
}

void orm_object_properties::letter_case(const boost::optional<masd::dogen::modeling::meta_model::letter_cases>& v) {
    letter_case_ = v;
}

void orm_object_properties::letter_case(const boost::optional<masd::dogen::modeling::meta_model::letter_cases>&& v) {
    letter_case_ = std::move(v);
}

}
