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
#include "dogen/yarn/types/mapping_repository.hpp"

namespace dogen {
namespace yarn {

mapping_repository::mapping_repository(
    const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_upsilon_id,
    const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& by_language_agnostic_id)
    : by_upsilon_id_(by_upsilon_id),
      by_language_agnostic_id_(by_language_agnostic_id) { }

void mapping_repository::swap(mapping_repository& other) noexcept {
    using std::swap;
    swap(by_upsilon_id_, other.by_upsilon_id_);
    swap(by_language_agnostic_id_, other.by_language_agnostic_id_);
}

bool mapping_repository::operator==(const mapping_repository& rhs) const {
    return by_upsilon_id_ == rhs.by_upsilon_id_ &&
        by_language_agnostic_id_ == rhs.by_language_agnostic_id_;
}

mapping_repository& mapping_repository::operator=(mapping_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& mapping_repository::by_upsilon_id() const {
    return by_upsilon_id_;
}

std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& mapping_repository::by_upsilon_id() {
    return by_upsilon_id_;
}

void mapping_repository::by_upsilon_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& v) {
    by_upsilon_id_ = v;
}

void mapping_repository::by_upsilon_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >&& v) {
    by_upsilon_id_ = std::move(v);
}

const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& mapping_repository::by_language_agnostic_id() const {
    return by_language_agnostic_id_;
}

std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& mapping_repository::by_language_agnostic_id() {
    return by_language_agnostic_id_;
}

void mapping_repository::by_language_agnostic_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >& v) {
    by_language_agnostic_id_ = v;
}

void mapping_repository::by_language_agnostic_id(const std::unordered_map<dogen::yarn::languages, std::unordered_map<std::string, dogen::yarn::name> >&& v) {
    by_language_agnostic_id_ = std::move(v);
}

} }
