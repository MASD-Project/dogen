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
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/physical/part.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::name>& v) {
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

part::part()
    : major_technical_space_(static_cast<dogen::logical::entities::technical_space>(0)),
      requires_relative_path_(static_cast<bool>(0)) { }

part::part(
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
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::string& id,
    const dogen::logical::entities::technical_space major_technical_space,
    const std::string& meta_model_name,
    const std::string& backend_name,
    const std::string& external_modules_path_contribution,
    const std::string& model_modules_path_contribution,
    const std::string& facet_path_contribution,
    const std::string& internal_modules_path_contribution,
    const bool requires_relative_path,
    const std::list<dogen::logical::entities::name>& archetypes)
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
      generability_status,
      decoration),
      id_(id),
      major_technical_space_(major_technical_space),
      meta_model_name_(meta_model_name),
      backend_name_(backend_name),
      external_modules_path_contribution_(external_modules_path_contribution),
      model_modules_path_contribution_(model_modules_path_contribution),
      facet_path_contribution_(facet_path_contribution),
      internal_modules_path_contribution_(internal_modules_path_contribution),
      requires_relative_path_(requires_relative_path),
      archetypes_(archetypes) { }

void part::accept(const element_visitor& v) const {
    v.visit(*this);
}

void part::accept(element_visitor& v) const {
    v.visit(*this);
    }

void part::accept(const element_visitor& v) {
    v.visit(*this);
}

void part::accept(element_visitor& v) {
    v.visit(*this);
}

void part::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::physical::part\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"id\": " << "\"" << tidy_up_string(id_) << "\"" << ", "
      << "\"major_technical_space\": " << major_technical_space_ << ", "
      << "\"meta_model_name\": " << "\"" << tidy_up_string(meta_model_name_) << "\"" << ", "
      << "\"backend_name\": " << "\"" << tidy_up_string(backend_name_) << "\"" << ", "
      << "\"external_modules_path_contribution\": " << "\"" << tidy_up_string(external_modules_path_contribution_) << "\"" << ", "
      << "\"model_modules_path_contribution\": " << "\"" << tidy_up_string(model_modules_path_contribution_) << "\"" << ", "
      << "\"facet_path_contribution\": " << "\"" << tidy_up_string(facet_path_contribution_) << "\"" << ", "
      << "\"internal_modules_path_contribution\": " << "\"" << tidy_up_string(internal_modules_path_contribution_) << "\"" << ", "
      << "\"requires_relative_path\": " << requires_relative_path_ << ", "
      << "\"archetypes\": " << archetypes_
      << " }";
}

void part::swap(part& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(id_, other.id_);
    swap(major_technical_space_, other.major_technical_space_);
    swap(meta_model_name_, other.meta_model_name_);
    swap(backend_name_, other.backend_name_);
    swap(external_modules_path_contribution_, other.external_modules_path_contribution_);
    swap(model_modules_path_contribution_, other.model_modules_path_contribution_);
    swap(facet_path_contribution_, other.facet_path_contribution_);
    swap(internal_modules_path_contribution_, other.internal_modules_path_contribution_);
    swap(requires_relative_path_, other.requires_relative_path_);
    swap(archetypes_, other.archetypes_);
}

bool part::equals(const dogen::logical::entities::element& other) const {
    const part* const p(dynamic_cast<const part* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool part::operator==(const part& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        id_ == rhs.id_ &&
        major_technical_space_ == rhs.major_technical_space_ &&
        meta_model_name_ == rhs.meta_model_name_ &&
        backend_name_ == rhs.backend_name_ &&
        external_modules_path_contribution_ == rhs.external_modules_path_contribution_ &&
        model_modules_path_contribution_ == rhs.model_modules_path_contribution_ &&
        facet_path_contribution_ == rhs.facet_path_contribution_ &&
        internal_modules_path_contribution_ == rhs.internal_modules_path_contribution_ &&
        requires_relative_path_ == rhs.requires_relative_path_ &&
        archetypes_ == rhs.archetypes_;
}

part& part::operator=(part other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& part::id() const {
    return id_;
}

std::string& part::id() {
    return id_;
}

void part::id(const std::string& v) {
    id_ = v;
}

void part::id(const std::string&& v) {
    id_ = std::move(v);
}

dogen::logical::entities::technical_space part::major_technical_space() const {
    return major_technical_space_;
}

void part::major_technical_space(const dogen::logical::entities::technical_space v) {
    major_technical_space_ = v;
}

const std::string& part::meta_model_name() const {
    return meta_model_name_;
}

std::string& part::meta_model_name() {
    return meta_model_name_;
}

void part::meta_model_name(const std::string& v) {
    meta_model_name_ = v;
}

void part::meta_model_name(const std::string&& v) {
    meta_model_name_ = std::move(v);
}

const std::string& part::backend_name() const {
    return backend_name_;
}

std::string& part::backend_name() {
    return backend_name_;
}

void part::backend_name(const std::string& v) {
    backend_name_ = v;
}

void part::backend_name(const std::string&& v) {
    backend_name_ = std::move(v);
}

const std::string& part::external_modules_path_contribution() const {
    return external_modules_path_contribution_;
}

std::string& part::external_modules_path_contribution() {
    return external_modules_path_contribution_;
}

void part::external_modules_path_contribution(const std::string& v) {
    external_modules_path_contribution_ = v;
}

void part::external_modules_path_contribution(const std::string&& v) {
    external_modules_path_contribution_ = std::move(v);
}

const std::string& part::model_modules_path_contribution() const {
    return model_modules_path_contribution_;
}

std::string& part::model_modules_path_contribution() {
    return model_modules_path_contribution_;
}

void part::model_modules_path_contribution(const std::string& v) {
    model_modules_path_contribution_ = v;
}

void part::model_modules_path_contribution(const std::string&& v) {
    model_modules_path_contribution_ = std::move(v);
}

const std::string& part::facet_path_contribution() const {
    return facet_path_contribution_;
}

std::string& part::facet_path_contribution() {
    return facet_path_contribution_;
}

void part::facet_path_contribution(const std::string& v) {
    facet_path_contribution_ = v;
}

void part::facet_path_contribution(const std::string&& v) {
    facet_path_contribution_ = std::move(v);
}

const std::string& part::internal_modules_path_contribution() const {
    return internal_modules_path_contribution_;
}

std::string& part::internal_modules_path_contribution() {
    return internal_modules_path_contribution_;
}

void part::internal_modules_path_contribution(const std::string& v) {
    internal_modules_path_contribution_ = v;
}

void part::internal_modules_path_contribution(const std::string&& v) {
    internal_modules_path_contribution_ = std::move(v);
}

bool part::requires_relative_path() const {
    return requires_relative_path_;
}

void part::requires_relative_path(const bool v) {
    requires_relative_path_ = v;
}

const std::list<dogen::logical::entities::name>& part::archetypes() const {
    return archetypes_;
}

std::list<dogen::logical::entities::name>& part::archetypes() {
    return archetypes_;
}

void part::archetypes(const std::list<dogen::logical::entities::name>& v) {
    archetypes_ = v;
}

void part::archetypes(const std::list<dogen::logical::entities::name>&& v) {
    archetypes_ = std::move(v);
}

}
