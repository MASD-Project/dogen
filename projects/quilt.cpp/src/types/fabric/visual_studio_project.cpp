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
#include "dogen/yarn/io/meta_model/element_io.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/fabric/visual_studio_project.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

visual_studio_project::visual_studio_project(
    const dogen::yarn::meta_model::name& name,
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::meta_model::origin_types origin_type,
    const boost::optional<dogen::yarn::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes,
    const std::list<std::string>& unknown_stereotypes,
    const dogen::yarn::meta_model::name& meta_name,
    const bool is_element_extension,
    const dogen::formatters::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::yarn::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::string& project_guid,
    const std::string& project_name,
    const std::string& tools_version)
    : dogen::yarn::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      well_known_stereotypes,
      unknown_stereotypes,
      meta_name,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties),
      project_guid_(project_guid),
      project_name_(project_name),
      tools_version_(tools_version) { }

void visual_studio_project::accept(const dogen::yarn::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void visual_studio_project::accept(dogen::yarn::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void visual_studio_project::accept(const dogen::yarn::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void visual_studio_project::accept(dogen::yarn::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void visual_studio_project::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::fabric::visual_studio_project\"" << ", "
      << "\"__parent_0__\": ";
    dogen::yarn::meta_model::element::to_stream(s);
    s << ", "
      << "\"project_guid\": " << "\"" << tidy_up_string(project_guid_) << "\"" << ", "
      << "\"project_name\": " << "\"" << tidy_up_string(project_name_) << "\"" << ", "
      << "\"tools_version\": " << "\"" << tidy_up_string(tools_version_) << "\""
      << " }";
}

void visual_studio_project::swap(visual_studio_project& other) noexcept {
    dogen::yarn::meta_model::element::swap(other);

    using std::swap;
    swap(project_guid_, other.project_guid_);
    swap(project_name_, other.project_name_);
    swap(tools_version_, other.tools_version_);
}

bool visual_studio_project::equals(const dogen::yarn::meta_model::element& other) const {
    const visual_studio_project* const p(dynamic_cast<const visual_studio_project* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool visual_studio_project::operator==(const visual_studio_project& rhs) const {
    return dogen::yarn::meta_model::element::compare(rhs) &&
        project_guid_ == rhs.project_guid_ &&
        project_name_ == rhs.project_name_ &&
        tools_version_ == rhs.tools_version_;
}

visual_studio_project& visual_studio_project::operator=(visual_studio_project other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& visual_studio_project::project_guid() const {
    return project_guid_;
}

std::string& visual_studio_project::project_guid() {
    return project_guid_;
}

void visual_studio_project::project_guid(const std::string& v) {
    project_guid_ = v;
}

void visual_studio_project::project_guid(const std::string&& v) {
    project_guid_ = std::move(v);
}

const std::string& visual_studio_project::project_name() const {
    return project_name_;
}

std::string& visual_studio_project::project_name() {
    return project_name_;
}

void visual_studio_project::project_name(const std::string& v) {
    project_name_ = v;
}

void visual_studio_project::project_name(const std::string&& v) {
    project_name_ = std::move(v);
}

const std::string& visual_studio_project::tools_version() const {
    return tools_version_;
}

std::string& visual_studio_project::tools_version() {
    return tools_version_;
}

void visual_studio_project::tools_version(const std::string& v) {
    tools_version_ = v;
}

void visual_studio_project::tools_version(const std::string&& v) {
    tools_version_ = std::move(v);
}

} } } }
