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
#include "dogen.relational/types/tracing/model.hpp"

namespace dogen::relational::tracing {

model::model()
    : type_(static_cast<dogen::relational::tracing::model_type>(0)) { }

model::model(
    const dogen::relational::tracing::json& json_content,
    const dogen::relational::tracing::xml& xml_content,
    const dogen::relational::tracing::model_id& id,
    const dogen::relational::tracing::model_set_id& model_set_id,
    const std::string& qualified_name,
    const std::string& qualified_meta_name,
    const dogen::relational::tracing::model_type type,
    const std::string& source_file)
    : json_content_(json_content),
      xml_content_(xml_content),
      id_(id),
      model_set_id_(model_set_id),
      qualified_name_(qualified_name),
      qualified_meta_name_(qualified_meta_name),
      type_(type),
      source_file_(source_file) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(json_content_, other.json_content_);
    swap(xml_content_, other.xml_content_);
    swap(id_, other.id_);
    swap(model_set_id_, other.model_set_id_);
    swap(qualified_name_, other.qualified_name_);
    swap(qualified_meta_name_, other.qualified_meta_name_);
    swap(type_, other.type_);
    swap(source_file_, other.source_file_);
}

bool model::operator==(const model& rhs) const {
    return json_content_ == rhs.json_content_ &&
        xml_content_ == rhs.xml_content_ &&
        id_ == rhs.id_ &&
        model_set_id_ == rhs.model_set_id_ &&
        qualified_name_ == rhs.qualified_name_ &&
        qualified_meta_name_ == rhs.qualified_meta_name_ &&
        type_ == rhs.type_ &&
        source_file_ == rhs.source_file_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::relational::tracing::json& model::json_content() const {
    return json_content_;
}

dogen::relational::tracing::json& model::json_content() {
    return json_content_;
}

void model::json_content(const dogen::relational::tracing::json& v) {
    json_content_ = v;
}

void model::json_content(const dogen::relational::tracing::json&& v) {
    json_content_ = std::move(v);
}

const dogen::relational::tracing::xml& model::xml_content() const {
    return xml_content_;
}

dogen::relational::tracing::xml& model::xml_content() {
    return xml_content_;
}

void model::xml_content(const dogen::relational::tracing::xml& v) {
    xml_content_ = v;
}

void model::xml_content(const dogen::relational::tracing::xml&& v) {
    xml_content_ = std::move(v);
}

const dogen::relational::tracing::model_id& model::id() const {
    return id_;
}

dogen::relational::tracing::model_id& model::id() {
    return id_;
}

void model::id(const dogen::relational::tracing::model_id& v) {
    id_ = v;
}

void model::id(const dogen::relational::tracing::model_id&& v) {
    id_ = std::move(v);
}

const dogen::relational::tracing::model_set_id& model::model_set_id() const {
    return model_set_id_;
}

dogen::relational::tracing::model_set_id& model::model_set_id() {
    return model_set_id_;
}

void model::model_set_id(const dogen::relational::tracing::model_set_id& v) {
    model_set_id_ = v;
}

void model::model_set_id(const dogen::relational::tracing::model_set_id&& v) {
    model_set_id_ = std::move(v);
}

const std::string& model::qualified_name() const {
    return qualified_name_;
}

std::string& model::qualified_name() {
    return qualified_name_;
}

void model::qualified_name(const std::string& v) {
    qualified_name_ = v;
}

void model::qualified_name(const std::string&& v) {
    qualified_name_ = std::move(v);
}

const std::string& model::qualified_meta_name() const {
    return qualified_meta_name_;
}

std::string& model::qualified_meta_name() {
    return qualified_meta_name_;
}

void model::qualified_meta_name(const std::string& v) {
    qualified_meta_name_ = v;
}

void model::qualified_meta_name(const std::string&& v) {
    qualified_meta_name_ = std::move(v);
}

dogen::relational::tracing::model_type model::type() const {
    return type_;
}

void model::type(const dogen::relational::tracing::model_type v) {
    type_ = v;
}

const std::string& model::source_file() const {
    return source_file_;
}

std::string& model::source_file() {
    return source_file_;
}

void model::source_file(const std::string& v) {
    source_file_ = v;
}

void model::source_file(const std::string&& v) {
    source_file_ = std::move(v);
}

}
