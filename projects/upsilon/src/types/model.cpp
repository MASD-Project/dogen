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
#include "dogen/upsilon/types/model.hpp"

namespace dogen {
namespace upsilon {

model::model(
    const std::unordered_map<std::string, dogen::upsilon::schema>& schemas,
    const std::vector<dogen::upsilon::type_information>& type_information,
    const dogen::upsilon::config& config)
    : schemas_(schemas),
      type_information_(type_information),
      config_(config) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(schemas_, other.schemas_);
    swap(type_information_, other.type_information_);
    swap(config_, other.config_);
}

bool model::operator==(const model& rhs) const {
    return schemas_ == rhs.schemas_ &&
        type_information_ == rhs.type_information_ &&
        config_ == rhs.config_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::upsilon::schema>& model::schemas() const {
    return schemas_;
}

std::unordered_map<std::string, dogen::upsilon::schema>& model::schemas() {
    return schemas_;
}

void model::schemas(const std::unordered_map<std::string, dogen::upsilon::schema>& v) {
    schemas_ = v;
}

void model::schemas(const std::unordered_map<std::string, dogen::upsilon::schema>&& v) {
    schemas_ = std::move(v);
}

const std::vector<dogen::upsilon::type_information>& model::type_information() const {
    return type_information_;
}

std::vector<dogen::upsilon::type_information>& model::type_information() {
    return type_information_;
}

void model::type_information(const std::vector<dogen::upsilon::type_information>& v) {
    type_information_ = v;
}

void model::type_information(const std::vector<dogen::upsilon::type_information>&& v) {
    type_information_ = std::move(v);
}

const dogen::upsilon::config& model::config() const {
    return config_;
}

dogen::upsilon::config& model::config() {
    return config_;
}

void model::config(const dogen::upsilon::config& v) {
    config_ = v;
}

void model::config(const dogen::upsilon::config&& v) {
    config_ = std::move(v);
}

} }
