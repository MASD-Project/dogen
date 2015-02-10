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
#include "dogen/cpp/types/formatters/file_details.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

file_details::file_details()
    : split_project_(static_cast<bool>(0)),
      file_type_(static_cast<dogen::cpp::formatters::file_types>(0)) { }

file_details::file_details(file_details&& rhs)
    : split_project_(std::move(rhs.split_project_)),
      file_type_(std::move(rhs.file_type_)),
      facet_directory_(std::move(rhs.facet_directory_)),
      extension_(std::move(rhs.extension_)),
      facet_postfix_(std::move(rhs.facet_postfix_)),
      formatter_postfix_(std::move(rhs.formatter_postfix_)),
      project_directory_(std::move(rhs.project_directory_)),
      source_directory_(std::move(rhs.source_directory_)),
      include_directory_(std::move(rhs.include_directory_)) { }

file_details::file_details(
    const bool split_project,
    const dogen::cpp::formatters::file_types& file_type,
    const std::string& facet_directory,
    const std::string& extension,
    const std::string& facet_postfix,
    const std::string& formatter_postfix,
    const boost::filesystem::path& project_directory,
    const boost::filesystem::path& source_directory,
    const boost::filesystem::path& include_directory)
    : split_project_(split_project),
      file_type_(file_type),
      facet_directory_(facet_directory),
      extension_(extension),
      facet_postfix_(facet_postfix),
      formatter_postfix_(formatter_postfix),
      project_directory_(project_directory),
      source_directory_(source_directory),
      include_directory_(include_directory) { }

void file_details::swap(file_details& other) noexcept {
    using std::swap;
    swap(split_project_, other.split_project_);
    swap(file_type_, other.file_type_);
    swap(facet_directory_, other.facet_directory_);
    swap(extension_, other.extension_);
    swap(facet_postfix_, other.facet_postfix_);
    swap(formatter_postfix_, other.formatter_postfix_);
    swap(project_directory_, other.project_directory_);
    swap(source_directory_, other.source_directory_);
    swap(include_directory_, other.include_directory_);
}

bool file_details::operator==(const file_details& rhs) const {
    return split_project_ == rhs.split_project_ &&
        file_type_ == rhs.file_type_ &&
        facet_directory_ == rhs.facet_directory_ &&
        extension_ == rhs.extension_ &&
        facet_postfix_ == rhs.facet_postfix_ &&
        formatter_postfix_ == rhs.formatter_postfix_ &&
        project_directory_ == rhs.project_directory_ &&
        source_directory_ == rhs.source_directory_ &&
        include_directory_ == rhs.include_directory_;
}

file_details& file_details::operator=(file_details other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool file_details::split_project() const {
    return split_project_;
}

void file_details::split_project(const bool v) {
    split_project_ = v;
}

dogen::cpp::formatters::file_types file_details::file_type() const {
    return file_type_;
}

void file_details::file_type(const dogen::cpp::formatters::file_types& v) {
    file_type_ = v;
}

const std::string& file_details::facet_directory() const {
    return facet_directory_;
}

std::string& file_details::facet_directory() {
    return facet_directory_;
}

void file_details::facet_directory(const std::string& v) {
    facet_directory_ = v;
}

void file_details::facet_directory(const std::string&& v) {
    facet_directory_ = std::move(v);
}

const std::string& file_details::extension() const {
    return extension_;
}

std::string& file_details::extension() {
    return extension_;
}

void file_details::extension(const std::string& v) {
    extension_ = v;
}

void file_details::extension(const std::string&& v) {
    extension_ = std::move(v);
}

const std::string& file_details::facet_postfix() const {
    return facet_postfix_;
}

std::string& file_details::facet_postfix() {
    return facet_postfix_;
}

void file_details::facet_postfix(const std::string& v) {
    facet_postfix_ = v;
}

void file_details::facet_postfix(const std::string&& v) {
    facet_postfix_ = std::move(v);
}

const std::string& file_details::formatter_postfix() const {
    return formatter_postfix_;
}

std::string& file_details::formatter_postfix() {
    return formatter_postfix_;
}

void file_details::formatter_postfix(const std::string& v) {
    formatter_postfix_ = v;
}

void file_details::formatter_postfix(const std::string&& v) {
    formatter_postfix_ = std::move(v);
}

const boost::filesystem::path& file_details::project_directory() const {
    return project_directory_;
}

boost::filesystem::path& file_details::project_directory() {
    return project_directory_;
}

void file_details::project_directory(const boost::filesystem::path& v) {
    project_directory_ = v;
}

void file_details::project_directory(const boost::filesystem::path&& v) {
    project_directory_ = std::move(v);
}

const boost::filesystem::path& file_details::source_directory() const {
    return source_directory_;
}

boost::filesystem::path& file_details::source_directory() {
    return source_directory_;
}

void file_details::source_directory(const boost::filesystem::path& v) {
    source_directory_ = v;
}

void file_details::source_directory(const boost::filesystem::path&& v) {
    source_directory_ = std::move(v);
}

const boost::filesystem::path& file_details::include_directory() const {
    return include_directory_;
}

boost::filesystem::path& file_details::include_directory() {
    return include_directory_;
}

void file_details::include_directory(const boost::filesystem::path& v) {
    include_directory_ = v;
}

void file_details::include_directory(const boost::filesystem::path&& v) {
    include_directory_ = std::move(v);
}

} } }