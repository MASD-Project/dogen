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
#include "dogen.codec/types/entities/comment.hpp"

namespace dogen::codec::entities {

comment::comment()
    : applies_to_container_(static_cast<bool>(0)) { }

comment::comment(
    const std::list<dogen::identification::entities::tagged_value>& tagged_values,
    const bool applies_to_container,
    const std::string& original_content,
    const std::string& documentation)
    : tagged_values_(tagged_values),
      applies_to_container_(applies_to_container),
      original_content_(original_content),
      documentation_(documentation) { }

void comment::swap(comment& other) noexcept {
    using std::swap;
    swap(tagged_values_, other.tagged_values_);
    swap(applies_to_container_, other.applies_to_container_);
    swap(original_content_, other.original_content_);
    swap(documentation_, other.documentation_);
}

bool comment::operator==(const comment& rhs) const {
    return tagged_values_ == rhs.tagged_values_ &&
        applies_to_container_ == rhs.applies_to_container_ &&
        original_content_ == rhs.original_content_ &&
        documentation_ == rhs.documentation_;
}

comment& comment::operator=(comment other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::identification::entities::tagged_value>& comment::tagged_values() const {
    return tagged_values_;
}

std::list<dogen::identification::entities::tagged_value>& comment::tagged_values() {
    return tagged_values_;
}

void comment::tagged_values(const std::list<dogen::identification::entities::tagged_value>& v) {
    tagged_values_ = v;
}

void comment::tagged_values(const std::list<dogen::identification::entities::tagged_value>&& v) {
    tagged_values_ = std::move(v);
}

bool comment::applies_to_container() const {
    return applies_to_container_;
}

void comment::applies_to_container(const bool v) {
    applies_to_container_ = v;
}

const std::string& comment::original_content() const {
    return original_content_;
}

std::string& comment::original_content() {
    return original_content_;
}

void comment::original_content(const std::string& v) {
    original_content_ = v;
}

void comment::original_content(const std::string&& v) {
    original_content_ = std::move(v);
}

const std::string& comment::documentation() const {
    return documentation_;
}

std::string& comment::documentation() {
    return documentation_;
}

void comment::documentation(const std::string& v) {
    documentation_ = v;
}

void comment::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

}
