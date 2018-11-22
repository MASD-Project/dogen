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
#include "masd.dogen.modeling/types/meta_model/orm_model_properties.hpp"

namespace masd::dogen::modeling::meta_model {

orm_model_properties::orm_model_properties(orm_model_properties&& rhs)
    : database_systems_(std::move(rhs.database_systems_)),
      schema_name_(std::move(rhs.schema_name_)),
      letter_case_(std::move(rhs.letter_case_)) { }

orm_model_properties::orm_model_properties(
    const std::vector<masd::dogen::modeling::meta_model::orm_database_systems>& database_systems,
    const std::string& schema_name,
    const boost::optional<masd::dogen::modeling::meta_model::letter_cases>& letter_case)
    : database_systems_(database_systems),
      schema_name_(schema_name),
      letter_case_(letter_case) { }

void orm_model_properties::swap(orm_model_properties& other) noexcept {
    using std::swap;
    swap(database_systems_, other.database_systems_);
    swap(schema_name_, other.schema_name_);
    swap(letter_case_, other.letter_case_);
}

bool orm_model_properties::operator==(const orm_model_properties& rhs) const {
    return database_systems_ == rhs.database_systems_ &&
        schema_name_ == rhs.schema_name_ &&
        letter_case_ == rhs.letter_case_;
}

orm_model_properties& orm_model_properties::operator=(orm_model_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<masd::dogen::modeling::meta_model::orm_database_systems>& orm_model_properties::database_systems() const {
    return database_systems_;
}

std::vector<masd::dogen::modeling::meta_model::orm_database_systems>& orm_model_properties::database_systems() {
    return database_systems_;
}

void orm_model_properties::database_systems(const std::vector<masd::dogen::modeling::meta_model::orm_database_systems>& v) {
    database_systems_ = v;
}

void orm_model_properties::database_systems(const std::vector<masd::dogen::modeling::meta_model::orm_database_systems>&& v) {
    database_systems_ = std::move(v);
}

const std::string& orm_model_properties::schema_name() const {
    return schema_name_;
}

std::string& orm_model_properties::schema_name() {
    return schema_name_;
}

void orm_model_properties::schema_name(const std::string& v) {
    schema_name_ = v;
}

void orm_model_properties::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

const boost::optional<masd::dogen::modeling::meta_model::letter_cases>& orm_model_properties::letter_case() const {
    return letter_case_;
}

boost::optional<masd::dogen::modeling::meta_model::letter_cases>& orm_model_properties::letter_case() {
    return letter_case_;
}

void orm_model_properties::letter_case(const boost::optional<masd::dogen::modeling::meta_model::letter_cases>& v) {
    letter_case_ = v;
}

void orm_model_properties::letter_case(const boost::optional<masd::dogen::modeling::meta_model::letter_cases>&& v) {
    letter_case_ = std::move(v);
}

}
