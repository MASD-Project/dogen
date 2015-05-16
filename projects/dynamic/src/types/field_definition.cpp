/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/dynamic/types/value.hpp"
#include "dogen/dynamic/types/field_definition.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::dynamic::value>& lhs,
const boost::shared_ptr<dogen::dynamic::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace dynamic {

field_definition::field_definition()
    : value_type_(static_cast<dogen::dynamic::value_types>(0)),
      scope_(static_cast<dogen::dynamic::scope_types>(0)),
      definition_type_(static_cast<dogen::dynamic::field_definition_types>(0)) { }

field_definition::field_definition(
    const dogen::dynamic::name& name,
    const dogen::dynamic::value_types& value_type,
    const dogen::dynamic::scope_types& scope,
    const dogen::dynamic::ownership_hierarchy& ownership_hierarchy,
    const boost::shared_ptr<dogen::dynamic::value>& default_value,
    const dogen::dynamic::field_definition_types& definition_type)
    : name_(name),
      value_type_(value_type),
      scope_(scope),
      ownership_hierarchy_(ownership_hierarchy),
      default_value_(default_value),
      definition_type_(definition_type) { }

void field_definition::swap(field_definition& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(value_type_, other.value_type_);
    swap(scope_, other.scope_);
    swap(ownership_hierarchy_, other.ownership_hierarchy_);
    swap(default_value_, other.default_value_);
    swap(definition_type_, other.definition_type_);
}

bool field_definition::operator==(const field_definition& rhs) const {
    return name_ == rhs.name_ &&
        value_type_ == rhs.value_type_ &&
        scope_ == rhs.scope_ &&
        ownership_hierarchy_ == rhs.ownership_hierarchy_ &&
        default_value_ == rhs.default_value_ &&
        definition_type_ == rhs.definition_type_;
}

field_definition& field_definition::operator=(field_definition other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::dynamic::name& field_definition::name() const {
    return name_;
}

dogen::dynamic::name& field_definition::name() {
    return name_;
}

void field_definition::name(const dogen::dynamic::name& v) {
    name_ = v;
}

void field_definition::name(const dogen::dynamic::name&& v) {
    name_ = std::move(v);
}

dogen::dynamic::value_types field_definition::value_type() const {
    return value_type_;
}

void field_definition::value_type(const dogen::dynamic::value_types& v) {
    value_type_ = v;
}

dogen::dynamic::scope_types field_definition::scope() const {
    return scope_;
}

void field_definition::scope(const dogen::dynamic::scope_types& v) {
    scope_ = v;
}

const dogen::dynamic::ownership_hierarchy& field_definition::ownership_hierarchy() const {
    return ownership_hierarchy_;
}

dogen::dynamic::ownership_hierarchy& field_definition::ownership_hierarchy() {
    return ownership_hierarchy_;
}

void field_definition::ownership_hierarchy(const dogen::dynamic::ownership_hierarchy& v) {
    ownership_hierarchy_ = v;
}

void field_definition::ownership_hierarchy(const dogen::dynamic::ownership_hierarchy&& v) {
    ownership_hierarchy_ = std::move(v);
}

const boost::shared_ptr<dogen::dynamic::value>& field_definition::default_value() const {
    return default_value_;
}

boost::shared_ptr<dogen::dynamic::value>& field_definition::default_value() {
    return default_value_;
}

void field_definition::default_value(const boost::shared_ptr<dogen::dynamic::value>& v) {
    default_value_ = v;
}

void field_definition::default_value(const boost::shared_ptr<dogen::dynamic::value>&& v) {
    default_value_ = std::move(v);
}

dogen::dynamic::field_definition_types field_definition::definition_type() const {
    return definition_type_;
}

void field_definition::definition_type(const dogen::dynamic::field_definition_types& v) {
    definition_type_ = v;
}

} }