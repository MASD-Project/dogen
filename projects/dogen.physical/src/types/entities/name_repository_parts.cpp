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
#include "dogen.physical/types/entities/name_repository_parts.hpp"

namespace dogen::physical::entities {

name_repository_parts::name_repository_parts(
    const std::list<dogen::physical::entities::name>& all,
    const std::unordered_map<std::string, dogen::physical::entities::name_group>& by_meta_name)
    : all_(all),
      by_meta_name_(by_meta_name) { }

void name_repository_parts::swap(name_repository_parts& other) noexcept {
    using std::swap;
    swap(all_, other.all_);
    swap(by_meta_name_, other.by_meta_name_);
}

bool name_repository_parts::operator==(const name_repository_parts& rhs) const {
    return all_ == rhs.all_ &&
        by_meta_name_ == rhs.by_meta_name_;
}

name_repository_parts& name_repository_parts::operator=(name_repository_parts other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::physical::entities::name>& name_repository_parts::all() const {
    return all_;
}

std::list<dogen::physical::entities::name>& name_repository_parts::all() {
    return all_;
}

void name_repository_parts::all(const std::list<dogen::physical::entities::name>& v) {
    all_ = v;
}

void name_repository_parts::all(const std::list<dogen::physical::entities::name>&& v) {
    all_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::name_group>& name_repository_parts::by_meta_name() const {
    return by_meta_name_;
}

std::unordered_map<std::string, dogen::physical::entities::name_group>& name_repository_parts::by_meta_name() {
    return by_meta_name_;
}

void name_repository_parts::by_meta_name(const std::unordered_map<std::string, dogen::physical::entities::name_group>& v) {
    by_meta_name_ = v;
}

void name_repository_parts::by_meta_name(const std::unordered_map<std::string, dogen::physical::entities::name_group>&& v) {
    by_meta_name_ = std::move(v);
}

}
