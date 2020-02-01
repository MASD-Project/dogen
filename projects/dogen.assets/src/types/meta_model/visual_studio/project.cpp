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
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.assets/types/meta_model/element_visitor.hpp"
#include "dogen.assets/types/meta_model/visual_studio/project.hpp"
#include "dogen.assets/io/meta_model/visual_studio/item_group_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::assets::meta_model::visual_studio::item_group>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::assets::meta_model::visual_studio {

project::project(
    const dogen::assets::meta_model::name& name,
    const std::string& documentation,
    const dogen::assets::meta_model::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::assets::meta_model::name& meta_name,
    const dogen::assets::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const bool is_element_extension,
    const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
    const std::string& guid,
    const std::string& type_guid,
    const std::list<dogen::assets::meta_model::visual_studio::item_group>& item_groups)
    : dogen::assets::meta_model::element(
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
      is_element_extension,
      artefact_properties,
      archetype_location_properties,
      decoration),
      guid_(guid),
      type_guid_(type_guid),
      item_groups_(item_groups) { }

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
      << "\"__type__\": " << "\"dogen::assets::meta_model::visual_studio::project\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"guid\": " << "\"" << tidy_up_string(guid_) << "\"" << ", "
      << "\"type_guid\": " << "\"" << tidy_up_string(type_guid_) << "\"" << ", "
      << "\"item_groups\": " << item_groups_
      << " }";
}

void project::swap(project& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(guid_, other.guid_);
    swap(type_guid_, other.type_guid_);
    swap(item_groups_, other.item_groups_);
}

bool project::equals(const dogen::assets::meta_model::element& other) const {
    const project* const p(dynamic_cast<const project* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool project::operator==(const project& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        guid_ == rhs.guid_ &&
        type_guid_ == rhs.type_guid_ &&
        item_groups_ == rhs.item_groups_;
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

const std::list<dogen::assets::meta_model::visual_studio::item_group>& project::item_groups() const {
    return item_groups_;
}

std::list<dogen::assets::meta_model::visual_studio::item_group>& project::item_groups() {
    return item_groups_;
}

void project::item_groups(const std::list<dogen::assets::meta_model::visual_studio::item_group>& v) {
    item_groups_ = v;
}

void project::item_groups(const std::list<dogen::assets::meta_model::visual_studio::item_group>&& v) {
    item_groups_ = std::move(v);
}

}
