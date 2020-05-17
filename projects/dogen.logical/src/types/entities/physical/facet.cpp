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
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/physical/facet.hpp"
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

inline std::ostream& operator<<(std::ostream& s, const std::unordered_set<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

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

facet::facet()
    : major_technical_space_(static_cast<dogen::logical::entities::technical_space>(0)) { }

facet::facet(
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
    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::string& id,
    const dogen::logical::entities::technical_space major_technical_space,
    const std::unordered_set<std::string>& contains,
    const std::string& kernel_name,
    const std::string& backend_name,
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
      artefact_properties,
      enablement_properties,
      decoration),
      id_(id),
      major_technical_space_(major_technical_space),
      contains_(contains),
      kernel_name_(kernel_name),
      backend_name_(backend_name),
      archetypes_(archetypes) { }

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
      << "\"kernel_name\": " << "\"" << tidy_up_string(kernel_name_) << "\"" << ", "
      << "\"backend_name\": " << "\"" << tidy_up_string(backend_name_) << "\"" << ", "
      << "\"archetypes\": " << archetypes_
      << " }";
}

void facet::swap(facet& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(id_, other.id_);
    swap(major_technical_space_, other.major_technical_space_);
    swap(contains_, other.contains_);
    swap(kernel_name_, other.kernel_name_);
    swap(backend_name_, other.backend_name_);
    swap(archetypes_, other.archetypes_);
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
        kernel_name_ == rhs.kernel_name_ &&
        backend_name_ == rhs.backend_name_ &&
        archetypes_ == rhs.archetypes_;
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

dogen::logical::entities::technical_space facet::major_technical_space() const {
    return major_technical_space_;
}

void facet::major_technical_space(const dogen::logical::entities::technical_space v) {
    major_technical_space_ = v;
}

const std::unordered_set<std::string>& facet::contains() const {
    return contains_;
}

std::unordered_set<std::string>& facet::contains() {
    return contains_;
}

void facet::contains(const std::unordered_set<std::string>& v) {
    contains_ = v;
}

void facet::contains(const std::unordered_set<std::string>&& v) {
    contains_ = std::move(v);
}

const std::string& facet::kernel_name() const {
    return kernel_name_;
}

std::string& facet::kernel_name() {
    return kernel_name_;
}

void facet::kernel_name(const std::string& v) {
    kernel_name_ = v;
}

void facet::kernel_name(const std::string&& v) {
    kernel_name_ = std::move(v);
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

const std::list<dogen::logical::entities::name>& facet::archetypes() const {
    return archetypes_;
}

std::list<dogen::logical::entities::name>& facet::archetypes() {
    return archetypes_;
}

void facet::archetypes(const std::list<dogen::logical::entities::name>& v) {
    archetypes_ = v;
}

void facet::archetypes(const std::list<dogen::logical::entities::name>&& v) {
    archetypes_ = std::move(v);
}

}
