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
#include "dogen/cpp/types/settings/cpp_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

cpp_settings::cpp_settings()
    : enabled_(static_cast<bool>(0)),
      split_project_(static_cast<bool>(0)),
      enable_facet_folders_(static_cast<bool>(0)),
      enable_unique_file_names_(static_cast<bool>(0)) { }

cpp_settings::cpp_settings(cpp_settings&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      split_project_(std::move(rhs.split_project_)),
      source_directory_name_(std::move(rhs.source_directory_name_)),
      include_directory_name_(std::move(rhs.include_directory_name_)),
      header_file_extension_(std::move(rhs.header_file_extension_)),
      implementation_file_extension_(std::move(rhs.implementation_file_extension_)),
      enable_facet_folders_(std::move(rhs.enable_facet_folders_)),
      enable_unique_file_names_(std::move(rhs.enable_unique_file_names_)),
      project_directory_path_(std::move(rhs.project_directory_path_)),
      source_directory_path_(std::move(rhs.source_directory_path_)),
      include_directory_path_(std::move(rhs.include_directory_path_)) { }

cpp_settings::cpp_settings(
    const bool enabled,
    const bool split_project,
    const std::string& source_directory_name,
    const std::string& include_directory_name,
    const std::string& header_file_extension,
    const std::string& implementation_file_extension,
    const bool enable_facet_folders,
    const bool enable_unique_file_names,
    const boost::filesystem::path& project_directory_path,
    const boost::filesystem::path& source_directory_path,
    const boost::filesystem::path& include_directory_path)
    : enabled_(enabled),
      split_project_(split_project),
      source_directory_name_(source_directory_name),
      include_directory_name_(include_directory_name),
      header_file_extension_(header_file_extension),
      implementation_file_extension_(implementation_file_extension),
      enable_facet_folders_(enable_facet_folders),
      enable_unique_file_names_(enable_unique_file_names),
      project_directory_path_(project_directory_path),
      source_directory_path_(source_directory_path),
      include_directory_path_(include_directory_path) { }

void cpp_settings::swap(cpp_settings& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(split_project_, other.split_project_);
    swap(source_directory_name_, other.source_directory_name_);
    swap(include_directory_name_, other.include_directory_name_);
    swap(header_file_extension_, other.header_file_extension_);
    swap(implementation_file_extension_, other.implementation_file_extension_);
    swap(enable_facet_folders_, other.enable_facet_folders_);
    swap(enable_unique_file_names_, other.enable_unique_file_names_);
    swap(project_directory_path_, other.project_directory_path_);
    swap(source_directory_path_, other.source_directory_path_);
    swap(include_directory_path_, other.include_directory_path_);
}

bool cpp_settings::operator==(const cpp_settings& rhs) const {
    return enabled_ == rhs.enabled_ &&
        split_project_ == rhs.split_project_ &&
        source_directory_name_ == rhs.source_directory_name_ &&
        include_directory_name_ == rhs.include_directory_name_ &&
        header_file_extension_ == rhs.header_file_extension_ &&
        implementation_file_extension_ == rhs.implementation_file_extension_ &&
        enable_facet_folders_ == rhs.enable_facet_folders_ &&
        enable_unique_file_names_ == rhs.enable_unique_file_names_ &&
        project_directory_path_ == rhs.project_directory_path_ &&
        source_directory_path_ == rhs.source_directory_path_ &&
        include_directory_path_ == rhs.include_directory_path_;
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

const std::string& cpp_settings::source_directory_name() const {
    return source_directory_name_;
}

std::string& cpp_settings::source_directory_name() {
    return source_directory_name_;
}

void cpp_settings::source_directory_name(const std::string& v) {
    source_directory_name_ = v;
}

void cpp_settings::source_directory_name(const std::string&& v) {
    source_directory_name_ = std::move(v);
}

const std::string& cpp_settings::include_directory_name() const {
    return include_directory_name_;
}

std::string& cpp_settings::include_directory_name() {
    return include_directory_name_;
}

void cpp_settings::include_directory_name(const std::string& v) {
    include_directory_name_ = v;
}

void cpp_settings::include_directory_name(const std::string&& v) {
    include_directory_name_ = std::move(v);
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

const boost::filesystem::path& cpp_settings::project_directory_path() const {
    return project_directory_path_;
}

boost::filesystem::path& cpp_settings::project_directory_path() {
    return project_directory_path_;
}

void cpp_settings::project_directory_path(const boost::filesystem::path& v) {
    project_directory_path_ = v;
}

void cpp_settings::project_directory_path(const boost::filesystem::path&& v) {
    project_directory_path_ = std::move(v);
}

const boost::filesystem::path& cpp_settings::source_directory_path() const {
    return source_directory_path_;
}

boost::filesystem::path& cpp_settings::source_directory_path() {
    return source_directory_path_;
}

void cpp_settings::source_directory_path(const boost::filesystem::path& v) {
    source_directory_path_ = v;
}

void cpp_settings::source_directory_path(const boost::filesystem::path&& v) {
    source_directory_path_ = std::move(v);
}

const boost::filesystem::path& cpp_settings::include_directory_path() const {
    return include_directory_path_;
}

boost::filesystem::path& cpp_settings::include_directory_path() {
    return include_directory_path_;
}

void cpp_settings::include_directory_path(const boost::filesystem::path& v) {
    include_directory_path_ = v;
}

void cpp_settings::include_directory_path(const boost::filesystem::path&& v) {
    include_directory_path_ = std::move(v);
}

} } }