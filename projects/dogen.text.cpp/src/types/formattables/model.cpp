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
#include "dogen.text.cpp/types/formattables/model.hpp"

namespace dogen::text::cpp::formattables {

model::model(
    const dogen::identification::entities::logical_name& name,
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& formattables)
    : name_(name),
      formattables_(formattables) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(formattables_, other.formattables_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        formattables_ == rhs.formattables_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::logical_name& model::name() const {
    return name_;
}

dogen::identification::entities::logical_name& model::name() {
    return name_;
}

void model::name(const dogen::identification::entities::logical_name& v) {
    name_ = v;
}

void model::name(const dogen::identification::entities::logical_name&& v) {
    name_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& model::formattables() const {
    return formattables_;
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& model::formattables() {
    return formattables_;
}

void model::formattables(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& v) {
    formattables_ = v;
}

void model::formattables(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>&& v) {
    formattables_ = std::move(v);
}

}
