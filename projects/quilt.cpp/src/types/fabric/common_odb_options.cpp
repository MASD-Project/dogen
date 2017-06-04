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
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/fabric/common_odb_options.hpp"

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

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

common_odb_options::common_odb_options(
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::vector<std::string>& stereotypes,
    const bool is_element_extension,
    const dogen::yarn::element_properties& element_properties,
    const std::string& sql_name_case,
    const std::list<std::string>& databases)
    : dogen::yarn::element(
      documentation,
      annotation,
      name,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      is_element_extension,
      element_properties),
      sql_name_case_(sql_name_case),
      databases_(databases) { }

void common_odb_options::accept(const dogen::yarn::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void common_odb_options::accept(dogen::yarn::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void common_odb_options::accept(const dogen::yarn::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void common_odb_options::accept(dogen::yarn::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void common_odb_options::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::fabric::common_odb_options\"" << ", "
      << "\"__parent_0__\": ";
    dogen::yarn::element::to_stream(s);
    s << ", "
      << "\"sql_name_case\": " << "\"" << tidy_up_string(sql_name_case_) << "\"" << ", "
      << "\"databases\": " << databases_
      << " }";
}

void common_odb_options::swap(common_odb_options& other) noexcept {
    dogen::yarn::element::swap(other);

    using std::swap;
    swap(sql_name_case_, other.sql_name_case_);
    swap(databases_, other.databases_);
}

bool common_odb_options::equals(const dogen::yarn::element& other) const {
    const common_odb_options* const p(dynamic_cast<const common_odb_options* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool common_odb_options::operator==(const common_odb_options& rhs) const {
    return dogen::yarn::element::compare(rhs) &&
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

} } } }
