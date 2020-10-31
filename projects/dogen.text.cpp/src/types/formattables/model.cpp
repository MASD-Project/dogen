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
#include "dogen.text.cpp/types/formattables/model.hpp"

namespace dogen::text::cpp::formattables {

model::model()
    : cpp_standard_(static_cast<dogen::text::cpp::formattables::cpp_standards>(0)) { }

model::model(
    const dogen::identification::entities::logical_name& name,
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& streaming_properties,
    const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& formattables,
    const dogen::text::cpp::formattables::cpp_standards cpp_standard,
    const std::list<std::string>& odb_databases,
    const std::string& odb_sql_name_case)
    : name_(name),
      streaming_properties_(streaming_properties),
      formattables_(formattables),
      cpp_standard_(cpp_standard),
      odb_databases_(odb_databases),
      odb_sql_name_case_(odb_sql_name_case) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(streaming_properties_, other.streaming_properties_);
    swap(formattables_, other.formattables_);
    swap(cpp_standard_, other.cpp_standard_);
    swap(odb_databases_, other.odb_databases_);
    swap(odb_sql_name_case_, other.odb_sql_name_case_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        streaming_properties_ == rhs.streaming_properties_ &&
        formattables_ == rhs.formattables_ &&
        cpp_standard_ == rhs.cpp_standard_ &&
        odb_databases_ == rhs.odb_databases_ &&
        odb_sql_name_case_ == rhs.odb_sql_name_case_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::logical_name& model::name() const {
    return name_;
}

dogen::identification::entities::logical_name& model::name() {
    return name_;
}

void model::name(const dogen::identification::entities::logical_name& v) {
    name_ = v;
}

void model::name(const dogen::identification::entities::logical_name&& v) {
    name_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& model::streaming_properties() const {
    return streaming_properties_;
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& model::streaming_properties() {
    return streaming_properties_;
}

void model::streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& v) {
    streaming_properties_ = v;
}

void model::streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>&& v) {
    streaming_properties_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& model::formattables() const {
    return formattables_;
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& model::formattables() {
    return formattables_;
}

void model::formattables(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& v) {
    formattables_ = v;
}

void model::formattables(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>&& v) {
    formattables_ = std::move(v);
}

dogen::text::cpp::formattables::cpp_standards model::cpp_standard() const {
    return cpp_standard_;
}

void model::cpp_standard(const dogen::text::cpp::formattables::cpp_standards v) {
    cpp_standard_ = v;
}

const std::list<std::string>& model::odb_databases() const {
    return odb_databases_;
}

std::list<std::string>& model::odb_databases() {
    return odb_databases_;
}

void model::odb_databases(const std::list<std::string>& v) {
    odb_databases_ = v;
}

void model::odb_databases(const std::list<std::string>&& v) {
    odb_databases_ = std::move(v);
}

const std::string& model::odb_sql_name_case() const {
    return odb_sql_name_case_;
}

std::string& model::odb_sql_name_case() {
    return odb_sql_name_case_;
}

void model::odb_sql_name_case(const std::string& v) {
    odb_sql_name_case_ = v;
}

void model::odb_sql_name_case(const std::string&& v) {
    odb_sql_name_case_ = std::move(v);
}

}
