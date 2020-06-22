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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::logical::entities::physical {

archetype_kind::archetype_kind()
    : major_technical_space_(static_cast<dogen::logical::entities::technical_space>(0)) { }

archetype_kind::archetype_kind(
    const dogen::logical::entities::name& name,
    const std::string& documentation,
    const dogen::logical::entities::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::entities::name& meta_name,
    const dogen::logical::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::logical::entities::label>& labels,
    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::string& id,
    const dogen::logical::entities::technical_space major_technical_space,
    const std::string& meta_model_name,
    const std::string& backend_name,
    const std::string& file_extension)
    : dogen::logical::entities::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      artefact_properties,
      enablement_properties,
      decoration),
      id_(id),
      major_technical_space_(major_technical_space),
      meta_model_name_(meta_model_name),
      backend_name_(backend_name),
      file_extension_(file_extension) { }

void archetype_kind::accept(const element_visitor& v) const {
    v.visit(*this);
}

void archetype_kind::accept(element_visitor& v) const {
    v.visit(*this);
    }

void archetype_kind::accept(const element_visitor& v) {
    v.visit(*this);
}

void archetype_kind::accept(element_visitor& v) {
    v.visit(*this);
}

void archetype_kind::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::physical::archetype_kind\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"id\": " << "\"" << tidy_up_string(id_) << "\"" << ", "
      << "\"major_technical_space\": " << major_technical_space_ << ", "
      << "\"meta_model_name\": " << "\"" << tidy_up_string(meta_model_name_) << "\"" << ", "
      << "\"backend_name\": " << "\"" << tidy_up_string(backend_name_) << "\"" << ", "
      << "\"file_extension\": " << "\"" << tidy_up_string(file_extension_) << "\""
      << " }";
}

void archetype_kind::swap(archetype_kind& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(id_, other.id_);
    swap(major_technical_space_, other.major_technical_space_);
    swap(meta_model_name_, other.meta_model_name_);
    swap(backend_name_, other.backend_name_);
    swap(file_extension_, other.file_extension_);
}

bool archetype_kind::equals(const dogen::logical::entities::element& other) const {
    const archetype_kind* const p(dynamic_cast<const archetype_kind* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool archetype_kind::operator==(const archetype_kind& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        id_ == rhs.id_ &&
        major_technical_space_ == rhs.major_technical_space_ &&
        meta_model_name_ == rhs.meta_model_name_ &&
        backend_name_ == rhs.backend_name_ &&
        file_extension_ == rhs.file_extension_;
}

archetype_kind& archetype_kind::operator=(archetype_kind other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& archetype_kind::id() const {
    return id_;
}

std::string& archetype_kind::id() {
    return id_;
}

void archetype_kind::id(const std::string& v) {
    id_ = v;
}

void archetype_kind::id(const std::string&& v) {
    id_ = std::move(v);
}

dogen::logical::entities::technical_space archetype_kind::major_technical_space() const {
    return major_technical_space_;
}

void archetype_kind::major_technical_space(const dogen::logical::entities::technical_space v) {
    major_technical_space_ = v;
}

const std::string& archetype_kind::meta_model_name() const {
    return meta_model_name_;
}

std::string& archetype_kind::meta_model_name() {
    return meta_model_name_;
}

void archetype_kind::meta_model_name(const std::string& v) {
    meta_model_name_ = v;
}

void archetype_kind::meta_model_name(const std::string&& v) {
    meta_model_name_ = std::move(v);
}

const std::string& archetype_kind::backend_name() const {
    return backend_name_;
}

std::string& archetype_kind::backend_name() {
    return backend_name_;
}

void archetype_kind::backend_name(const std::string& v) {
    backend_name_ = v;
}

void archetype_kind::backend_name(const std::string&& v) {
    backend_name_ = std::move(v);
}

const std::string& archetype_kind::file_extension() const {
    return file_extension_;
}

std::string& archetype_kind::file_extension() {
    return file_extension_;
}

void archetype_kind::file_extension(const std::string& v) {
    file_extension_ = v;
}

void archetype_kind::file_extension(const std::string&& v) {
    file_extension_ = std::move(v);
}

}
