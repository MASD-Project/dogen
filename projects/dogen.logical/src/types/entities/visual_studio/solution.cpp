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
#include "dogen.logical/types/entities/visual_studio/solution.hpp"
#include "dogen.logical/io/entities/visual_studio/project_persistence_block_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::visual_studio::project_persistence_block>& v) {
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

solution::solution(
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
    const std::string& guid,
    const std::list<dogen::logical::entities::visual_studio::project_persistence_block>& project_persistence_blocks)
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
      << "\"__type__\": " << "\"dogen::logical::entities::visual_studio::solution\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"guid\": " << "\"" << tidy_up_string(guid_) << "\"" << ", "
      << "\"project_persistence_blocks\": " << project_persistence_blocks_
      << " }";
}

void solution::swap(solution& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(guid_, other.guid_);
    swap(project_persistence_blocks_, other.project_persistence_blocks_);
}

bool solution::equals(const dogen::logical::entities::element& other) const {
    const solution* const p(dynamic_cast<const solution* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool solution::operator==(const solution& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
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

const std::list<dogen::logical::entities::visual_studio::project_persistence_block>& solution::project_persistence_blocks() const {
    return project_persistence_blocks_;
}

std::list<dogen::logical::entities::visual_studio::project_persistence_block>& solution::project_persistence_blocks() {
    return project_persistence_blocks_;
}

void solution::project_persistence_blocks(const std::list<dogen::logical::entities::visual_studio::project_persistence_block>& v) {
    project_persistence_blocks_ = v;
}

void solution::project_persistence_blocks(const std::list<dogen::logical::entities::visual_studio::project_persistence_block>&& v) {
    project_persistence_blocks_ = std::move(v);
}

}
