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
#include "dogen/yarn.dia/types/repository.hpp"

namespace dogen {
namespace yarn {
namespace dia {

repository::repository(
    const std::unordered_map<std::string, std::list<std::string> >& child_id_to_parent_ids,
    const std::unordered_map<std::string, dogen::yarn::meta_model::name>& id_to_name,
    const dogen::yarn::meta_model::intermediate_model& model)
    : child_id_to_parent_ids_(child_id_to_parent_ids),
      id_to_name_(id_to_name),
      model_(model) { }

void repository::swap(repository& other) noexcept {
    using std::swap;
    swap(child_id_to_parent_ids_, other.child_id_to_parent_ids_);
    swap(id_to_name_, other.id_to_name_);
    swap(model_, other.model_);
}

bool repository::operator==(const repository& rhs) const {
    return child_id_to_parent_ids_ == rhs.child_id_to_parent_ids_ &&
        id_to_name_ == rhs.id_to_name_ &&
        model_ == rhs.model_;
}

repository& repository::operator=(repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::list<std::string> >& repository::child_id_to_parent_ids() const {
    return child_id_to_parent_ids_;
}

std::unordered_map<std::string, std::list<std::string> >& repository::child_id_to_parent_ids() {
    return child_id_to_parent_ids_;
}

void repository::child_id_to_parent_ids(const std::unordered_map<std::string, std::list<std::string> >& v) {
    child_id_to_parent_ids_ = v;
}

void repository::child_id_to_parent_ids(const std::unordered_map<std::string, std::list<std::string> >&& v) {
    child_id_to_parent_ids_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::meta_model::name>& repository::id_to_name() const {
    return id_to_name_;
}

std::unordered_map<std::string, dogen::yarn::meta_model::name>& repository::id_to_name() {
    return id_to_name_;
}

void repository::id_to_name(const std::unordered_map<std::string, dogen::yarn::meta_model::name>& v) {
    id_to_name_ = v;
}

void repository::id_to_name(const std::unordered_map<std::string, dogen::yarn::meta_model::name>&& v) {
    id_to_name_ = std::move(v);
}

const dogen::yarn::meta_model::intermediate_model& repository::model() const {
    return model_;
}

dogen::yarn::meta_model::intermediate_model& repository::model() {
    return model_;
}

void repository::model(const dogen::yarn::meta_model::intermediate_model& v) {
    model_ = v;
}

void repository::model(const dogen::yarn::meta_model::intermediate_model&& v) {
    model_ = std::move(v);
}

} } }
