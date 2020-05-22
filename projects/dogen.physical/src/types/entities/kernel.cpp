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
#include "dogen.physical/types/entities/kernel.hpp"

namespace dogen::physical::entities {

kernel::kernel(
    const std::string& description,
    const dogen::physical::entities::meta_name& meta_name,
    const std::list<dogen::physical::entities::backend>& backends,
    const dogen::physical::entities::meta_name_indices& indexed_names)
    : description_(description),
      meta_name_(meta_name),
      backends_(backends),
      indexed_names_(indexed_names) { }

void kernel::swap(kernel& other) noexcept {
    using std::swap;
    swap(description_, other.description_);
    swap(meta_name_, other.meta_name_);
    swap(backends_, other.backends_);
    swap(indexed_names_, other.indexed_names_);
}

bool kernel::operator==(const kernel& rhs) const {
    return description_ == rhs.description_ &&
        meta_name_ == rhs.meta_name_ &&
        backends_ == rhs.backends_ &&
        indexed_names_ == rhs.indexed_names_;
}

kernel& kernel::operator=(kernel other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& kernel::description() const {
    return description_;
}

std::string& kernel::description() {
    return description_;
}

void kernel::description(const std::string& v) {
    description_ = v;
}

void kernel::description(const std::string&& v) {
    description_ = std::move(v);
}

const dogen::physical::entities::meta_name& kernel::meta_name() const {
    return meta_name_;
}

dogen::physical::entities::meta_name& kernel::meta_name() {
    return meta_name_;
}

void kernel::meta_name(const dogen::physical::entities::meta_name& v) {
    meta_name_ = v;
}

void kernel::meta_name(const dogen::physical::entities::meta_name&& v) {
    meta_name_ = std::move(v);
}

const std::list<dogen::physical::entities::backend>& kernel::backends() const {
    return backends_;
}

std::list<dogen::physical::entities::backend>& kernel::backends() {
    return backends_;
}

void kernel::backends(const std::list<dogen::physical::entities::backend>& v) {
    backends_ = v;
}

void kernel::backends(const std::list<dogen::physical::entities::backend>&& v) {
    backends_ = std::move(v);
}

const dogen::physical::entities::meta_name_indices& kernel::indexed_names() const {
    return indexed_names_;
}

dogen::physical::entities::meta_name_indices& kernel::indexed_names() {
    return indexed_names_;
}

void kernel::indexed_names(const dogen::physical::entities::meta_name_indices& v) {
    indexed_names_ = v;
}

void kernel::indexed_names(const dogen::physical::entities::meta_name_indices&& v) {
    indexed_names_ = std::move(v);
}

}
