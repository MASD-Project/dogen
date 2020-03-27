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
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.logical/io/entities/visual_studio/item_group_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::visual_studio::item_group>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::visual_studio {

project::project(
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
    const std::string& guid,
    const std::string& type_guid,
    const std::list<dogen::logical::entities::visual_studio::item_group>& item_groups,
    const std::string& project_name)
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
      guid_(guid),
      type_guid_(type_guid),
      item_groups_(item_groups),
      project_name_(project_name) { }

void project::accept(const element_visitor& v) const {
    v.visit(*this);
}

void project::accept(element_visitor& v) const {
    v.visit(*this);
    }

void project::accept(const element_visitor& v) {
    v.visit(*this);
}

void project::accept(element_visitor& v) {
    v.visit(*this);
}

void project::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::visual_studio::project\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"guid\": " << "\"" << tidy_up_string(guid_) << "\"" << ", "
      << "\"type_guid\": " << "\"" << tidy_up_string(type_guid_) << "\"" << ", "
      << "\"item_groups\": " << item_groups_ << ", "
      << "\"project_name\": " << "\"" << tidy_up_string(project_name_) << "\""
      << " }";
}

void project::swap(project& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(guid_, other.guid_);
    swap(type_guid_, other.type_guid_);
    swap(item_groups_, other.item_groups_);
    swap(project_name_, other.project_name_);
}

bool project::equals(const dogen::logical::entities::element& other) const {
    const project* const p(dynamic_cast<const project* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool project::operator==(const project& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        guid_ == rhs.guid_ &&
        type_guid_ == rhs.type_guid_ &&
        item_groups_ == rhs.item_groups_ &&
        project_name_ == rhs.project_name_;
}

project& project::operator=(project other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& project::guid() const {
    return guid_;
}

std::string& project::guid() {
    return guid_;
}

void project::guid(const std::string& v) {
    guid_ = v;
}

void project::guid(const std::string&& v) {
    guid_ = std::move(v);
}

const std::string& project::type_guid() const {
    return type_guid_;
}

std::string& project::type_guid() {
    return type_guid_;
}

void project::type_guid(const std::string& v) {
    type_guid_ = v;
}

void project::type_guid(const std::string&& v) {
    type_guid_ = std::move(v);
}

const std::list<dogen::logical::entities::visual_studio::item_group>& project::item_groups() const {
    return item_groups_;
}

std::list<dogen::logical::entities::visual_studio::item_group>& project::item_groups() {
    return item_groups_;
}

void project::item_groups(const std::list<dogen::logical::entities::visual_studio::item_group>& v) {
    item_groups_ = v;
}

void project::item_groups(const std::list<dogen::logical::entities::visual_studio::item_group>&& v) {
    item_groups_ = std::move(v);
}

const std::string& project::project_name() const {
    return project_name_;
}

std::string& project::project_name() {
    return project_name_;
}

void project::project_name(const std::string& v) {
    project_name_ = v;
}

void project::project_name(const std::string&& v) {
    project_name_ = std::move(v);
}

}
