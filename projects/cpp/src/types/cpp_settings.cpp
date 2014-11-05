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
#include "dogen/cpp/types/cpp_settings.hpp"

namespace dogen {
namespace cpp {

cpp_settings::cpp_settings()
    : enabled_(static_cast<bool>(0)),
      split_project_(static_cast<bool>(0)),
      enable_facet_folders_(static_cast<bool>(0)),
      enable_unique_file_names_(static_cast<bool>(0)) { }

cpp_settings::cpp_settings(
    const bool enabled,
    const bool split_project,
    const std::string& source_directory,
    const std::string& include_directory,
    const std::string& header_file_extension,
    const std::string& implementation_file_extension,
    const bool enable_facet_folders,
    const bool enable_unique_file_names)
    : enabled_(enabled),
      split_project_(split_project),
      source_directory_(source_directory),
      include_directory_(include_directory),
      header_file_extension_(header_file_extension),
      implementation_file_extension_(implementation_file_extension),
      enable_facet_folders_(enable_facet_folders),
      enable_unique_file_names_(enable_unique_file_names) { }

void cpp_settings::swap(cpp_settings& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(split_project_, other.split_project_);
    swap(source_directory_, other.source_directory_);
    swap(include_directory_, other.include_directory_);
    swap(header_file_extension_, other.header_file_extension_);
    swap(implementation_file_extension_, other.implementation_file_extension_);
    swap(enable_facet_folders_, other.enable_facet_folders_);
    swap(enable_unique_file_names_, other.enable_unique_file_names_);
}

bool cpp_settings::operator==(const cpp_settings& rhs) const {
    return enabled_ == rhs.enabled_ &&
        split_project_ == rhs.split_project_ &&
        source_directory_ == rhs.source_directory_ &&
        include_directory_ == rhs.include_directory_ &&
        header_file_extension_ == rhs.header_file_extension_ &&
        implementation_file_extension_ == rhs.implementation_file_extension_ &&
        enable_facet_folders_ == rhs.enable_facet_folders_ &&
        enable_unique_file_names_ == rhs.enable_unique_file_names_;
}

cpp_settings& cpp_settings::operator=(cpp_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_settings::enabled() const {
    return enabled_;
}

void cpp_settings::enabled(const bool v) {
    enabled_ = v;
}

bool cpp_settings::split_project() const {
    return split_project_;
}

void cpp_settings::split_project(const bool v) {
    split_project_ = v;
}

const std::string& cpp_settings::source_directory() const {
    return source_directory_;
}

std::string& cpp_settings::source_directory() {
    return source_directory_;
}

void cpp_settings::source_directory(const std::string& v) {
    source_directory_ = v;
}

void cpp_settings::source_directory(const std::string&& v) {
    source_directory_ = std::move(v);
}

const std::string& cpp_settings::include_directory() const {
    return include_directory_;
}

std::string& cpp_settings::include_directory() {
    return include_directory_;
}

void cpp_settings::include_directory(const std::string& v) {
    include_directory_ = v;
}

void cpp_settings::include_directory(const std::string&& v) {
    include_directory_ = std::move(v);
}

const std::string& cpp_settings::header_file_extension() const {
    return header_file_extension_;
}

std::string& cpp_settings::header_file_extension() {
    return header_file_extension_;
}

void cpp_settings::header_file_extension(const std::string& v) {
    header_file_extension_ = v;
}

void cpp_settings::header_file_extension(const std::string&& v) {
    header_file_extension_ = std::move(v);
}

const std::string& cpp_settings::implementation_file_extension() const {
    return implementation_file_extension_;
}

std::string& cpp_settings::implementation_file_extension() {
    return implementation_file_extension_;
}

void cpp_settings::implementation_file_extension(const std::string& v) {
    implementation_file_extension_ = v;
}

void cpp_settings::implementation_file_extension(const std::string&& v) {
    implementation_file_extension_ = std::move(v);
}

bool cpp_settings::enable_facet_folders() const {
    return enable_facet_folders_;
}

void cpp_settings::enable_facet_folders(const bool v) {
    enable_facet_folders_ = v;
}

bool cpp_settings::enable_unique_file_names() const {
    return enable_unique_file_names_;
}

void cpp_settings::enable_unique_file_names(const bool v) {
    enable_unique_file_names_ = v;
}

} }