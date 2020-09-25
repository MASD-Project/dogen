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
#include "dogen.logical/types/entities/physical/facet.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
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

facet::facet()
    : major_technical_space_(static_cast<dogen::identification::entities::technical_space>(0)) { }

facet::facet(
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
    const std::string& id,
    const dogen::identification::entities::technical_space major_technical_space,
    const std::list<dogen::identification::entities::logical_id>& contains,
    const std::string& meta_model_name,
    const std::string& backend_name,
    const std::list<dogen::identification::entities::logical_name>& archetypes,
    const std::string& directory_name,
    const std::string& postfix)
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
      decoration),
      id_(id),
      major_technical_space_(major_technical_space),
      contains_(contains),
      meta_model_name_(meta_model_name),
      backend_name_(backend_name),
      archetypes_(archetypes),
      directory_name_(directory_name),
      postfix_(postfix) { }

void facet::accept(const element_visitor& v) const {
    v.visit(*this);
}

void facet::accept(element_visitor& v) const {
    v.visit(*this);
    }

void facet::accept(const element_visitor& v) {
    v.visit(*this);
}

void facet::accept(element_visitor& v) {
    v.visit(*this);
}

void facet::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::physical::facet\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"id\": " << "\"" << tidy_up_string(id_) << "\"" << ", "
      << "\"major_technical_space\": " << major_technical_space_ << ", "
      << "\"contains\": " << contains_ << ", "
      << "\"meta_model_name\": " << "\"" << tidy_up_string(meta_model_name_) << "\"" << ", "
      << "\"backend_name\": " << "\"" << tidy_up_string(backend_name_) << "\"" << ", "
      << "\"archetypes\": " << archetypes_ << ", "
      << "\"directory_name\": " << "\"" << tidy_up_string(directory_name_) << "\"" << ", "
      << "\"postfix\": " << "\"" << tidy_up_string(postfix_) << "\""
      << " }";
}

void facet::swap(facet& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(id_, other.id_);
    swap(major_technical_space_, other.major_technical_space_);
    swap(contains_, other.contains_);
    swap(meta_model_name_, other.meta_model_name_);
    swap(backend_name_, other.backend_name_);
    swap(archetypes_, other.archetypes_);
    swap(directory_name_, other.directory_name_);
    swap(postfix_, other.postfix_);
}

bool facet::equals(const dogen::logical::entities::element& other) const {
    const facet* const p(dynamic_cast<const facet* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool facet::operator==(const facet& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        id_ == rhs.id_ &&
        major_technical_space_ == rhs.major_technical_space_ &&
        contains_ == rhs.contains_ &&
        meta_model_name_ == rhs.meta_model_name_ &&
        backend_name_ == rhs.backend_name_ &&
        archetypes_ == rhs.archetypes_ &&
        directory_name_ == rhs.directory_name_ &&
        postfix_ == rhs.postfix_;
}

facet& facet::operator=(facet other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& facet::id() const {
    return id_;
}

std::string& facet::id() {
    return id_;
}

void facet::id(const std::string& v) {
    id_ = v;
}

void facet::id(const std::string&& v) {
    id_ = std::move(v);
}

dogen::identification::entities::technical_space facet::major_technical_space() const {
    return major_technical_space_;
}

void facet::major_technical_space(const dogen::identification::entities::technical_space v) {
    major_technical_space_ = v;
}

const std::list<dogen::identification::entities::logical_id>& facet::contains() const {
    return contains_;
}

std::list<dogen::identification::entities::logical_id>& facet::contains() {
    return contains_;
}

void facet::contains(const std::list<dogen::identification::entities::logical_id>& v) {
    contains_ = v;
}

void facet::contains(const std::list<dogen::identification::entities::logical_id>&& v) {
    contains_ = std::move(v);
}

const std::string& facet::meta_model_name() const {
    return meta_model_name_;
}

std::string& facet::meta_model_name() {
    return meta_model_name_;
}

void facet::meta_model_name(const std::string& v) {
    meta_model_name_ = v;
}

void facet::meta_model_name(const std::string&& v) {
    meta_model_name_ = std::move(v);
}

const std::string& facet::backend_name() const {
    return backend_name_;
}

std::string& facet::backend_name() {
    return backend_name_;
}

void facet::backend_name(const std::string& v) {
    backend_name_ = v;
}

void facet::backend_name(const std::string&& v) {
    backend_name_ = std::move(v);
}

const std::list<dogen::identification::entities::logical_name>& facet::archetypes() const {
    return archetypes_;
}

std::list<dogen::identification::entities::logical_name>& facet::archetypes() {
    return archetypes_;
}

void facet::archetypes(const std::list<dogen::identification::entities::logical_name>& v) {
    archetypes_ = v;
}

void facet::archetypes(const std::list<dogen::identification::entities::logical_name>&& v) {
    archetypes_ = std::move(v);
}

const std::string& facet::directory_name() const {
    return directory_name_;
}

std::string& facet::directory_name() {
    return directory_name_;
}

void facet::directory_name(const std::string& v) {
    directory_name_ = v;
}

void facet::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

const std::string& facet::postfix() const {
    return postfix_;
}

std::string& facet::postfix() {
    return postfix_;
}

void facet::postfix(const std::string& v) {
    postfix_ = v;
}

void facet::postfix(const std::string&& v) {
    postfix_ = std::move(v);
}

}
