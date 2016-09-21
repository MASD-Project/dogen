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
#include "dogen/quilt.cpp/types/annotations/path_annotations.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

path_annotations::path_annotations()
    : file_type_(static_cast<dogen::quilt::cpp::formatters::file_types>(0)),
      disable_facet_directories_(static_cast<bool>(0)) { }

path_annotations::path_annotations(
    const dogen::quilt::cpp::formatters::file_types file_type,
    const std::string& facet_directory,
    const std::string& facet_postfix,
    const std::string& formatter_postfix,
    const std::string& include_directory_name,
    const std::string& source_directory_name,
    const bool disable_facet_directories,
    const std::string& header_file_extension,
    const std::string& implementation_file_extension)
    : file_type_(file_type),
      facet_directory_(facet_directory),
      facet_postfix_(facet_postfix),
      formatter_postfix_(formatter_postfix),
      include_directory_name_(include_directory_name),
      source_directory_name_(source_directory_name),
      disable_facet_directories_(disable_facet_directories),
      header_file_extension_(header_file_extension),
      implementation_file_extension_(implementation_file_extension) { }

void path_annotations::swap(path_annotations& other) noexcept {
    using std::swap;
    swap(file_type_, other.file_type_);
    swap(facet_directory_, other.facet_directory_);
    swap(facet_postfix_, other.facet_postfix_);
    swap(formatter_postfix_, other.formatter_postfix_);
    swap(include_directory_name_, other.include_directory_name_);
    swap(source_directory_name_, other.source_directory_name_);
    swap(disable_facet_directories_, other.disable_facet_directories_);
    swap(header_file_extension_, other.header_file_extension_);
    swap(implementation_file_extension_, other.implementation_file_extension_);
}

bool path_annotations::operator==(const path_annotations& rhs) const {
    return file_type_ == rhs.file_type_ &&
        facet_directory_ == rhs.facet_directory_ &&
        facet_postfix_ == rhs.facet_postfix_ &&
        formatter_postfix_ == rhs.formatter_postfix_ &&
        include_directory_name_ == rhs.include_directory_name_ &&
        source_directory_name_ == rhs.source_directory_name_ &&
        disable_facet_directories_ == rhs.disable_facet_directories_ &&
        header_file_extension_ == rhs.header_file_extension_ &&
        implementation_file_extension_ == rhs.implementation_file_extension_;
}

path_annotations& path_annotations::operator=(path_annotations other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::quilt::cpp::formatters::file_types path_annotations::file_type() const {
    return file_type_;
}

void path_annotations::file_type(const dogen::quilt::cpp::formatters::file_types v) {
    file_type_ = v;
}

const std::string& path_annotations::facet_directory() const {
    return facet_directory_;
}

std::string& path_annotations::facet_directory() {
    return facet_directory_;
}

void path_annotations::facet_directory(const std::string& v) {
    facet_directory_ = v;
}

void path_annotations::facet_directory(const std::string&& v) {
    facet_directory_ = std::move(v);
}

const std::string& path_annotations::facet_postfix() const {
    return facet_postfix_;
}

std::string& path_annotations::facet_postfix() {
    return facet_postfix_;
}

void path_annotations::facet_postfix(const std::string& v) {
    facet_postfix_ = v;
}

void path_annotations::facet_postfix(const std::string&& v) {
    facet_postfix_ = std::move(v);
}

const std::string& path_annotations::formatter_postfix() const {
    return formatter_postfix_;
}

std::string& path_annotations::formatter_postfix() {
    return formatter_postfix_;
}

void path_annotations::formatter_postfix(const std::string& v) {
    formatter_postfix_ = v;
}

void path_annotations::formatter_postfix(const std::string&& v) {
    formatter_postfix_ = std::move(v);
}

const std::string& path_annotations::include_directory_name() const {
    return include_directory_name_;
}

std::string& path_annotations::include_directory_name() {
    return include_directory_name_;
}

void path_annotations::include_directory_name(const std::string& v) {
    include_directory_name_ = v;
}

void path_annotations::include_directory_name(const std::string&& v) {
    include_directory_name_ = std::move(v);
}

const std::string& path_annotations::source_directory_name() const {
    return source_directory_name_;
}

std::string& path_annotations::source_directory_name() {
    return source_directory_name_;
}

void path_annotations::source_directory_name(const std::string& v) {
    source_directory_name_ = v;
}

void path_annotations::source_directory_name(const std::string&& v) {
    source_directory_name_ = std::move(v);
}

bool path_annotations::disable_facet_directories() const {
    return disable_facet_directories_;
}

void path_annotations::disable_facet_directories(const bool v) {
    disable_facet_directories_ = v;
}

const std::string& path_annotations::header_file_extension() const {
    return header_file_extension_;
}

std::string& path_annotations::header_file_extension() {
    return header_file_extension_;
}

void path_annotations::header_file_extension(const std::string& v) {
    header_file_extension_ = v;
}

void path_annotations::header_file_extension(const std::string&& v) {
    header_file_extension_ = std::move(v);
}

const std::string& path_annotations::implementation_file_extension() const {
    return implementation_file_extension_;
}

std::string& path_annotations::implementation_file_extension() {
    return implementation_file_extension_;
}

void path_annotations::implementation_file_extension(const std::string& v) {
    implementation_file_extension_ = v;
}

void path_annotations::implementation_file_extension(const std::string&& v) {
    implementation_file_extension_ = std::move(v);
}

} } } }
