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
#include "dogen.physical/types/entities/logical_name.hpp"

namespace dogen::physical::entities {

logical_name::logical_name(
    const std::string& simple,
    const std::string& qualified,
    const std::list<std::string>& external_modules,
    const std::list<std::string>& model_modules,
    const std::list<std::string>& internal_modules)
    : simple_(simple),
      qualified_(qualified),
      external_modules_(external_modules),
      model_modules_(model_modules),
      internal_modules_(internal_modules) { }

void logical_name::swap(logical_name& other) noexcept {
    using std::swap;
    swap(simple_, other.simple_);
    swap(qualified_, other.qualified_);
    swap(external_modules_, other.external_modules_);
    swap(model_modules_, other.model_modules_);
    swap(internal_modules_, other.internal_modules_);
}

bool logical_name::operator==(const logical_name& rhs) const {
    return simple_ == rhs.simple_ &&
        qualified_ == rhs.qualified_ &&
        external_modules_ == rhs.external_modules_ &&
        model_modules_ == rhs.model_modules_ &&
        internal_modules_ == rhs.internal_modules_;
}

logical_name& logical_name::operator=(logical_name other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& logical_name::simple() const {
    return simple_;
}

std::string& logical_name::simple() {
    return simple_;
}

void logical_name::simple(const std::string& v) {
    simple_ = v;
}

void logical_name::simple(const std::string&& v) {
    simple_ = std::move(v);
}

const std::string& logical_name::qualified() const {
    return qualified_;
}

std::string& logical_name::qualified() {
    return qualified_;
}

void logical_name::qualified(const std::string& v) {
    qualified_ = v;
}

void logical_name::qualified(const std::string&& v) {
    qualified_ = std::move(v);
}

const std::list<std::string>& logical_name::external_modules() const {
    return external_modules_;
}

std::list<std::string>& logical_name::external_modules() {
    return external_modules_;
}

void logical_name::external_modules(const std::list<std::string>& v) {
    external_modules_ = v;
}

void logical_name::external_modules(const std::list<std::string>&& v) {
    external_modules_ = std::move(v);
}

const std::list<std::string>& logical_name::model_modules() const {
    return model_modules_;
}

std::list<std::string>& logical_name::model_modules() {
    return model_modules_;
}

void logical_name::model_modules(const std::list<std::string>& v) {
    model_modules_ = v;
}

void logical_name::model_modules(const std::list<std::string>&& v) {
    model_modules_ = std::move(v);
}

const std::list<std::string>& logical_name::internal_modules() const {
    return internal_modules_;
}

std::list<std::string>& logical_name::internal_modules() {
    return internal_modules_;
}

void logical_name::internal_modules(const std::list<std::string>& v) {
    internal_modules_ = v;
}

void logical_name::internal_modules(const std::list<std::string>&& v) {
    internal_modules_ = std::move(v);
}

}
