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
#include "dogen.logical/types/meta_model/orm/module_properties.hpp"

namespace dogen::logical::meta_model::orm {

module_properties::module_properties(module_properties&& rhs)
    : schema_name_(std::move(rhs.schema_name_)),
      capitalised_schema_name_(std::move(rhs.capitalised_schema_name_)),
      letter_case_(std::move(rhs.letter_case_)) { }

module_properties::module_properties(
    const std::string& schema_name,
    const std::string& capitalised_schema_name,
    const boost::optional<dogen::logical::meta_model::orm::letter_case>& letter_case)
    : schema_name_(schema_name),
      capitalised_schema_name_(capitalised_schema_name),
      letter_case_(letter_case) { }

void module_properties::swap(module_properties& other) noexcept {
    using std::swap;
    swap(schema_name_, other.schema_name_);
    swap(capitalised_schema_name_, other.capitalised_schema_name_);
    swap(letter_case_, other.letter_case_);
}

bool module_properties::operator==(const module_properties& rhs) const {
    return schema_name_ == rhs.schema_name_ &&
        capitalised_schema_name_ == rhs.capitalised_schema_name_ &&
        letter_case_ == rhs.letter_case_;
}

module_properties& module_properties::operator=(module_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& module_properties::schema_name() const {
    return schema_name_;
}

std::string& module_properties::schema_name() {
    return schema_name_;
}

void module_properties::schema_name(const std::string& v) {
    schema_name_ = v;
}

void module_properties::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

const std::string& module_properties::capitalised_schema_name() const {
    return capitalised_schema_name_;
}

std::string& module_properties::capitalised_schema_name() {
    return capitalised_schema_name_;
}

void module_properties::capitalised_schema_name(const std::string& v) {
    capitalised_schema_name_ = v;
}

void module_properties::capitalised_schema_name(const std::string&& v) {
    capitalised_schema_name_ = std::move(v);
}

const boost::optional<dogen::logical::meta_model::orm::letter_case>& module_properties::letter_case() const {
    return letter_case_;
}

boost::optional<dogen::logical::meta_model::orm::letter_case>& module_properties::letter_case() {
    return letter_case_;
}

void module_properties::letter_case(const boost::optional<dogen::logical::meta_model::orm::letter_case>& v) {
    letter_case_ = v;
}

void module_properties::letter_case(const boost::optional<dogen::logical::meta_model::orm::letter_case>&& v) {
    letter_case_ = std::move(v);
}

}
