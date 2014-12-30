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
#include "dogen/dynamic/types/field_definition.hpp"

namespace dogen {
namespace dynamic {

field_definition::field_definition()
    : type_(static_cast<dogen::dynamic::value_types>(0)),
      scope_(static_cast<dogen::dynamic::scope_types>(0)),
      is_mandatory_(static_cast<bool>(0)) { }

field_definition::field_definition(
    const dogen::dynamic::name& name,
    const dogen::dynamic::value_types& type,
    const dogen::dynamic::scope_types& scope,
    const bool is_mandatory)
    : name_(name),
      type_(type),
      scope_(scope),
      is_mandatory_(is_mandatory) { }

void field_definition::swap(field_definition& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(type_, other.type_);
    swap(scope_, other.scope_);
    swap(is_mandatory_, other.is_mandatory_);
}

bool field_definition::operator==(const field_definition& rhs) const {
    return name_ == rhs.name_ &&
        type_ == rhs.type_ &&
        scope_ == rhs.scope_ &&
        is_mandatory_ == rhs.is_mandatory_;
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

dogen::dynamic::value_types field_definition::type() const {
    return type_;
}

void field_definition::type(const dogen::dynamic::value_types& v) {
    type_ = v;
}

dogen::dynamic::scope_types field_definition::scope() const {
    return scope_;
}

void field_definition::scope(const dogen::dynamic::scope_types& v) {
    scope_ = v;
}

bool field_definition::is_mandatory() const {
    return is_mandatory_;
}

void field_definition::is_mandatory(const bool v) {
    is_mandatory_ = v;
}

} }