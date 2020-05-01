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
#include "dogen.logical/types/entities/output_model_set.hpp"

namespace dogen::logical::entities {

output_model_set::output_model_set(
    const dogen::logical::entities::name& name,
    const std::list<dogen::logical::entities::model>& models)
    : name_(name),
      models_(models) { }

void output_model_set::swap(output_model_set& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(models_, other.models_);
}

bool output_model_set::operator==(const output_model_set& rhs) const {
    return name_ == rhs.name_ &&
        models_ == rhs.models_;
}

output_model_set& output_model_set::operator=(output_model_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::logical::entities::name& output_model_set::name() const {
    return name_;
}

dogen::logical::entities::name& output_model_set::name() {
    return name_;
}

void output_model_set::name(const dogen::logical::entities::name& v) {
    name_ = v;
}

void output_model_set::name(const dogen::logical::entities::name&& v) {
    name_ = std::move(v);
}

const std::list<dogen::logical::entities::model>& output_model_set::models() const {
    return models_;
}

std::list<dogen::logical::entities::model>& output_model_set::models() {
    return models_;
}

void output_model_set::models(const std::list<dogen::logical::entities::model>& v) {
    models_ = v;
}

void output_model_set::models(const std::list<dogen::logical::entities::model>&& v) {
    models_ = std::move(v);
}

}
