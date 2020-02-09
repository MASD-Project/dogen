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
#include "dogen.assets/types/meta_model/visual_studio/solution.hpp"
#include "dogen.assets/io/meta_model/visual_studio/project_persistence_block_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::assets::meta_model::visual_studio::project_persistence_block>& v) {
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

solution::solution(
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
    const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<dogen::assets::meta_model::technical_space, boost::optional<dogen::assets::meta_model::decoration::element_properties> >& decoration,
    const std::string& guid,
    const std::list<dogen::assets::meta_model::visual_studio::project_persistence_block>& project_persistence_blocks)
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
      artefact_properties,
      archetype_location_properties,
      decoration),
      guid_(guid),
      project_persistence_blocks_(project_persistence_blocks) { }

void solution::accept(const element_visitor& v) const {
    v.visit(*this);
}

void solution::accept(element_visitor& v) const {
    v.visit(*this);
    }

void solution::accept(const element_visitor& v) {
    v.visit(*this);
}

void solution::accept(element_visitor& v) {
    v.visit(*this);
}

void solution::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::visual_studio::solution\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"guid\": " << "\"" << tidy_up_string(guid_) << "\"" << ", "
      << "\"project_persistence_blocks\": " << project_persistence_blocks_
      << " }";
}

void solution::swap(solution& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(guid_, other.guid_);
    swap(project_persistence_blocks_, other.project_persistence_blocks_);
}

bool solution::equals(const dogen::assets::meta_model::element& other) const {
    const solution* const p(dynamic_cast<const solution* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool solution::operator==(const solution& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        guid_ == rhs.guid_ &&
        project_persistence_blocks_ == rhs.project_persistence_blocks_;
}

solution& solution::operator=(solution other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& solution::guid() const {
    return guid_;
}

std::string& solution::guid() {
    return guid_;
}

void solution::guid(const std::string& v) {
    guid_ = v;
}

void solution::guid(const std::string&& v) {
    guid_ = std::move(v);
}

const std::list<dogen::assets::meta_model::visual_studio::project_persistence_block>& solution::project_persistence_blocks() const {
    return project_persistence_blocks_;
}

std::list<dogen::assets::meta_model::visual_studio::project_persistence_block>& solution::project_persistence_blocks() {
    return project_persistence_blocks_;
}

void solution::project_persistence_blocks(const std::list<dogen::assets::meta_model::visual_studio::project_persistence_block>& v) {
    project_persistence_blocks_ = v;
}

void solution::project_persistence_blocks(const std::list<dogen::assets::meta_model::visual_studio::project_persistence_block>&& v) {
    project_persistence_blocks_ = std::move(v);
}

}
