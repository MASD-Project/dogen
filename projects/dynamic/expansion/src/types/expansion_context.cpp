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
#include "dogen/dynamic/expansion/types/expansion_context.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

expansion_context::expansion_context(
    const dogen::sml::model& model,
    const dogen::dynamic::schema::object& root_module,
    const std::list<dogen::dynamic::schema::field_definition>& field_definitions)
    : model_(model),
      root_module_(root_module),
      field_definitions_(field_definitions) { }

void expansion_context::swap(expansion_context& other) noexcept {
    using std::swap;
    swap(model_, other.model_);
    swap(root_module_, other.root_module_);
    swap(field_definitions_, other.field_definitions_);
}

bool expansion_context::operator==(const expansion_context& rhs) const {
    return model_ == rhs.model_ &&
        root_module_ == rhs.root_module_ &&
        field_definitions_ == rhs.field_definitions_;
}

expansion_context& expansion_context::operator=(expansion_context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::sml::model& expansion_context::model() const {
    return model_;
}

dogen::sml::model& expansion_context::model() {
    return model_;
}

void expansion_context::model(const dogen::sml::model& v) {
    model_ = v;
}

void expansion_context::model(const dogen::sml::model&& v) {
    model_ = std::move(v);
}

const dogen::dynamic::schema::object& expansion_context::root_module() const {
    return root_module_;
}

dogen::dynamic::schema::object& expansion_context::root_module() {
    return root_module_;
}

void expansion_context::root_module(const dogen::dynamic::schema::object& v) {
    root_module_ = v;
}

void expansion_context::root_module(const dogen::dynamic::schema::object&& v) {
    root_module_ = std::move(v);
}

const std::list<dogen::dynamic::schema::field_definition>& expansion_context::field_definitions() const {
    return field_definitions_;
}

std::list<dogen::dynamic::schema::field_definition>& expansion_context::field_definitions() {
    return field_definitions_;
}

void expansion_context::field_definitions(const std::list<dogen::dynamic::schema::field_definition>& v) {
    field_definitions_ = v;
}

void expansion_context::field_definitions(const std::list<dogen::dynamic::schema::field_definition>&& v) {
    field_definitions_ = std::move(v);
}

} } }