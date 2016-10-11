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
    const std::unordered_map<std::string, dogen::annotations::scribble_group>& scribble_groups)
    : objects_always_in_heap_(objects_always_in_heap),
      elements_referable_by_attributes_(elements_referable_by_attributes),
      scribble_groups_(scribble_groups) { }

void indices::swap(indices& other) noexcept {
    using std::swap;
    swap(objects_always_in_heap_, other.objects_always_in_heap_);
    swap(elements_referable_by_attributes_, other.elements_referable_by_attributes_);
    swap(scribble_groups_, other.scribble_groups_);
}

bool indices::operator==(const indices& rhs) const {
    return objects_always_in_heap_ == rhs.objects_always_in_heap_ &&
        elements_referable_by_attributes_ == rhs.elements_referable_by_attributes_ &&
        scribble_groups_ == rhs.scribble_groups_;
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

const std::unordered_map<std::string, dogen::annotations::scribble_group>& indices::scribble_groups() const {
    return scribble_groups_;
}

std::unordered_map<std::string, dogen::annotations::scribble_group>& indices::scribble_groups() {
    return scribble_groups_;
}

void indices::scribble_groups(const std::unordered_map<std::string, dogen::annotations::scribble_group>& v) {
    scribble_groups_ = v;
}

void indices::scribble_groups(const std::unordered_map<std::string, dogen::annotations::scribble_group>&& v) {
    scribble_groups_ = std::move(v);
}

} }
