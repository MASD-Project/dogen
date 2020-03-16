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
#include "dogen.physical/types/entities/element.hpp"

namespace dogen::physical::entities {

element::element(
    const std::string& simple_name,
    const std::string& qualified_name,
    const std::list<std::string>& external_modules,
    const std::list<std::string>& model_modules,
    const std::list<std::string>& internal_modules,
    const std::unordered_map<std::string, dogen::physical::entities::paths>& paths)
    : simple_name_(simple_name),
      qualified_name_(qualified_name),
      external_modules_(external_modules),
      model_modules_(model_modules),
      internal_modules_(internal_modules),
      paths_(paths) { }

void element::swap(element& other) noexcept {
    using std::swap;
    swap(simple_name_, other.simple_name_);
    swap(qualified_name_, other.qualified_name_);
    swap(external_modules_, other.external_modules_);
    swap(model_modules_, other.model_modules_);
    swap(internal_modules_, other.internal_modules_);
    swap(paths_, other.paths_);
}

bool element::operator==(const element& rhs) const {
    return simple_name_ == rhs.simple_name_ &&
        qualified_name_ == rhs.qualified_name_ &&
        external_modules_ == rhs.external_modules_ &&
        model_modules_ == rhs.model_modules_ &&
        internal_modules_ == rhs.internal_modules_ &&
        paths_ == rhs.paths_;
}

element& element::operator=(element other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& element::simple_name() const {
    return simple_name_;
}

std::string& element::simple_name() {
    return simple_name_;
}

void element::simple_name(const std::string& v) {
    simple_name_ = v;
}

void element::simple_name(const std::string&& v) {
    simple_name_ = std::move(v);
}

const std::string& element::qualified_name() const {
    return qualified_name_;
}

std::string& element::qualified_name() {
    return qualified_name_;
}

void element::qualified_name(const std::string& v) {
    qualified_name_ = v;
}

void element::qualified_name(const std::string&& v) {
    qualified_name_ = std::move(v);
}

const std::list<std::string>& element::external_modules() const {
    return external_modules_;
}

std::list<std::string>& element::external_modules() {
    return external_modules_;
}

void element::external_modules(const std::list<std::string>& v) {
    external_modules_ = v;
}

void element::external_modules(const std::list<std::string>&& v) {
    external_modules_ = std::move(v);
}

const std::list<std::string>& element::model_modules() const {
    return model_modules_;
}

std::list<std::string>& element::model_modules() {
    return model_modules_;
}

void element::model_modules(const std::list<std::string>& v) {
    model_modules_ = v;
}

void element::model_modules(const std::list<std::string>&& v) {
    model_modules_ = std::move(v);
}

const std::list<std::string>& element::internal_modules() const {
    return internal_modules_;
}

std::list<std::string>& element::internal_modules() {
    return internal_modules_;
}

void element::internal_modules(const std::list<std::string>& v) {
    internal_modules_ = v;
}

void element::internal_modules(const std::list<std::string>&& v) {
    internal_modules_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::paths>& element::paths() const {
    return paths_;
}

std::unordered_map<std::string, dogen::physical::entities::paths>& element::paths() {
    return paths_;
}

void element::paths(const std::unordered_map<std::string, dogen::physical::entities::paths>& v) {
    paths_ = v;
}

void element::paths(const std::unordered_map<std::string, dogen::physical::entities::paths>&& v) {
    paths_ = std::move(v);
}

}
