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
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"

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

backend::backend(
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
    const std::string& kernel_name,
    const std::list<dogen::logical::entities::name>& facets,
    const std::list<dogen::logical::entities::name>& parts)
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
      kernel_name_(kernel_name),
      facets_(facets),
      parts_(parts) { }

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
      << "\"kernel_name\": " << "\"" << tidy_up_string(kernel_name_) << "\"" << ", "
      << "\"facets\": " << facets_ << ", "
      << "\"parts\": " << parts_
      << " }";
}

void backend::swap(backend& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(id_, other.id_);
    swap(kernel_name_, other.kernel_name_);
    swap(facets_, other.facets_);
    swap(parts_, other.parts_);
}

bool backend::equals(const dogen::logical::entities::element& other) const {
    const backend* const p(dynamic_cast<const backend* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool backend::operator==(const backend& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        id_ == rhs.id_ &&
        kernel_name_ == rhs.kernel_name_ &&
        facets_ == rhs.facets_ &&
        parts_ == rhs.parts_;
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

const std::string& backend::kernel_name() const {
    return kernel_name_;
}

std::string& backend::kernel_name() {
    return kernel_name_;
}

void backend::kernel_name(const std::string& v) {
    kernel_name_ = v;
}

void backend::kernel_name(const std::string&& v) {
    kernel_name_ = std::move(v);
}

const std::list<dogen::logical::entities::name>& backend::facets() const {
    return facets_;
}

std::list<dogen::logical::entities::name>& backend::facets() {
    return facets_;
}

void backend::facets(const std::list<dogen::logical::entities::name>& v) {
    facets_ = v;
}

void backend::facets(const std::list<dogen::logical::entities::name>&& v) {
    facets_ = std::move(v);
}

const std::list<dogen::logical::entities::name>& backend::parts() const {
    return parts_;
}

std::list<dogen::logical::entities::name>& backend::parts() {
    return parts_;
}

void backend::parts(const std::list<dogen::logical::entities::name>& v) {
    parts_ = v;
}

void backend::parts(const std::list<dogen::logical::entities::name>&& v) {
    parts_ = std::move(v);
}

}