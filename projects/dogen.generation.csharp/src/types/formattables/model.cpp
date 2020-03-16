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
#include "dogen.generation.csharp/types/formattables/model.hpp"

namespace dogen::generation::csharp::formattables {

model::model(
    const dogen::logical::entities::name& name,
    const std::unordered_map<std::string, dogen::generation::csharp::formattables::formattable>& formattables,
    const std::list<std::string>& project_items,
    const std::unordered_map<std::string, dogen::generation::csharp::formattables::aspect_properties>& aspect_properties,
    const std::unordered_map<std::string, dogen::generation::csharp::formattables::assistant_properties>& assistant_properties)
    : name_(name),
      formattables_(formattables),
      project_items_(project_items),
      aspect_properties_(aspect_properties),
      assistant_properties_(assistant_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(formattables_, other.formattables_);
    swap(project_items_, other.project_items_);
    swap(aspect_properties_, other.aspect_properties_);
    swap(assistant_properties_, other.assistant_properties_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        formattables_ == rhs.formattables_ &&
        project_items_ == rhs.project_items_ &&
        aspect_properties_ == rhs.aspect_properties_ &&
        assistant_properties_ == rhs.assistant_properties_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::logical::entities::name& model::name() const {
    return name_;
}

dogen::logical::entities::name& model::name() {
    return name_;
}

void model::name(const dogen::logical::entities::name& v) {
    name_ = v;
}

void model::name(const dogen::logical::entities::name&& v) {
    name_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::csharp::formattables::formattable>& model::formattables() const {
    return formattables_;
}

std::unordered_map<std::string, dogen::generation::csharp::formattables::formattable>& model::formattables() {
    return formattables_;
}

void model::formattables(const std::unordered_map<std::string, dogen::generation::csharp::formattables::formattable>& v) {
    formattables_ = v;
}

void model::formattables(const std::unordered_map<std::string, dogen::generation::csharp::formattables::formattable>&& v) {
    formattables_ = std::move(v);
}

const std::list<std::string>& model::project_items() const {
    return project_items_;
}

std::list<std::string>& model::project_items() {
    return project_items_;
}

void model::project_items(const std::list<std::string>& v) {
    project_items_ = v;
}

void model::project_items(const std::list<std::string>&& v) {
    project_items_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::csharp::formattables::aspect_properties>& model::aspect_properties() const {
    return aspect_properties_;
}

std::unordered_map<std::string, dogen::generation::csharp::formattables::aspect_properties>& model::aspect_properties() {
    return aspect_properties_;
}

void model::aspect_properties(const std::unordered_map<std::string, dogen::generation::csharp::formattables::aspect_properties>& v) {
    aspect_properties_ = v;
}

void model::aspect_properties(const std::unordered_map<std::string, dogen::generation::csharp::formattables::aspect_properties>&& v) {
    aspect_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::csharp::formattables::assistant_properties>& model::assistant_properties() const {
    return assistant_properties_;
}

std::unordered_map<std::string, dogen::generation::csharp::formattables::assistant_properties>& model::assistant_properties() {
    return assistant_properties_;
}

void model::assistant_properties(const std::unordered_map<std::string, dogen::generation::csharp::formattables::assistant_properties>& v) {
    assistant_properties_ = v;
}

void model::assistant_properties(const std::unordered_map<std::string, dogen::generation::csharp::formattables::assistant_properties>&& v) {
    assistant_properties_ = std::move(v);
}

}
