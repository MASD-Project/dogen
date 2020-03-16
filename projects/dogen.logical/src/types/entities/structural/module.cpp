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
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/io/entities/orm/module_properties_io.hpp"

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

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::logical::entities::orm::module_properties>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::logical::entities::structural {

module::module()
    : is_root_(static_cast<bool>(0)),
      is_global_module_(static_cast<bool>(0)) { }

module::module(module&& rhs)
    : dogen::logical::entities::element(
        std::forward<dogen::logical::entities::element>(rhs)),
      contains_(std::move(rhs.contains_)),
      is_root_(std::move(rhs.is_root_)),
      is_global_module_(std::move(rhs.is_global_module_)),
      orm_properties_(std::move(rhs.orm_properties_)) { }

module::module(
    const dogen::logical::entities::name& name,
    const std::string& documentation,
    const dogen::logical::entities::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::entities::name& meta_name,
    const dogen::logical::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::entities::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::unordered_set<std::string>& contains,
    const bool is_root,
    const bool is_global_module,
    const boost::optional<dogen::logical::entities::orm::module_properties>& orm_properties)
    : dogen::logical::entities::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      origin_element_id,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      artefact_properties,
      archetype_location_properties,
      decoration),
      contains_(contains),
      is_root_(is_root),
      is_global_module_(is_global_module),
      orm_properties_(orm_properties) { }

void module::accept(const element_visitor& v) const {
    v.visit(*this);
}

void module::accept(element_visitor& v) const {
    v.visit(*this);
    }

void module::accept(const element_visitor& v) {
    v.visit(*this);
}

void module::accept(element_visitor& v) {
    v.visit(*this);
}

void module::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::structural::module\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"contains\": " << contains_ << ", "
      << "\"is_root\": " << is_root_ << ", "
      << "\"is_global_module\": " << is_global_module_ << ", "
      << "\"orm_properties\": " << orm_properties_
      << " }";
}

void module::swap(module& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(contains_, other.contains_);
    swap(is_root_, other.is_root_);
    swap(is_global_module_, other.is_global_module_);
    swap(orm_properties_, other.orm_properties_);
}

bool module::equals(const dogen::logical::entities::element& other) const {
    const module* const p(dynamic_cast<const module* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool module::operator==(const module& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        contains_ == rhs.contains_ &&
        is_root_ == rhs.is_root_ &&
        is_global_module_ == rhs.is_global_module_ &&
        orm_properties_ == rhs.orm_properties_;
}

module& module::operator=(module other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& module::contains() const {
    return contains_;
}

std::unordered_set<std::string>& module::contains() {
    return contains_;
}

void module::contains(const std::unordered_set<std::string>& v) {
    contains_ = v;
}

void module::contains(const std::unordered_set<std::string>&& v) {
    contains_ = std::move(v);
}

bool module::is_root() const {
    return is_root_;
}

void module::is_root(const bool v) {
    is_root_ = v;
}

bool module::is_global_module() const {
    return is_global_module_;
}

void module::is_global_module(const bool v) {
    is_global_module_ = v;
}

const boost::optional<dogen::logical::entities::orm::module_properties>& module::orm_properties() const {
    return orm_properties_;
}

boost::optional<dogen::logical::entities::orm::module_properties>& module::orm_properties() {
    return orm_properties_;
}

void module::orm_properties(const boost::optional<dogen::logical::entities::orm::module_properties>& v) {
    orm_properties_ = v;
}

void module::orm_properties(const boost::optional<dogen::logical::entities::orm::module_properties>&& v) {
    orm_properties_ = std::move(v);
}

}
