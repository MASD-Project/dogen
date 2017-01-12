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
#include "dogen/upsilon/types/type_name.hpp"

namespace dogen {
namespace upsilon {

type_name::type_name(
    const std::string& name,
    const std::string& schema_name)
    : name_(name),
      schema_name_(schema_name) { }

void type_name::swap(type_name& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(schema_name_, other.schema_name_);
}

bool type_name::operator==(const type_name& rhs) const {
    return name_ == rhs.name_ &&
        schema_name_ == rhs.schema_name_;
}

type_name& type_name::operator=(type_name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& type_name::name() const {
    return name_;
}

std::string& type_name::name() {
    return name_;
}

void type_name::name(const std::string& v) {
    name_ = v;
}

void type_name::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& type_name::schema_name() const {
    return schema_name_;
}

std::string& type_name::schema_name() {
    return schema_name_;
}

void type_name::schema_name(const std::string& v) {
    schema_name_ = v;
}

void type_name::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

} }
