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
#include "dogen.logical/types/meta_model/model_set.hpp"

namespace dogen::logical::meta_model {

model_set::model_set(
    const dogen::logical::meta_model::model& target,
    const std::list<dogen::logical::meta_model::model>& references,
    const std::unordered_map<std::string, std::string>& fixed_mappings)
    : target_(target),
      references_(references),
      fixed_mappings_(fixed_mappings) { }

void model_set::swap(model_set& other) noexcept {
    using std::swap;
    swap(target_, other.target_);
    swap(references_, other.references_);
    swap(fixed_mappings_, other.fixed_mappings_);
}

bool model_set::operator==(const model_set& rhs) const {
    return target_ == rhs.target_ &&
        references_ == rhs.references_ &&
        fixed_mappings_ == rhs.fixed_mappings_;
}

model_set& model_set::operator=(model_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::logical::meta_model::model& model_set::target() const {
    return target_;
}

dogen::logical::meta_model::model& model_set::target() {
    return target_;
}

void model_set::target(const dogen::logical::meta_model::model& v) {
    target_ = v;
}

void model_set::target(const dogen::logical::meta_model::model&& v) {
    target_ = std::move(v);
}

const std::list<dogen::logical::meta_model::model>& model_set::references() const {
    return references_;
}

std::list<dogen::logical::meta_model::model>& model_set::references() {
    return references_;
}

void model_set::references(const std::list<dogen::logical::meta_model::model>& v) {
    references_ = v;
}

void model_set::references(const std::list<dogen::logical::meta_model::model>&& v) {
    references_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& model_set::fixed_mappings() const {
    return fixed_mappings_;
}

std::unordered_map<std::string, std::string>& model_set::fixed_mappings() {
    return fixed_mappings_;
}

void model_set::fixed_mappings(const std::unordered_map<std::string, std::string>& v) {
    fixed_mappings_ = v;
}

void model_set::fixed_mappings(const std::unordered_map<std::string, std::string>&& v) {
    fixed_mappings_ = std::move(v);
}

}
