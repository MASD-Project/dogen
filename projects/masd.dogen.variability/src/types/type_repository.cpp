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
#include "masd.dogen.variability/types/type_repository.hpp"

namespace masd::dogen::variability {

type_repository::type_repository(
    const std::list<masd::dogen::variability::type>& all_types,
    const std::unordered_map<std::string, masd::dogen::variability::type>& types_by_name,
    const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_facet_name,
    const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_formatter_name,
    const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& types_by_backend_name,
    const std::unordered_map<std::string, masd::dogen::variability::type>& partially_matchable_types)
    : all_types_(all_types),
      types_by_name_(types_by_name),
      types_by_facet_name_(types_by_facet_name),
      types_by_formatter_name_(types_by_formatter_name),
      types_by_backend_name_(types_by_backend_name),
      partially_matchable_types_(partially_matchable_types) { }

void type_repository::swap(type_repository& other) noexcept {
    using std::swap;
    swap(all_types_, other.all_types_);
    swap(types_by_name_, other.types_by_name_);
    swap(types_by_facet_name_, other.types_by_facet_name_);
    swap(types_by_formatter_name_, other.types_by_formatter_name_);
    swap(types_by_backend_name_, other.types_by_backend_name_);
    swap(partially_matchable_types_, other.partially_matchable_types_);
}

bool type_repository::operator==(const type_repository& rhs) const {
    return all_types_ == rhs.all_types_ &&
        types_by_name_ == rhs.types_by_name_ &&
        types_by_facet_name_ == rhs.types_by_facet_name_ &&
        types_by_formatter_name_ == rhs.types_by_formatter_name_ &&
        types_by_backend_name_ == rhs.types_by_backend_name_ &&
        partially_matchable_types_ == rhs.partially_matchable_types_;
}

type_repository& type_repository::operator=(type_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<masd::dogen::variability::type>& type_repository::all_types() const {
    return all_types_;
}

std::list<masd::dogen::variability::type>& type_repository::all_types() {
    return all_types_;
}

void type_repository::all_types(const std::list<masd::dogen::variability::type>& v) {
    all_types_ = v;
}

void type_repository::all_types(const std::list<masd::dogen::variability::type>&& v) {
    all_types_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::variability::type>& type_repository::types_by_name() const {
    return types_by_name_;
}

std::unordered_map<std::string, masd::dogen::variability::type>& type_repository::types_by_name() {
    return types_by_name_;
}

void type_repository::types_by_name(const std::unordered_map<std::string, masd::dogen::variability::type>& v) {
    types_by_name_ = v;
}

void type_repository::types_by_name(const std::unordered_map<std::string, masd::dogen::variability::type>&& v) {
    types_by_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& type_repository::types_by_facet_name() const {
    return types_by_facet_name_;
}

std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& type_repository::types_by_facet_name() {
    return types_by_facet_name_;
}

void type_repository::types_by_facet_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& v) {
    types_by_facet_name_ = v;
}

void type_repository::types_by_facet_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >&& v) {
    types_by_facet_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& type_repository::types_by_formatter_name() const {
    return types_by_formatter_name_;
}

std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& type_repository::types_by_formatter_name() {
    return types_by_formatter_name_;
}

void type_repository::types_by_formatter_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& v) {
    types_by_formatter_name_ = v;
}

void type_repository::types_by_formatter_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >&& v) {
    types_by_formatter_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& type_repository::types_by_backend_name() const {
    return types_by_backend_name_;
}

std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& type_repository::types_by_backend_name() {
    return types_by_backend_name_;
}

void type_repository::types_by_backend_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >& v) {
    types_by_backend_name_ = v;
}

void type_repository::types_by_backend_name(const std::unordered_map<std::string, std::list<masd::dogen::variability::type> >&& v) {
    types_by_backend_name_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::variability::type>& type_repository::partially_matchable_types() const {
    return partially_matchable_types_;
}

std::unordered_map<std::string, masd::dogen::variability::type>& type_repository::partially_matchable_types() {
    return partially_matchable_types_;
}

void type_repository::partially_matchable_types(const std::unordered_map<std::string, masd::dogen::variability::type>& v) {
    partially_matchable_types_ = v;
}

void type_repository::partially_matchable_types(const std::unordered_map<std::string, masd::dogen::variability::type>&& v) {
    partially_matchable_types_ = std::move(v);
}

}
