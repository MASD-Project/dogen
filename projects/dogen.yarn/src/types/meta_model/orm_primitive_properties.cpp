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
#include "dogen.yarn/types/meta_model/orm_primitive_properties.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

orm_primitive_properties::orm_primitive_properties()
    : generate_mapping_(static_cast<bool>(0)) { }

orm_primitive_properties::orm_primitive_properties(orm_primitive_properties&& rhs)
    : generate_mapping_(std::move(rhs.generate_mapping_)),
      schema_name_(std::move(rhs.schema_name_)),
      letter_case_(std::move(rhs.letter_case_)) { }

orm_primitive_properties::orm_primitive_properties(
    const bool generate_mapping,
    const std::string& schema_name,
    const boost::optional<dogen::yarn::meta_model::letter_cases>& letter_case)
    : generate_mapping_(generate_mapping),
      schema_name_(schema_name),
      letter_case_(letter_case) { }

void orm_primitive_properties::swap(orm_primitive_properties& other) noexcept {
    using std::swap;
    swap(generate_mapping_, other.generate_mapping_);
    swap(schema_name_, other.schema_name_);
    swap(letter_case_, other.letter_case_);
}

bool orm_primitive_properties::operator==(const orm_primitive_properties& rhs) const {
    return generate_mapping_ == rhs.generate_mapping_ &&
        schema_name_ == rhs.schema_name_ &&
        letter_case_ == rhs.letter_case_;
}

orm_primitive_properties& orm_primitive_properties::operator=(orm_primitive_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool orm_primitive_properties::generate_mapping() const {
    return generate_mapping_;
}

void orm_primitive_properties::generate_mapping(const bool v) {
    generate_mapping_ = v;
}

const std::string& orm_primitive_properties::schema_name() const {
    return schema_name_;
}

std::string& orm_primitive_properties::schema_name() {
    return schema_name_;
}

void orm_primitive_properties::schema_name(const std::string& v) {
    schema_name_ = v;
}

void orm_primitive_properties::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

const boost::optional<dogen::yarn::meta_model::letter_cases>& orm_primitive_properties::letter_case() const {
    return letter_case_;
}

boost::optional<dogen::yarn::meta_model::letter_cases>& orm_primitive_properties::letter_case() {
    return letter_case_;
}

void orm_primitive_properties::letter_case(const boost::optional<dogen::yarn::meta_model::letter_cases>& v) {
    letter_case_ = v;
}

void orm_primitive_properties::letter_case(const boost::optional<dogen::yarn::meta_model::letter_cases>&& v) {
    letter_case_ = std::move(v);
}

} } }
