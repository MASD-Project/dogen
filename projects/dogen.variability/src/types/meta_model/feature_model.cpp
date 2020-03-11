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
#include "dogen.variability/types/meta_model/feature_model.hpp"

namespace dogen::variability::meta_model {

feature_model::feature_model(
    const std::list<dogen::variability::meta_model::feature>& all,
    const std::unordered_map<std::string, dogen::variability::meta_model::feature>& by_name,
    const std::unordered_map<std::string, dogen::variability::meta_model::feature>& partially_matchable)
    : all_(all),
      by_name_(by_name),
      partially_matchable_(partially_matchable) { }

void feature_model::swap(feature_model& other) noexcept {
    using std::swap;
    swap(all_, other.all_);
    swap(by_name_, other.by_name_);
    swap(partially_matchable_, other.partially_matchable_);
}

bool feature_model::operator==(const feature_model& rhs) const {
    return all_ == rhs.all_ &&
        by_name_ == rhs.by_name_ &&
        partially_matchable_ == rhs.partially_matchable_;
}

feature_model& feature_model::operator=(feature_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::variability::meta_model::feature>& feature_model::all() const {
    return all_;
}

std::list<dogen::variability::meta_model::feature>& feature_model::all() {
    return all_;
}

void feature_model::all(const std::list<dogen::variability::meta_model::feature>& v) {
    all_ = v;
}

void feature_model::all(const std::list<dogen::variability::meta_model::feature>&& v) {
    all_ = std::move(v);
}

const std::unordered_map<std::string, dogen::variability::meta_model::feature>& feature_model::by_name() const {
    return by_name_;
}

std::unordered_map<std::string, dogen::variability::meta_model::feature>& feature_model::by_name() {
    return by_name_;
}

void feature_model::by_name(const std::unordered_map<std::string, dogen::variability::meta_model::feature>& v) {
    by_name_ = v;
}

void feature_model::by_name(const std::unordered_map<std::string, dogen::variability::meta_model::feature>&& v) {
    by_name_ = std::move(v);
}

const std::unordered_map<std::string, dogen::variability::meta_model::feature>& feature_model::partially_matchable() const {
    return partially_matchable_;
}

std::unordered_map<std::string, dogen::variability::meta_model::feature>& feature_model::partially_matchable() {
    return partially_matchable_;
}

void feature_model::partially_matchable(const std::unordered_map<std::string, dogen::variability::meta_model::feature>& v) {
    partially_matchable_ = v;
}

void feature_model::partially_matchable(const std::unordered_map<std::string, dogen::variability::meta_model::feature>&& v) {
    partially_matchable_ = std::move(v);
}

}
