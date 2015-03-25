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
#include "dogen/cpp/types/settings/path_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

path_settings::path_settings()
    : split_project_(static_cast<bool>(0)),
      file_type_(static_cast<dogen::cpp::formatters::file_types>(0)),
      inclusion_delimiter_type_(static_cast<dogen::cpp::settings::inclusion_delimiter_types>(0)) { }

path_settings::path_settings(path_settings&& rhs)
    : split_project_(std::move(rhs.split_project_)),
      file_type_(std::move(rhs.file_type_)),
      facet_directory_(std::move(rhs.facet_directory_)),
      extension_(std::move(rhs.extension_)),
      facet_postfix_(std::move(rhs.facet_postfix_)),
      formatter_postfix_(std::move(rhs.formatter_postfix_)),
      project_directory_path_(std::move(rhs.project_directory_path_)),
      source_directory_path_(std::move(rhs.source_directory_path_)),
      include_directory_path_(std::move(rhs.include_directory_path_)),
      inclusion_path_(std::move(rhs.inclusion_path_)),
      inclusion_delimiter_type_(std::move(rhs.inclusion_delimiter_type_)),
      include_directory_name_(std::move(rhs.include_directory_name_)),
      source_directory_name_(std::move(rhs.source_directory_name_)) { }

path_settings::path_settings(
    const bool split_project,
    const dogen::cpp::formatters::file_types& file_type,
    const std::string& facet_directory,
    const std::string& extension,
    const std::string& facet_postfix,
    const std::string& formatter_postfix,
    const boost::filesystem::path& project_directory_path,
    const boost::filesystem::path& source_directory_path,
    const boost::filesystem::path& include_directory_path,
    const boost::filesystem::path& inclusion_path,
    const dogen::cpp::settings::inclusion_delimiter_types& inclusion_delimiter_type,
    const std::string& include_directory_name,
    const std::string& source_directory_name)
    : split_project_(split_project),
      file_type_(file_type),
      facet_directory_(facet_directory),
      extension_(extension),
      facet_postfix_(facet_postfix),
      formatter_postfix_(formatter_postfix),
      project_directory_path_(project_directory_path),
      source_directory_path_(source_directory_path),
      include_directory_path_(include_directory_path),
      inclusion_path_(inclusion_path),
      inclusion_delimiter_type_(inclusion_delimiter_type),
      include_directory_name_(include_directory_name),
      source_directory_name_(source_directory_name) { }

void path_settings::swap(path_settings& other) noexcept {
    using std::swap;
    swap(split_project_, other.split_project_);
    swap(file_type_, other.file_type_);
    swap(facet_directory_, other.facet_directory_);
    swap(extension_, other.extension_);
    swap(facet_postfix_, other.facet_postfix_);
    swap(formatter_postfix_, other.formatter_postfix_);
    swap(project_directory_path_, other.project_directory_path_);
    swap(source_directory_path_, other.source_directory_path_);
    swap(include_directory_path_, other.include_directory_path_);
    swap(inclusion_path_, other.inclusion_path_);
    swap(inclusion_delimiter_type_, other.inclusion_delimiter_type_);
    swap(include_directory_name_, other.include_directory_name_);
    swap(source_directory_name_, other.source_directory_name_);
}

bool path_settings::operator==(const path_settings& rhs) const {
    return split_project_ == rhs.split_project_ &&
        file_type_ == rhs.file_type_ &&
        facet_directory_ == rhs.facet_directory_ &&
        extension_ == rhs.extension_ &&
        facet_postfix_ == rhs.facet_postfix_ &&
        formatter_postfix_ == rhs.formatter_postfix_ &&
        project_directory_path_ == rhs.project_directory_path_ &&
        source_directory_path_ == rhs.source_directory_path_ &&
        include_directory_path_ == rhs.include_directory_path_ &&
        inclusion_path_ == rhs.inclusion_path_ &&
        inclusion_delimiter_type_ == rhs.inclusion_delimiter_type_ &&
        include_directory_name_ == rhs.include_directory_name_ &&
        source_directory_name_ == rhs.source_directory_name_;
}

