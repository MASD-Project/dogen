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
#include "dogen.physical/types/entities/logical_location.hpp"

namespace dogen::physical::entities {

logical_location::logical_location(
    const std::string& simple_name,
    const std::string& qualified_name,
    const std::list<std::string>& external_modules,
    const std::list<std::string>& model_modules,
    const std::list<std::string>& internal_modules)
    : simple_name_(simple_name),
      qualified_name_(qualified_name),
      external_modules_(external_modules),
      model_modules_(model_modules),
      internal_modules_(internal_modules) { }

void logical_location::swap(logical_location& other) noexcept {
    using std::swap;
    swap(simple_name_, other.simple_name_);
    swap(qualified_name_, other.qualified_name_);
    swap(external_modules_, other.external_modules_);
    swap(model_modules_, other.model_modules_);
    swap(internal_modules_, other.internal_modules_);
}

bool logical_location::operator==(const logical_location& rhs) const {
    return simple_name_ == rhs.simple_name_ &&
        qualified_name_ == rhs.qualified_name_ &&
        external_modules_ == rhs.external_modules_ &&
        model_modules_ == rhs.model_modules_ &&
        internal_modules_ == rhs.internal_modules_;
}

logical_location& logical_location::operator=(logical_location other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& logical_location::simple_name() const {
    return simple_name_;
}

std::string& logical_location::simple_name() {
    return simple_name_;
}

void logical_location::simple_name(const std::string& v) {
    simple_name_ = v;
}

void logical_location::simple_name(const std::string&& v) {
    simple_name_ = std::move(v);
}

const std::string& logical_location::qualified_name() const {
    return qualified_name_;
}

std::string& logical_location::qualified_name() {
    return qualified_name_;
}

void logical_location::qualified_name(const std::string& v) {
    qualified_name_ = v;
}

void logical_location::qualified_name(const std::string&& v) {
    qualified_name_ = std::move(v);
}

const std::list<std::string>& logical_location::external_modules() const {
    return external_modules_;
}

std::list<std::string>& logical_location::external_modules() {
    return external_modules_;
}

void logical_location::external_modules(const std::list<std::string>& v) {
    external_modules_ = v;
}

void logical_location::external_modules(const std::list<std::string>&& v) {
    external_modules_ = std::move(v);
}

const std::list<std::string>& logical_location::model_modules() const {
    return model_modules_;
}

std::list<std::string>& logical_location::model_modules() {
    return model_modules_;
}

void logical_location::model_modules(const std::list<std::string>& v) {
    model_modules_ = v;
}

void logical_location::model_modules(const std::list<std::string>&& v) {
    model_modules_ = std::move(v);
}

const std::list<std::string>& logical_location::internal_modules() const {
    return internal_modules_;
}

std::list<std::string>& logical_location::internal_modules() {
    return internal_modules_;
}

void logical_location::internal_modules(const std::list<std::string>& v) {
    internal_modules_ = v;
}

void logical_location::internal_modules(const std::list<std::string>&& v) {
    internal_modules_ = std::move(v);
}

}
