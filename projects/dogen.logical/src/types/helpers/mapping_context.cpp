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
#include "dogen.logical/types/helpers/mapping_context.hpp"

namespace dogen::logical::helpers {

mapping_context::mapping_context(
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& translations,
    const std::unordered_set<dogen::identification::entities::logical_id>& erasures,
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& injections)
    : translations_(translations),
      erasures_(erasures),
      injections_(injections) { }

void mapping_context::swap(mapping_context& other) noexcept {
    using std::swap;
    swap(translations_, other.translations_);
    swap(erasures_, other.erasures_);
    swap(injections_, other.injections_);
}

bool mapping_context::operator==(const mapping_context& rhs) const {
    return translations_ == rhs.translations_ &&
        erasures_ == rhs.erasures_ &&
        injections_ == rhs.injections_;
}

mapping_context& mapping_context::operator=(mapping_context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& mapping_context::translations() const {
    return translations_;
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& mapping_context::translations() {
    return translations_;
}

void mapping_context::translations(const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& v) {
    translations_ = v;
}

void mapping_context::translations(const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>&& v) {
    translations_ = std::move(v);
}

const std::unordered_set<dogen::identification::entities::logical_id>& mapping_context::erasures() const {
    return erasures_;
}

std::unordered_set<dogen::identification::entities::logical_id>& mapping_context::erasures() {
    return erasures_;
}

void mapping_context::erasures(const std::unordered_set<dogen::identification::entities::logical_id>& v) {
    erasures_ = v;
}

void mapping_context::erasures(const std::unordered_set<dogen::identification::entities::logical_id>&& v) {
    erasures_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& mapping_context::injections() const {
    return injections_;
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& mapping_context::injections() {
    return injections_;
}

void mapping_context::injections(const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>& v) {
    injections_ = v;
}

void mapping_context::injections(const std::unordered_map<dogen::identification::entities::logical_id, dogen::identification::entities::logical_name>&& v) {
    injections_ = std::move(v);
}

}