path_settings& path_settings::operator=(path_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool path_settings::split_project() const {
    return split_project_;
}

void path_settings::split_project(const bool v) {
    split_project_ = v;
}

dogen::cpp::formatters::file_types path_settings::file_type() const {
    return file_type_;
}

void path_settings::file_type(const dogen::cpp::formatters::file_types& v) {
    file_type_ = v;
}

const std::string& path_settings::facet_directory() const {
    return facet_directory_;
}

std::string& path_settings::facet_directory() {
    return facet_directory_;
}

void path_settings::facet_directory(const std::string& v) {
    facet_directory_ = v;
}

void path_settings::facet_directory(const std::string&& v) {
    facet_directory_ = std::move(v);
}

const std::string& path_settings::extension() const {
    return extension_;
}

std::string& path_settings::extension() {
    return extension_;
}

void path_settings::extension(const std::string& v) {
    extension_ = v;
}

void path_settings::extension(const std::string&& v) {
    extension_ = std::move(v);
}

const std::string& path_settings::facet_postfix() const {
    return facet_postfix_;
}

std::string& path_settings::facet_postfix() {
    return facet_postfix_;
}

void path_settings::facet_postfix(const std::string& v) {
    facet_postfix_ = v;
}

void path_settings::facet_postfix(const std::string&& v) {
    facet_postfix_ = std::move(v);
}

const std::string& path_settings::formatter_postfix() const {
    return formatter_postfix_;
}

std::string& path_settings::formatter_postfix() {
    return formatter_postfix_;
}

void path_settings::formatter_postfix(const std::string& v) {
    formatter_postfix_ = v;
}

void path_settings::formatter_postfix(const std::string&& v) {
    formatter_postfix_ = std::move(v);
}

const boost::filesystem::path& path_settings::project_directory_path() const {
    return project_directory_path_;
}

boost::filesystem::path& path_settings::project_directory_path() {
    return project_directory_path_;
}

void path_settings::project_directory_path(const boost::filesystem::path& v) {
    project_directory_path_ = v;
}

void path_settings::project_directory_path(const boost::filesystem::path&& v) {
    project_directory_path_ = std::move(v);
}

const boost::filesystem::path& path_settings::source_directory_path() const {
    return source_directory_path_;
}

boost::filesystem::path& path_settings::source_directory_path() {
    return source_directory_path_;
}

void path_settings::source_directory_path(const boost::filesystem::path& v) {
    source_directory_path_ = v;
}

void path_settings::source_directory_path(const boost::filesystem::path&& v) {
    source_directory_path_ = std::move(v);
}

const boost::filesystem::path& path_settings::include_directory_path() const {
    return include_directory_path_;
}

boost::filesystem::path& path_settings::include_directory_path() {
    return include_directory_path_;
}

void path_settings::include_directory_path(const boost::filesystem::path& v) {
    include_directory_path_ = v;
}

void path_settings::include_directory_path(const boost::filesystem::path&& v) {
    include_directory_path_ = std::move(v);
}

const boost::filesystem::path& path_settings::inclusion_path() const {
    return inclusion_path_;
}

boost::filesystem::path& path_settings::inclusion_path() {
    return inclusion_path_;
}

void path_settings::inclusion_path(const boost::filesystem::path& v) {
    inclusion_path_ = v;
}

void path_settings::inclusion_path(const boost::filesystem::path&& v) {
    inclusion_path_ = std::move(v);
}

dogen::cpp::settings::inclusion_delimiter_types path_settings::inclusion_delimiter_type() const {
    return inclusion_delimiter_type_;
}

void path_settings::inclusion_delimiter_type(const dogen::cpp::settings::inclusion_delimiter_types& v) {
    inclusion_delimiter_type_ = v;
}

const std::string& path_settings::include_directory_name() const {
    return include_directory_name_;
}

std::string& path_settings::include_directory_name() {
    return include_directory_name_;
}

void path_settings::include_directory_name(const std::string& v) {
    include_directory_name_ = v;
}

void path_settings::include_directory_name(const std::string&& v) {
    include_directory_name_ = std::move(v);
}

const std::string& path_settings::source_directory_name() const {
    return source_directory_name_;
}

std::string& path_settings::source_directory_name() {
    return source_directory_name_;
}

void path_settings::source_directory_name(const std::string& v) {
    source_directory_name_ = v;
}

void path_settings::source_directory_name(const std::string&& v) {
    source_directory_name_ = std::move(v);
}

} } }