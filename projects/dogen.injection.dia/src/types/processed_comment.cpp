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
#include "dogen.injection.dia/types/processed_comment.hpp"

namespace dogen::injection::dia {

processed_comment::processed_comment()
    : applicable_to_parent_object_(static_cast<bool>(0)) { }

processed_comment::processed_comment(
    const std::string& documentation,
    const std::list<dogen::identification::entities::tagged_value>& tagged_values,
    const bool applicable_to_parent_object,
    const std::string& original_content)
    : documentation_(documentation),
      tagged_values_(tagged_values),
      applicable_to_parent_object_(applicable_to_parent_object),
      original_content_(original_content) { }

void processed_comment::swap(processed_comment& other) noexcept {
    using std::swap;
    swap(documentation_, other.documentation_);
    swap(tagged_values_, other.tagged_values_);
    swap(applicable_to_parent_object_, other.applicable_to_parent_object_);
    swap(original_content_, other.original_content_);
}

bool processed_comment::operator==(const processed_comment& rhs) const {
    return documentation_ == rhs.documentation_ &&
        tagged_values_ == rhs.tagged_values_ &&
        applicable_to_parent_object_ == rhs.applicable_to_parent_object_ &&
        original_content_ == rhs.original_content_;
}

processed_comment& processed_comment::operator=(processed_comment other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& processed_comment::documentation() const {
    return documentation_;
}

std::string& processed_comment::documentation() {
    return documentation_;
}

void processed_comment::documentation(const std::string& v) {
    documentation_ = v;
}

void processed_comment::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::list<dogen::identification::entities::tagged_value>& processed_comment::tagged_values() const {
    return tagged_values_;
}

std::list<dogen::identification::entities::tagged_value>& processed_comment::tagged_values() {
    return tagged_values_;
}

void processed_comment::tagged_values(const std::list<dogen::identification::entities::tagged_value>& v) {
    tagged_values_ = v;
}

void processed_comment::tagged_values(const std::list<dogen::identification::entities::tagged_value>&& v) {
    tagged_values_ = std::move(v);
}

bool processed_comment::applicable_to_parent_object() const {
    return applicable_to_parent_object_;
}

void processed_comment::applicable_to_parent_object(const bool v) {
    applicable_to_parent_object_ = v;
}

const std::string& processed_comment::original_content() const {
    return original_content_;
}

std::string& processed_comment::original_content() {
    return original_content_;
}

void processed_comment::original_content(const std::string& v) {
    original_content_ = v;
}

void processed_comment::original_content(const std::string&& v) {
    original_content_ = std::move(v);
}

}
