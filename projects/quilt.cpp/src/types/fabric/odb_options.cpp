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
#include "dogen/yarn/io/letter_cases_io.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"

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

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::yarn::letter_cases>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

odb_options::odb_options(odb_options&& rhs)
    : dogen::yarn::element(
        std::forward<dogen::yarn::element>(rhs)),
      databases_(std::move(rhs.databases_)),
      letter_case_(std::move(rhs.letter_case_)),
      odb_include_directory_path_(std::move(rhs.odb_include_directory_path_)),
      types_include_directory_path_(std::move(rhs.types_include_directory_path_)),
      header_guard_prefix_(std::move(rhs.header_guard_prefix_)) { }

odb_options::odb_options(
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::vector<std::string>& stereotypes,
    const bool is_element_extension,
    const std::list<std::string>& databases,
    const boost::optional<dogen::yarn::letter_cases>& letter_case,
    const std::string& odb_include_directory_path,
    const std::string& types_include_directory_path,
    const std::string& header_guard_prefix)
    : dogen::yarn::element(
      documentation,
      annotation,
      name,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      is_element_extension),
      databases_(databases),
      letter_case_(letter_case),
      odb_include_directory_path_(odb_include_directory_path),
      types_include_directory_path_(types_include_directory_path),
      header_guard_prefix_(header_guard_prefix) { }

void odb_options::accept(const dogen::yarn::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void odb_options::accept(dogen::yarn::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void odb_options::accept(const dogen::yarn::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void odb_options::accept(dogen::yarn::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void odb_options::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::fabric::odb_options\"" << ", "
      << "\"__parent_0__\": ";
    dogen::yarn::element::to_stream(s);
    s << ", "
      << "\"databases\": " << databases_ << ", "
      << "\"letter_case\": " << letter_case_ << ", "
      << "\"odb_include_directory_path\": " << "\"" << tidy_up_string(odb_include_directory_path_) << "\"" << ", "
      << "\"types_include_directory_path\": " << "\"" << tidy_up_string(types_include_directory_path_) << "\"" << ", "
      << "\"header_guard_prefix\": " << "\"" << tidy_up_string(header_guard_prefix_) << "\""
      << " }";
}

void odb_options::swap(odb_options& other) noexcept {
    dogen::yarn::element::swap(other);

    using std::swap;
    swap(databases_, other.databases_);
    swap(letter_case_, other.letter_case_);
    swap(odb_include_directory_path_, other.odb_include_directory_path_);
    swap(types_include_directory_path_, other.types_include_directory_path_);
    swap(header_guard_prefix_, other.header_guard_prefix_);
}

bool odb_options::equals(const dogen::yarn::element& other) const {
    const odb_options* const p(dynamic_cast<const odb_options* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool odb_options::operator==(const odb_options& rhs) const {
    return dogen::yarn::element::compare(rhs) &&
        databases_ == rhs.databases_ &&
        letter_case_ == rhs.letter_case_ &&
        odb_include_directory_path_ == rhs.odb_include_directory_path_ &&
        types_include_directory_path_ == rhs.types_include_directory_path_ &&
        header_guard_prefix_ == rhs.header_guard_prefix_;
}

odb_options& odb_options::operator=(odb_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& odb_options::databases() const {
    return databases_;
}

std::list<std::string>& odb_options::databases() {
    return databases_;
}

void odb_options::databases(const std::list<std::string>& v) {
    databases_ = v;
}

void odb_options::databases(const std::list<std::string>&& v) {
    databases_ = std::move(v);
}

const boost::optional<dogen::yarn::letter_cases>& odb_options::letter_case() const {
    return letter_case_;
}

boost::optional<dogen::yarn::letter_cases>& odb_options::letter_case() {
    return letter_case_;
}

void odb_options::letter_case(const boost::optional<dogen::yarn::letter_cases>& v) {
    letter_case_ = v;
}

void odb_options::letter_case(const boost::optional<dogen::yarn::letter_cases>&& v) {
    letter_case_ = std::move(v);
}

const std::string& odb_options::odb_include_directory_path() const {
    return odb_include_directory_path_;
}

std::string& odb_options::odb_include_directory_path() {
    return odb_include_directory_path_;
}

void odb_options::odb_include_directory_path(const std::string& v) {
    odb_include_directory_path_ = v;
}

void odb_options::odb_include_directory_path(const std::string&& v) {
    odb_include_directory_path_ = std::move(v);
}

const std::string& odb_options::types_include_directory_path() const {
    return types_include_directory_path_;
}

std::string& odb_options::types_include_directory_path() {
    return types_include_directory_path_;
}

void odb_options::types_include_directory_path(const std::string& v) {
    types_include_directory_path_ = v;
}

void odb_options::types_include_directory_path(const std::string&& v) {
    types_include_directory_path_ = std::move(v);
}

const std::string& odb_options::header_guard_prefix() const {
    return header_guard_prefix_;
}

std::string& odb_options::header_guard_prefix() {
    return header_guard_prefix_;
}

void odb_options::header_guard_prefix(const std::string& v) {
    header_guard_prefix_ = v;
}

void odb_options::header_guard_prefix(const std::string&& v) {
    header_guard_prefix_ = std::move(v);
}

} } } }
