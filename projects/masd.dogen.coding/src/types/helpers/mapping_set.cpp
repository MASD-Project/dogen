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
#include "masd.dogen.coding/types/helpers/mapping_set.hpp"

namespace masd::dogen::coding::helpers {

mapping_set::mapping_set(
    const std::string& name,
    const std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_map<std::string, masd::dogen::coding::meta_model::name> >& by_language_agnostic_id,
    const std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_set<std::string> >& erasures_by_language)
    : name_(name),
      by_language_agnostic_id_(by_language_agnostic_id),
      erasures_by_language_(erasures_by_language) { }

void mapping_set::swap(mapping_set& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(by_language_agnostic_id_, other.by_language_agnostic_id_);
    swap(erasures_by_language_, other.erasures_by_language_);
}

bool mapping_set::operator==(const mapping_set& rhs) const {
    return name_ == rhs.name_ &&
        by_language_agnostic_id_ == rhs.by_language_agnostic_id_ &&
        erasures_by_language_ == rhs.erasures_by_language_;
}

mapping_set& mapping_set::operator=(mapping_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& mapping_set::name() const {
    return name_;
}

std::string& mapping_set::name() {
    return name_;
}

void mapping_set::name(const std::string& v) {
    name_ = v;
}

void mapping_set::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_map<std::string, masd::dogen::coding::meta_model::name> >& mapping_set::by_language_agnostic_id() const {
    return by_language_agnostic_id_;
}

std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_map<std::string, masd::dogen::coding::meta_model::name> >& mapping_set::by_language_agnostic_id() {
    return by_language_agnostic_id_;
}

void mapping_set::by_language_agnostic_id(const std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_map<std::string, masd::dogen::coding::meta_model::name> >& v) {
    by_language_agnostic_id_ = v;
}

void mapping_set::by_language_agnostic_id(const std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_map<std::string, masd::dogen::coding::meta_model::name> >&& v) {
    by_language_agnostic_id_ = std::move(v);
}

const std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_set<std::string> >& mapping_set::erasures_by_language() const {
    return erasures_by_language_;
}

std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_set<std::string> >& mapping_set::erasures_by_language() {
    return erasures_by_language_;
}

void mapping_set::erasures_by_language(const std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_set<std::string> >& v) {
    erasures_by_language_ = v;
}

void mapping_set::erasures_by_language(const std::unordered_map<masd::dogen::coding::meta_model::languages, std::unordered_set<std::string> >&& v) {
    erasures_by_language_ = std::move(v);
}

}
