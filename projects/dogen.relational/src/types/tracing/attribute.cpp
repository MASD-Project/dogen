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
#include "dogen.relational/types/tracing/attribute.hpp"

namespace dogen::relational::tracing {

attribute::attribute(
    const dogen::relational::tracing::json& json_content,
    const dogen::relational::tracing::attribute_id& id,
    const dogen::relational::tracing::element_id& element_id,
    const std::string& qualified_name,
    const std::string& qualified_meta_name)
    : json_content_(json_content),
      id_(id),
      element_id_(element_id),
      qualified_name_(qualified_name),
      qualified_meta_name_(qualified_meta_name) { }

void attribute::swap(attribute& other) noexcept {
    using std::swap;
    swap(json_content_, other.json_content_);
    swap(id_, other.id_);
    swap(element_id_, other.element_id_);
    swap(qualified_name_, other.qualified_name_);
    swap(qualified_meta_name_, other.qualified_meta_name_);
}

bool attribute::operator==(const attribute& rhs) const {
    return json_content_ == rhs.json_content_ &&
        id_ == rhs.id_ &&
        element_id_ == rhs.element_id_ &&
        qualified_name_ == rhs.qualified_name_ &&
        qualified_meta_name_ == rhs.qualified_meta_name_;
}

attribute& attribute::operator=(attribute other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::relational::tracing::json& attribute::json_content() const {
    return json_content_;
}

dogen::relational::tracing::json& attribute::json_content() {
    return json_content_;
}

void attribute::json_content(const dogen::relational::tracing::json& v) {
    json_content_ = v;
}

void attribute::json_content(const dogen::relational::tracing::json&& v) {
    json_content_ = std::move(v);
}

const dogen::relational::tracing::attribute_id& attribute::id() const {
    return id_;
}

dogen::relational::tracing::attribute_id& attribute::id() {
    return id_;
}

void attribute::id(const dogen::relational::tracing::attribute_id& v) {
    id_ = v;
}

void attribute::id(const dogen::relational::tracing::attribute_id&& v) {
    id_ = std::move(v);
}

const dogen::relational::tracing::element_id& attribute::element_id() const {
    return element_id_;
}

dogen::relational::tracing::element_id& attribute::element_id() {
    return element_id_;
}

void attribute::element_id(const dogen::relational::tracing::element_id& v) {
    element_id_ = v;
}

void attribute::element_id(const dogen::relational::tracing::element_id&& v) {
    element_id_ = std::move(v);
}

const std::string& attribute::qualified_name() const {
    return qualified_name_;
}

std::string& attribute::qualified_name() {
    return qualified_name_;
}

void attribute::qualified_name(const std::string& v) {
    qualified_name_ = v;
}

void attribute::qualified_name(const std::string&& v) {
    qualified_name_ = std::move(v);
}

const std::string& attribute::qualified_meta_name() const {
    return qualified_meta_name_;
}

std::string& attribute::qualified_meta_name() {
    return qualified_meta_name_;
}

void attribute::qualified_meta_name(const std::string& v) {
    qualified_meta_name_ = v;
}

void attribute::qualified_meta_name(const std::string&& v) {
    qualified_meta_name_ = std::move(v);
}

}
