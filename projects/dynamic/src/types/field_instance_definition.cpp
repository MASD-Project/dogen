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
#include "dogen/dynamic/types/field_instance_definition.hpp"

namespace dogen {
namespace dynamic {

field_instance_definition::field_instance_definition()
    : definition_types_(static_cast<dogen::dynamic::field_definition_types>(0)) { }

field_instance_definition::field_instance_definition(
    const std::string& name,
    const dogen::dynamic::ownership_hierarchy& ownership_hierarchy,
    const std::list<std::string>& value,
    const dogen::dynamic::field_definition_types definition_types)
    : name_(name),
      ownership_hierarchy_(ownership_hierarchy),
      value_(value),
      definition_types_(definition_types) { }

void field_instance_definition::swap(field_instance_definition& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(ownership_hierarchy_, other.ownership_hierarchy_);
    swap(value_, other.value_);
    swap(definition_types_, other.definition_types_);
}

bool field_instance_definition::operator==(const field_instance_definition& rhs) const {
    return name_ == rhs.name_ &&
        ownership_hierarchy_ == rhs.ownership_hierarchy_ &&
        value_ == rhs.value_ &&
        definition_types_ == rhs.definition_types_;
}

field_instance_definition& field_instance_definition::operator=(field_instance_definition other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& field_instance_definition::name() const {
    return name_;
}

std::string& field_instance_definition::name() {
    return name_;
}

void field_instance_definition::name(const std::string& v) {
    name_ = v;
}

void field_instance_definition::name(const std::string&& v) {
    name_ = std::move(v);
}

const dogen::dynamic::ownership_hierarchy& field_instance_definition::ownership_hierarchy() const {
    return ownership_hierarchy_;
}

dogen::dynamic::ownership_hierarchy& field_instance_definition::ownership_hierarchy() {
    return ownership_hierarchy_;
}

void field_instance_definition::ownership_hierarchy(const dogen::dynamic::ownership_hierarchy& v) {
    ownership_hierarchy_ = v;
}

void field_instance_definition::ownership_hierarchy(const dogen::dynamic::ownership_hierarchy&& v) {
    ownership_hierarchy_ = std::move(v);
}

const std::list<std::string>& field_instance_definition::value() const {
    return value_;
}

std::list<std::string>& field_instance_definition::value() {
    return value_;
}

void field_instance_definition::value(const std::list<std::string>& v) {
    value_ = v;
}

void field_instance_definition::value(const std::list<std::string>&& v) {
    value_ = std::move(v);
}

dogen::dynamic::field_definition_types field_instance_definition::definition_types() const {
    return definition_types_;
}

void field_instance_definition::definition_types(const dogen::dynamic::field_definition_types v) {
    definition_types_ = v;
}

} }
