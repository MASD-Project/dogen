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
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"

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

cmakelists::cmakelists(cmakelists&& rhs)
    : dogen::yarn::element(
        std::forward<dogen::yarn::element>(rhs)),
      include_directory_name_(std::move(rhs.include_directory_name_)),
      odb_include_directory_path_(std::move(rhs.odb_include_directory_path_)),
      odb_source_directory_path_(std::move(rhs.odb_source_directory_path_)),
      odb_options_file_path_(std::move(rhs.odb_options_file_path_)),
      types_include_directory_path_(std::move(rhs.types_include_directory_path_)) { }

cmakelists::cmakelists(
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::yarn::name& name,
    const dogen::yarn::origin_types origin_type,
    const boost::optional<dogen::yarn::name>& contained_by,
    const bool in_global_module,
    const std::vector<std::string>& stereotypes,
    const bool is_element_extension,
    const std::string& include_directory_name,
    const boost::filesystem::path& odb_include_directory_path,
    const boost::filesystem::path& odb_source_directory_path,
    const boost::filesystem::path& odb_options_file_path,
    const boost::filesystem::path& types_include_directory_path)
    : dogen::yarn::element(
      documentation,
      annotation,
      name,
      origin_type,
      contained_by,
      in_global_module,
      stereotypes,
      is_element_extension),
      include_directory_name_(include_directory_name),
      odb_include_directory_path_(odb_include_directory_path),
      odb_source_directory_path_(odb_source_directory_path),
      odb_options_file_path_(odb_options_file_path),
      types_include_directory_path_(types_include_directory_path) { }

void cmakelists::accept(const dogen::yarn::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::accept(dogen::yarn::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void cmakelists::accept(const dogen::yarn::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::accept(dogen::yarn::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::fabric::cmakelists\"" << ", "
      << "\"__parent_0__\": ";
    dogen::yarn::element::to_stream(s);
    s << ", "
      << "\"include_directory_name\": " << "\"" << tidy_up_string(include_directory_name_) << "\"" << ", "
      << "\"odb_include_directory_path\": " << "\"" << odb_include_directory_path_.generic_string() << "\"" << ", "
      << "\"odb_source_directory_path\": " << "\"" << odb_source_directory_path_.generic_string() << "\"" << ", "
      << "\"odb_options_file_path\": " << "\"" << odb_options_file_path_.generic_string() << "\"" << ", "
      << "\"types_include_directory_path\": " << "\"" << types_include_directory_path_.generic_string() << "\""
      << " }";
}

void cmakelists::swap(cmakelists& other) noexcept {
    dogen::yarn::element::swap(other);

    using std::swap;
    swap(include_directory_name_, other.include_directory_name_);
    swap(odb_include_directory_path_, other.odb_include_directory_path_);
    swap(odb_source_directory_path_, other.odb_source_directory_path_);
    swap(odb_options_file_path_, other.odb_options_file_path_);
    swap(types_include_directory_path_, other.types_include_directory_path_);
}

bool cmakelists::equals(const dogen::yarn::element& other) const {
    const cmakelists* const p(dynamic_cast<const cmakelists* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cmakelists::operator==(const cmakelists& rhs) const {
    return dogen::yarn::element::compare(rhs) &&
        include_directory_name_ == rhs.include_directory_name_ &&
        odb_include_directory_path_ == rhs.odb_include_directory_path_ &&
        odb_source_directory_path_ == rhs.odb_source_directory_path_ &&
        odb_options_file_path_ == rhs.odb_options_file_path_ &&
        types_include_directory_path_ == rhs.types_include_directory_path_;
}

cmakelists& cmakelists::operator=(cmakelists other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& cmakelists::include_directory_name() const {
    return include_directory_name_;
}

std::string& cmakelists::include_directory_name() {
    return include_directory_name_;
}

void cmakelists::include_directory_name(const std::string& v) {
    include_directory_name_ = v;
}

void cmakelists::include_directory_name(const std::string&& v) {
    include_directory_name_ = std::move(v);
}

const boost::filesystem::path& cmakelists::odb_include_directory_path() const {
    return odb_include_directory_path_;
}

boost::filesystem::path& cmakelists::odb_include_directory_path() {
    return odb_include_directory_path_;
}

void cmakelists::odb_include_directory_path(const boost::filesystem::path& v) {
    odb_include_directory_path_ = v;
}

void cmakelists::odb_include_directory_path(const boost::filesystem::path&& v) {
    odb_include_directory_path_ = std::move(v);
}

const boost::filesystem::path& cmakelists::odb_source_directory_path() const {
    return odb_source_directory_path_;
}

boost::filesystem::path& cmakelists::odb_source_directory_path() {
    return odb_source_directory_path_;
}

void cmakelists::odb_source_directory_path(const boost::filesystem::path& v) {
    odb_source_directory_path_ = v;
}

void cmakelists::odb_source_directory_path(const boost::filesystem::path&& v) {
    odb_source_directory_path_ = std::move(v);
}

const boost::filesystem::path& cmakelists::odb_options_file_path() const {
    return odb_options_file_path_;
}

boost::filesystem::path& cmakelists::odb_options_file_path() {
    return odb_options_file_path_;
}

void cmakelists::odb_options_file_path(const boost::filesystem::path& v) {
    odb_options_file_path_ = v;
}

void cmakelists::odb_options_file_path(const boost::filesystem::path&& v) {
    odb_options_file_path_ = std::move(v);
}

const boost::filesystem::path& cmakelists::types_include_directory_path() const {
    return types_include_directory_path_;
}

boost::filesystem::path& cmakelists::types_include_directory_path() {
    return types_include_directory_path_;
}

void cmakelists::types_include_directory_path(const boost::filesystem::path& v) {
    types_include_directory_path_ = v;
}

void cmakelists::types_include_directory_path(const boost::filesystem::path&& v) {
    types_include_directory_path_ = std::move(v);
}

} } } }
