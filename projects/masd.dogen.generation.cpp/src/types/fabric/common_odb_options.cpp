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
#include "masd.dogen.coding/io/meta_model/element_io.hpp"
#include "masd.dogen.generation.cpp/types/fabric/element_visitor.hpp"
#include "masd.dogen.generation.cpp/types/fabric/common_odb_options.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace masd::dogen::generation::cpp::fabric {

common_odb_options::common_odb_options(
    const masd::dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const masd::dogen::annotations::annotation& annotation,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const boost::optional<masd::dogen::coding::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const masd::dogen::coding::meta_model::name& meta_name,
    const bool is_element_extension,
    const masd::dogen::extraction::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::string& sql_name_case,
    const std::list<std::string>& databases)
    : masd::dogen::coding::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties),
      sql_name_case_(sql_name_case),
      databases_(databases) { }

void common_odb_options::accept(const masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void common_odb_options::accept(masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void common_odb_options::accept(const masd::dogen::coding::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void common_odb_options::accept(masd::dogen::coding::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void common_odb_options::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::generation::cpp::fabric::common_odb_options\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"sql_name_case\": " << "\"" << tidy_up_string(sql_name_case_) << "\"" << ", "
      << "\"databases\": " << databases_
      << " }";
}

void common_odb_options::swap(common_odb_options& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(sql_name_case_, other.sql_name_case_);
    swap(databases_, other.databases_);
}

bool common_odb_options::equals(const masd::dogen::coding::meta_model::element& other) const {
    const common_odb_options* const p(dynamic_cast<const common_odb_options* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool common_odb_options::operator==(const common_odb_options& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        sql_name_case_ == rhs.sql_name_case_ &&
        databases_ == rhs.databases_;
}

common_odb_options& common_odb_options::operator=(common_odb_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& common_odb_options::sql_name_case() const {
    return sql_name_case_;
}

std::string& common_odb_options::sql_name_case() {
    return sql_name_case_;
}

void common_odb_options::sql_name_case(const std::string& v) {
    sql_name_case_ = v;
}

void common_odb_options::sql_name_case(const std::string&& v) {
    sql_name_case_ = std::move(v);
}

const std::list<std::string>& common_odb_options::databases() const {
    return databases_;
}

std::list<std::string>& common_odb_options::databases() {
    return databases_;
}

void common_odb_options::databases(const std::list<std::string>& v) {
    databases_ = v;
}

void common_odb_options::databases(const std::list<std::string>&& v) {
    databases_ = std::move(v);
}

}
