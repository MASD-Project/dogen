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
#include "dogen/cpp/types/settings/common_formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

common_formatter_settings::common_formatter_settings()
    : enabled_(static_cast<bool>(0)),
      supported_(static_cast<bool>(0)),
      inclusion_required_(static_cast<bool>(0)),
      inclusion_delimiter_type_(static_cast<dogen::cpp::settings::inclusion_delimiter_types>(0)) { }

common_formatter_settings::common_formatter_settings(common_formatter_settings&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      supported_(std::move(rhs.supported_)),
      file_path_(std::move(rhs.file_path_)),
      inclusion_required_(std::move(rhs.inclusion_required_)),
      inclusion_path_(std::move(rhs.inclusion_path_)),
      inclusion_delimiter_type_(std::move(rhs.inclusion_delimiter_type_)),
      inclusion_dependencies_(std::move(rhs.inclusion_dependencies_)),
      integrated_facets_(std::move(rhs.integrated_facets_)) { }

common_formatter_settings::common_formatter_settings(
    const bool enabled,
    const bool supported,
    const boost::filesystem::path& file_path,
    const bool inclusion_required,
    const boost::filesystem::path& inclusion_path,
    const dogen::cpp::settings::inclusion_delimiter_types& inclusion_delimiter_type,
    const std::list<dogen::cpp::settings::inclusion>& inclusion_dependencies,
    const std::set<std::string>& integrated_facets)
    : enabled_(enabled),
      supported_(supported),
      file_path_(file_path),
      inclusion_required_(inclusion_required),
      inclusion_path_(inclusion_path),
      inclusion_delimiter_type_(inclusion_delimiter_type),
      inclusion_dependencies_(inclusion_dependencies),
      integrated_facets_(integrated_facets) { }

void common_formatter_settings::swap(common_formatter_settings& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(supported_, other.supported_);
    swap(file_path_, other.file_path_);
    swap(inclusion_required_, other.inclusion_required_);
    swap(inclusion_path_, other.inclusion_path_);
    swap(inclusion_delimiter_type_, other.inclusion_delimiter_type_);
    swap(inclusion_dependencies_, other.inclusion_dependencies_);
    swap(integrated_facets_, other.integrated_facets_);
}

bool common_formatter_settings::operator==(const common_formatter_settings& rhs) const {
    return enabled_ == rhs.enabled_ &&
        supported_ == rhs.supported_ &&
        file_path_ == rhs.file_path_ &&
        inclusion_required_ == rhs.inclusion_required_ &&
        inclusion_path_ == rhs.inclusion_path_ &&
        inclusion_delimiter_type_ == rhs.inclusion_delimiter_type_ &&
        inclusion_dependencies_ == rhs.inclusion_dependencies_ &&
        integrated_facets_ == rhs.integrated_facets_;
}

common_formatter_settings& common_formatter_settings::operator=(common_formatter_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool common_formatter_settings::enabled() const {
    return enabled_;
}

void common_formatter_settings::enabled(const bool v) {
    enabled_ = v;
}

bool common_formatter_settings::supported() const {
    return supported_;
}

void common_formatter_settings::supported(const bool v) {
    supported_ = v;
}

const boost::filesystem::path& common_formatter_settings::file_path() const {
    return file_path_;
}

boost::filesystem::path& common_formatter_settings::file_path() {
    return file_path_;
}

void common_formatter_settings::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void common_formatter_settings::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

bool common_formatter_settings::inclusion_required() const {
    return inclusion_required_;
}

void common_formatter_settings::inclusion_required(const bool v) {
    inclusion_required_ = v;
}

const boost::filesystem::path& common_formatter_settings::inclusion_path() const {
    return inclusion_path_;
}

boost::filesystem::path& common_formatter_settings::inclusion_path() {
    return inclusion_path_;
}

void common_formatter_settings::inclusion_path(const boost::filesystem::path& v) {
    inclusion_path_ = v;
}

void common_formatter_settings::inclusion_path(const boost::filesystem::path&& v) {
    inclusion_path_ = std::move(v);
}

dogen::cpp::settings::inclusion_delimiter_types common_formatter_settings::inclusion_delimiter_type() const {
    return inclusion_delimiter_type_;
}

void common_formatter_settings::inclusion_delimiter_type(const dogen::cpp::settings::inclusion_delimiter_types& v) {
    inclusion_delimiter_type_ = v;
}

const std::list<dogen::cpp::settings::inclusion>& common_formatter_settings::inclusion_dependencies() const {
    return inclusion_dependencies_;
}

std::list<dogen::cpp::settings::inclusion>& common_formatter_settings::inclusion_dependencies() {
    return inclusion_dependencies_;
}

void common_formatter_settings::inclusion_dependencies(const std::list<dogen::cpp::settings::inclusion>& v) {
    inclusion_dependencies_ = v;
}

void common_formatter_settings::inclusion_dependencies(const std::list<dogen::cpp::settings::inclusion>&& v) {
    inclusion_dependencies_ = std::move(v);
}

const std::set<std::string>& common_formatter_settings::integrated_facets() const {
    return integrated_facets_;
}

std::set<std::string>& common_formatter_settings::integrated_facets() {
    return integrated_facets_;
}

void common_formatter_settings::integrated_facets(const std::set<std::string>& v) {
    integrated_facets_ = v;
}

void common_formatter_settings::integrated_facets(const std::set<std::string>&& v) {
    integrated_facets_ = std::move(v);
}

} } }