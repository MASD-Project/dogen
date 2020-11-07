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
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::logical_id>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::identification::entities::logical_name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::physical {

backend::backend()
    : major_technical_space_(static_cast<dogen::identification::entities::technical_space>(0)) { }

backend::backend(
    const dogen::identification::entities::logical_name& name,
    const std::string& documentation,
    const dogen::identification::entities::codec_provenance& provenance,
    const dogen::identification::entities::logical_id& contained_by,
    const bool in_global_module,
    const dogen::logical::entities::stereotypes& stereotypes,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::identification::entities::label>& labels,
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::list<dogen::logical::entities::helper_properties>& helper_properties,
    const std::string& id,
    const dogen::identification::entities::technical_space major_technical_space,
    const std::list<dogen::identification::entities::logical_id>& contains,
    const std::string& technical_space,
    const std::string& meta_model_name,
    const std::list<dogen::identification::entities::logical_name>& facets,
    const std::list<dogen::identification::entities::logical_name>& parts,
    const std::list<dogen::identification::entities::logical_name>& archetype_kinds,
    const std::string& backend_name,
    const std::string& directory_name)
    : dogen::logical::entities::element(
      name,
      documentation,
      provenance,
      contained_by,
      in_global_module,
      stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      generability_status,
      decoration,
      helper_properties),
      id_(id),
      major_technical_space_(major_technical_space),
      contains_(contains),
      technical_space_(technical_space),
      meta_model_name_(meta_model_name),
      facets_(facets),
      parts_(parts),
      archetype_kinds_(archetype_kinds),
      backend_name_(backend_name),
      directory_name_(directory_name) { }

void backend::accept(const element_visitor& v) const {
    v.visit(*this);
}

void backend::accept(element_visitor& v) const {
    v.visit(*this);
    }

void backend::accept(const element_visitor& v) {
    v.visit(*this);
}

void backend::accept(element_visitor& v) {
    v.visit(*this);
}

void backend::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::physical::backend\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"id\": " << "\"" << tidy_up_string(id_) << "\"" << ", "
      << "\"major_technical_space\": " << major_technical_space_ << ", "
      << "\"contains\": " << contains_ << ", "
      << "\"technical_space\": " << "\"" << tidy_up_string(technical_space_) << "\"" << ", "
      << "\"meta_model_name\": " << "\"" << tidy_up_string(meta_model_name_) << "\"" << ", "
      << "\"facets\": " << facets_ << ", "
      << "\"parts\": " << parts_ << ", "
      << "\"archetype_kinds\": " << archetype_kinds_ << ", "
      << "\"backend_name\": " << "\"" << tidy_up_string(backend_name_) << "\"" << ", "
      << "\"directory_name\": " << "\"" << tidy_up_string(directory_name_) << "\""
      << " }";
}

void backend::swap(backend& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(id_, other.id_);
    swap(major_technical_space_, other.major_technical_space_);
    swap(contains_, other.contains_);
    swap(technical_space_, other.technical_space_);
    swap(meta_model_name_, other.meta_model_name_);
    swap(facets_, other.facets_);
    swap(parts_, other.parts_);
    swap(archetype_kinds_, other.archetype_kinds_);
    swap(backend_name_, other.backend_name_);
    swap(directory_name_, other.directory_name_);
}

bool backend::equals(const dogen::logical::entities::element& other) const {
    const backend* const p(dynamic_cast<const backend* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool backend::operator==(const backend& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        id_ == rhs.id_ &&
        major_technical_space_ == rhs.major_technical_space_ &&
        contains_ == rhs.contains_ &&
        technical_space_ == rhs.technical_space_ &&
        meta_model_name_ == rhs.meta_model_name_ &&
        facets_ == rhs.facets_ &&
        parts_ == rhs.parts_ &&
        archetype_kinds_ == rhs.archetype_kinds_ &&
        backend_name_ == rhs.backend_name_ &&
        directory_name_ == rhs.directory_name_;
}

backend& backend::operator=(backend other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& backend::id() const {
    return id_;
}

std::string& backend::id() {
    return id_;
}

void backend::id(const std::string& v) {
    id_ = v;
}

void backend::id(const std::string&& v) {
    id_ = std::move(v);
}

dogen::identification::entities::technical_space backend::major_technical_space() const {
    return major_technical_space_;
}

void backend::major_technical_space(const dogen::identification::entities::technical_space v) {
    major_technical_space_ = v;
}

const std::list<dogen::identification::entities::logical_id>& backend::contains() const {
    return contains_;
}

std::list<dogen::identification::entities::logical_id>& backend::contains() {
    return contains_;
}

void backend::contains(const std::list<dogen::identification::entities::logical_id>& v) {
    contains_ = v;
}

void backend::contains(const std::list<dogen::identification::entities::logical_id>&& v) {
    contains_ = std::move(v);
}

const std::string& backend::technical_space() const {
    return technical_space_;
}

std::string& backend::technical_space() {
    return technical_space_;
}

void backend::technical_space(const std::string& v) {
    technical_space_ = v;
}

void backend::technical_space(const std::string&& v) {
    technical_space_ = std::move(v);
}

const std::string& backend::meta_model_name() const {
    return meta_model_name_;
}

std::string& backend::meta_model_name() {
    return meta_model_name_;
}

void backend::meta_model_name(const std::string& v) {
    meta_model_name_ = v;
}

void backend::meta_model_name(const std::string&& v) {
    meta_model_name_ = std::move(v);
}

const std::list<dogen::identification::entities::logical_name>& backend::facets() const {
    return facets_;
}

std::list<dogen::identification::entities::logical_name>& backend::facets() {
    return facets_;
}

void backend::facets(const std::list<dogen::identification::entities::logical_name>& v) {
    facets_ = v;
}

void backend::facets(const std::list<dogen::identification::entities::logical_name>&& v) {
    facets_ = std::move(v);
}

const std::list<dogen::identification::entities::logical_name>& backend::parts() const {
    return parts_;
}

std::list<dogen::identification::entities::logical_name>& backend::parts() {
    return parts_;
}

void backend::parts(const std::list<dogen::identification::entities::logical_name>& v) {
    parts_ = v;
}

void backend::parts(const std::list<dogen::identification::entities::logical_name>&& v) {
    parts_ = std::move(v);
}

const std::list<dogen::identification::entities::logical_name>& backend::archetype_kinds() const {
    return archetype_kinds_;
}

std::list<dogen::identification::entities::logical_name>& backend::archetype_kinds() {
    return archetype_kinds_;
}

void backend::archetype_kinds(const std::list<dogen::identification::entities::logical_name>& v) {
    archetype_kinds_ = v;
}

void backend::archetype_kinds(const std::list<dogen::identification::entities::logical_name>&& v) {
    archetype_kinds_ = std::move(v);
}

const std::string& backend::backend_name() const {
    return backend_name_;
}

std::string& backend::backend_name() {
    return backend_name_;
}

void backend::backend_name(const std::string& v) {
    backend_name_ = v;
}

void backend::backend_name(const std::string&& v) {
    backend_name_ = std::move(v);
}

const std::string& backend::directory_name() const {
    return directory_name_;
}

std::string& backend::directory_name() {
    return directory_name_;
}

void backend::directory_name(const std::string& v) {
    directory_name_ = v;
}

void backend::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

}
