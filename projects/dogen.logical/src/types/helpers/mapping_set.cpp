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
#include "dogen.logical/types/helpers/mapping_set.hpp"

namespace dogen::logical::helpers {

mapping_set::mapping_set(
    const std::string& name,
    const std::unordered_map<dogen::logical::entities::technical_space, std::unordered_map<std::string, dogen::logical::entities::name> >& by_agnostic_id,
    const std::unordered_map<dogen::logical::entities::technical_space, std::unordered_set<std::string> >& erasures_by_technical_space)
    : name_(name),
      by_agnostic_id_(by_agnostic_id),
      erasures_by_technical_space_(erasures_by_technical_space) { }

void mapping_set::swap(mapping_set& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(by_agnostic_id_, other.by_agnostic_id_);
    swap(erasures_by_technical_space_, other.erasures_by_technical_space_);
}

bool mapping_set::operator==(const mapping_set& rhs) const {
    return name_ == rhs.name_ &&
        by_agnostic_id_ == rhs.by_agnostic_id_ &&
        erasures_by_technical_space_ == rhs.erasures_by_technical_space_;
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

const std::unordered_map<dogen::logical::entities::technical_space, std::unordered_map<std::string, dogen::logical::entities::name> >& mapping_set::by_agnostic_id() const {
    return by_agnostic_id_;
}

std::unordered_map<dogen::logical::entities::technical_space, std::unordered_map<std::string, dogen::logical::entities::name> >& mapping_set::by_agnostic_id() {
    return by_agnostic_id_;
}

void mapping_set::by_agnostic_id(const std::unordered_map<dogen::logical::entities::technical_space, std::unordered_map<std::string, dogen::logical::entities::name> >& v) {
    by_agnostic_id_ = v;
}

void mapping_set::by_agnostic_id(const std::unordered_map<dogen::logical::entities::technical_space, std::unordered_map<std::string, dogen::logical::entities::name> >&& v) {
    by_agnostic_id_ = std::move(v);
}

const std::unordered_map<dogen::logical::entities::technical_space, std::unordered_set<std::string> >& mapping_set::erasures_by_technical_space() const {
    return erasures_by_technical_space_;
}

std::unordered_map<dogen::logical::entities::technical_space, std::unordered_set<std::string> >& mapping_set::erasures_by_technical_space() {
    return erasures_by_technical_space_;
}

void mapping_set::erasures_by_technical_space(const std::unordered_map<dogen::logical::entities::technical_space, std::unordered_set<std::string> >& v) {
    erasures_by_technical_space_ = v;
}

void mapping_set::erasures_by_technical_space(const std::unordered_map<dogen::logical::entities::technical_space, std::unordered_set<std::string> >&& v) {
    erasures_by_technical_space_ = std::move(v);
}

}
