/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/specialized_property_sheet.hpp"

namespace dogen {
namespace cpp {

specialized_property_sheet::specialized_property_sheet()
    : generate_header_guards_(static_cast<bool>(0)),
      split_project_(static_cast<bool>(0)) { }

specialized_property_sheet::specialized_property_sheet(
    const bool generate_header_guards,
    const bool split_project,
    const std::string& source_directory,
    const std::string& include_directory,
    const std::string& header_file_extension,
    const std::string& implementation_file_extension,
    const std::string& forward_declaration_postfix)
    : generate_header_guards_(generate_header_guards),
      split_project_(split_project),
      source_directory_(source_directory),
      include_directory_(include_directory),
      header_file_extension_(header_file_extension),
      implementation_file_extension_(implementation_file_extension),
      forward_declaration_postfix_(forward_declaration_postfix) { }

void specialized_property_sheet::swap(specialized_property_sheet& other) noexcept {
    using std::swap;
    swap(generate_header_guards_, other.generate_header_guards_);
    swap(split_project_, other.split_project_);
    swap(source_directory_, other.source_directory_);
    swap(include_directory_, other.include_directory_);
    swap(header_file_extension_, other.header_file_extension_);
    swap(implementation_file_extension_, other.implementation_file_extension_);
    swap(forward_declaration_postfix_, other.forward_declaration_postfix_);
}

bool specialized_property_sheet::operator==(const specialized_property_sheet& rhs) const {
    return generate_header_guards_ == rhs.generate_header_guards_ &&
        split_project_ == rhs.split_project_ &&
        source_directory_ == rhs.source_directory_ &&
        include_directory_ == rhs.include_directory_ &&
        header_file_extension_ == rhs.header_file_extension_ &&
        implementation_file_extension_ == rhs.implementation_file_extension_ &&
        forward_declaration_postfix_ == rhs.forward_declaration_postfix_;
}

specialized_property_sheet& specialized_property_sheet::operator=(specialized_property_sheet other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool specialized_property_sheet::generate_header_guards() const {
    return generate_header_guards_;
}

void specialized_property_sheet::generate_header_guards(const bool v) {
    generate_header_guards_ = v;
}

bool specialized_property_sheet::split_project() const {
    return split_project_;
}

void specialized_property_sheet::split_project(const bool v) {
    split_project_ = v;
}

const std::string& specialized_property_sheet::source_directory() const {
    return source_directory_;
}

std::string& specialized_property_sheet::source_directory() {
    return source_directory_;
}

void specialized_property_sheet::source_directory(const std::string& v) {
    source_directory_ = v;
}

void specialized_property_sheet::source_directory(const std::string&& v) {
    source_directory_ = std::move(v);
}

const std::string& specialized_property_sheet::include_directory() const {
    return include_directory_;
}

std::string& specialized_property_sheet::include_directory() {
    return include_directory_;
}

void specialized_property_sheet::include_directory(const std::string& v) {
    include_directory_ = v;
}

void specialized_property_sheet::include_directory(const std::string&& v) {
    include_directory_ = std::move(v);
}

const std::string& specialized_property_sheet::header_file_extension() const {
    return header_file_extension_;
}

std::string& specialized_property_sheet::header_file_extension() {
    return header_file_extension_;
}

void specialized_property_sheet::header_file_extension(const std::string& v) {
    header_file_extension_ = v;
}

void specialized_property_sheet::header_file_extension(const std::string&& v) {
    header_file_extension_ = std::move(v);
}

const std::string& specialized_property_sheet::implementation_file_extension() const {
    return implementation_file_extension_;
}

std::string& specialized_property_sheet::implementation_file_extension() {
    return implementation_file_extension_;
}

void specialized_property_sheet::implementation_file_extension(const std::string& v) {
    implementation_file_extension_ = v;
}

void specialized_property_sheet::implementation_file_extension(const std::string&& v) {
    implementation_file_extension_ = std::move(v);
}

const std::string& specialized_property_sheet::forward_declaration_postfix() const {
    return forward_declaration_postfix_;
}

std::string& specialized_property_sheet::forward_declaration_postfix() {
    return forward_declaration_postfix_;
}

void specialized_property_sheet::forward_declaration_postfix(const std::string& v) {
    forward_declaration_postfix_ = v;
}

void specialized_property_sheet::forward_declaration_postfix(const std::string&& v) {
    forward_declaration_postfix_ = std::move(v);
}

} }