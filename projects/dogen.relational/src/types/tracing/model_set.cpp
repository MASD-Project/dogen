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
#include "dogen.relational/types/tracing/model_set.hpp"

namespace dogen::relational::tracing {

model_set::model_set(
    const dogen::relational::tracing::model_set_id& id,
    const std::string& qualified_name)
    : id_(id),
      qualified_name_(qualified_name) { }

void model_set::swap(model_set& other) noexcept {
    using std::swap;
    swap(id_, other.id_);
    swap(qualified_name_, other.qualified_name_);
}

bool model_set::operator==(const model_set& rhs) const {
    return id_ == rhs.id_ &&
        qualified_name_ == rhs.qualified_name_;
}

model_set& model_set::operator=(model_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::relational::tracing::model_set_id& model_set::id() const {
    return id_;
}

dogen::relational::tracing::model_set_id& model_set::id() {
    return id_;
}

void model_set::id(const dogen::relational::tracing::model_set_id& v) {
    id_ = v;
}

void model_set::id(const dogen::relational::tracing::model_set_id&& v) {
    id_ = std::move(v);
}

const std::string& model_set::qualified_name() const {
    return qualified_name_;
}

std::string& model_set::qualified_name() {
    return qualified_name_;
}

void model_set::qualified_name(const std::string& v) {
    qualified_name_ = v;
}

void model_set::qualified_name(const std::string&& v) {
    qualified_name_ = std::move(v);
}

}
