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
#include "masd.dogen.injection/types/meta_model/model_set.hpp"

namespace masd::dogen::injection::meta_model {

model_set::model_set(
    const masd::dogen::injection::meta_model::model& target,
    const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& direct_references,
    const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& transitive_references,
    const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& system_models)
    : target_(target),
      direct_references_(direct_references),
      transitive_references_(transitive_references),
      system_models_(system_models) { }

void model_set::swap(model_set& other) noexcept {
    using std::swap;
    swap(target_, other.target_);
    swap(direct_references_, other.direct_references_);
    swap(transitive_references_, other.transitive_references_);
    swap(system_models_, other.system_models_);
}

bool model_set::operator==(const model_set& rhs) const {
    return target_ == rhs.target_ &&
        direct_references_ == rhs.direct_references_ &&
        transitive_references_ == rhs.transitive_references_ &&
        system_models_ == rhs.system_models_;
}

model_set& model_set::operator=(model_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::injection::meta_model::model& model_set::target() const {
    return target_;
}

masd::dogen::injection::meta_model::model& model_set::target() {
    return target_;
}

void model_set::target(const masd::dogen::injection::meta_model::model& v) {
    target_ = v;
}

void model_set::target(const masd::dogen::injection::meta_model::model&& v) {
    target_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& model_set::direct_references() const {
    return direct_references_;
}

std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& model_set::direct_references() {
    return direct_references_;
}

void model_set::direct_references(const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& v) {
    direct_references_ = v;
}

void model_set::direct_references(const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>&& v) {
    direct_references_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& model_set::transitive_references() const {
    return transitive_references_;
}

std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& model_set::transitive_references() {
    return transitive_references_;
}

void model_set::transitive_references(const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& v) {
    transitive_references_ = v;
}

void model_set::transitive_references(const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>&& v) {
    transitive_references_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& model_set::system_models() const {
    return system_models_;
}

std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& model_set::system_models() {
    return system_models_;
}

void model_set::system_models(const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>& v) {
    system_models_ = v;
}

void model_set::system_models(const std::unordered_map<std::string, masd::dogen::injection::meta_model::model>&& v) {
    system_models_ = std::move(v);
}

}
