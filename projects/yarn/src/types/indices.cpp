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
#include "dogen/yarn/types/indices.hpp"

namespace dogen {
namespace yarn {

indices::indices(
    const std::unordered_set<std::string>& objects_always_in_heap,
    const std::unordered_set<std::string>& elements_referable_by_attributes,
    const std::unordered_map<std::string, dogen::annotations::raw_aggregate>& raw_aggregates)
    : objects_always_in_heap_(objects_always_in_heap),
      elements_referable_by_attributes_(elements_referable_by_attributes),
      raw_aggregates_(raw_aggregates) { }

void indices::swap(indices& other) noexcept {
    using std::swap;
    swap(objects_always_in_heap_, other.objects_always_in_heap_);
    swap(elements_referable_by_attributes_, other.elements_referable_by_attributes_);
    swap(raw_aggregates_, other.raw_aggregates_);
}

bool indices::operator==(const indices& rhs) const {
    return objects_always_in_heap_ == rhs.objects_always_in_heap_ &&
        elements_referable_by_attributes_ == rhs.elements_referable_by_attributes_ &&
        raw_aggregates_ == rhs.raw_aggregates_;
}

indices& indices::operator=(indices other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& indices::objects_always_in_heap() const {
    return objects_always_in_heap_;
}

std::unordered_set<std::string>& indices::objects_always_in_heap() {
    return objects_always_in_heap_;
}

void indices::objects_always_in_heap(const std::unordered_set<std::string>& v) {
    objects_always_in_heap_ = v;
}

void indices::objects_always_in_heap(const std::unordered_set<std::string>&& v) {
    objects_always_in_heap_ = std::move(v);
}

const std::unordered_set<std::string>& indices::elements_referable_by_attributes() const {
    return elements_referable_by_attributes_;
}

std::unordered_set<std::string>& indices::elements_referable_by_attributes() {
    return elements_referable_by_attributes_;
}

void indices::elements_referable_by_attributes(const std::unordered_set<std::string>& v) {
    elements_referable_by_attributes_ = v;
}

void indices::elements_referable_by_attributes(const std::unordered_set<std::string>&& v) {
    elements_referable_by_attributes_ = std::move(v);
}

const std::unordered_map<std::string, dogen::annotations::raw_aggregate>& indices::raw_aggregates() const {
    return raw_aggregates_;
}

std::unordered_map<std::string, dogen::annotations::raw_aggregate>& indices::raw_aggregates() {
    return raw_aggregates_;
}

void indices::raw_aggregates(const std::unordered_map<std::string, dogen::annotations::raw_aggregate>& v) {
    raw_aggregates_ = v;
}

void indices::raw_aggregates(const std::unordered_map<std::string, dogen::annotations::raw_aggregate>&& v) {
    raw_aggregates_ = std::move(v);
}

} }
