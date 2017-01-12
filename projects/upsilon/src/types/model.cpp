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
    const dogen::upsilon::schema& target,
    const std::vector<dogen::upsilon::schema>& refs,
    const std::vector<dogen::upsilon::type_information>& type_information,
    const dogen::upsilon::config& config)
    : target_(target),
      refs_(refs),
      type_information_(type_information),
      config_(config) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(target_, other.target_);
    swap(refs_, other.refs_);
    swap(type_information_, other.type_information_);
    swap(config_, other.config_);
}

bool model::operator==(const model& rhs) const {
    return target_ == rhs.target_ &&
        refs_ == rhs.refs_ &&
        type_information_ == rhs.type_information_ &&
        config_ == rhs.config_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::upsilon::schema& model::target() const {
    return target_;
}

dogen::upsilon::schema& model::target() {
    return target_;
}

void model::target(const dogen::upsilon::schema& v) {
    target_ = v;
}

void model::target(const dogen::upsilon::schema&& v) {
    target_ = std::move(v);
}

const std::vector<dogen::upsilon::schema>& model::refs() const {
    return refs_;
}

std::vector<dogen::upsilon::schema>& model::refs() {
    return refs_;
}

void model::refs(const std::vector<dogen::upsilon::schema>& v) {
    refs_ = v;
}

void model::refs(const std::vector<dogen::upsilon::schema>&& v) {
    refs_ = std::move(v);
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
