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
#include "dogen/annotations/types/repository.hpp"

namespace dogen {
namespace annotations {

repository::repository(
    const std::list<dogen::annotations::type>& all_field_definitions,
    const std::unordered_map<std::string, dogen::annotations::type>& field_definitions_by_name,
    const std::unordered_map<std::string, std::list<dogen::annotations::type> >& field_definitions_by_facet_name,
    const std::unordered_map<std::string, std::list<dogen::annotations::type> >& field_definitions_by_formatter_name,
    const std::unordered_map<std::string, std::list<dogen::annotations::type> >& field_definitions_by_model_name)
    : all_field_definitions_(all_field_definitions),
      field_definitions_by_name_(field_definitions_by_name),
      field_definitions_by_facet_name_(field_definitions_by_facet_name),
      field_definitions_by_formatter_name_(field_definitions_by_formatter_name),
      field_definitions_by_model_name_(field_definitions_by_model_name) { }

void repository::swap(repository& other) noexcept {
    using std::swap;
    swap(all_field_definitions_, other.all_field_definitions_);
    swap(field_definitions_by_name_, other.field_definitions_by_name_);
    swap(field_definitions_by_facet_name_, other.field_definitions_by_facet_name_);
    swap(field_definitions_by_formatter_name_, other.field_definitions_by_formatter_name_);
    swap(field_definitions_by_model_name_, other.field_definitions_by_model_name_);
}

bool repository::operator==(const repository& rhs) const {
    return all_field_definitions_ == rhs.all_field_definitions_ &&
        field_definitions_by_name_ == rhs.field_definitions_by_name_ &&
        field_definitions_by_facet_name_ == rhs.field_definitions_by_facet_name_ &&
        field_definitions_by_formatter_name_ == rhs.field_definitions_by_formatter_name_ &&
        field_definitions_by_model_name_ == rhs.field_definitions_by_model_name_;
}

repository& repository::operator=(repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::annotations::type>& repository::all_field_definitions() const {
    return all_field_definitions_;
}

std::list<dogen::annotations::type>& repository::all_field_definitions() {
    return all_field_definitions_;
}

void repository::all_field_definitions(const std::list<dogen::annotations::type>& v) {
    all_field_definitions_ = v;
}

void repository::all_field_definitions(const std::list<dogen::annotations::type>&& v) {
    all_field_definitions_ = std::move(v);
}

const std::unordered_map<std::string, dogen::annotations::type>& repository::field_definitions_by_name() const {
    return field_definitions_by_name_;
}

std::unordered_map<std::string, dogen::annotations::type>& repository::field_definitions_by_name() {
    return field_definitions_by_name_;
}

void repository::field_definitions_by_name(const std::unordered_map<std::string, dogen::annotations::type>& v) {
    field_definitions_by_name_ = v;
}

void repository::field_definitions_by_name(const std::unordered_map<std::string, dogen::annotations::type>&& v) {
    field_definitions_by_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::annotations::type> >& repository::field_definitions_by_facet_name() const {
    return field_definitions_by_facet_name_;
}

std::unordered_map<std::string, std::list<dogen::annotations::type> >& repository::field_definitions_by_facet_name() {
    return field_definitions_by_facet_name_;
}

void repository::field_definitions_by_facet_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >& v) {
    field_definitions_by_facet_name_ = v;
}

void repository::field_definitions_by_facet_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >&& v) {
    field_definitions_by_facet_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::annotations::type> >& repository::field_definitions_by_formatter_name() const {
    return field_definitions_by_formatter_name_;
}

std::unordered_map<std::string, std::list<dogen::annotations::type> >& repository::field_definitions_by_formatter_name() {
    return field_definitions_by_formatter_name_;
}

void repository::field_definitions_by_formatter_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >& v) {
    field_definitions_by_formatter_name_ = v;
}

void repository::field_definitions_by_formatter_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >&& v) {
    field_definitions_by_formatter_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::annotations::type> >& repository::field_definitions_by_model_name() const {
    return field_definitions_by_model_name_;
}

std::unordered_map<std::string, std::list<dogen::annotations::type> >& repository::field_definitions_by_model_name() {
    return field_definitions_by_model_name_;
}

void repository::field_definitions_by_model_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >& v) {
    field_definitions_by_model_name_ = v;
}

void repository::field_definitions_by_model_name(const std::unordered_map<std::string, std::list<dogen::annotations::type> >&& v) {
    field_definitions_by_model_name_ = std::move(v);
}

} }
