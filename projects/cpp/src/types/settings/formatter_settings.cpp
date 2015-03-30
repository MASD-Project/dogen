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
#include "dogen/cpp/types/settings/formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

formatter_settings::formatter_settings()
    : enabled_(static_cast<bool>(0)) { }

formatter_settings::formatter_settings(formatter_settings&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      file_path_(std::move(rhs.file_path_)),
      header_guard_(std::move(rhs.header_guard_)),
      inclusion_dependencies_(std::move(rhs.inclusion_dependencies_)),
      integrated_facets_(std::move(rhs.integrated_facets_)) { }

formatter_settings::formatter_settings(
    const bool enabled,
    const boost::filesystem::path& file_path,
    const boost::optional<std::string>& header_guard,
    const std::list<std::string>& inclusion_dependencies,
    const std::set<std::string>& integrated_facets)
    : enabled_(enabled),
      file_path_(file_path),
      header_guard_(header_guard),
      inclusion_dependencies_(inclusion_dependencies),
      integrated_facets_(integrated_facets) { }

void formatter_settings::swap(formatter_settings& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(file_path_, other.file_path_);
    swap(header_guard_, other.header_guard_);
    swap(inclusion_dependencies_, other.inclusion_dependencies_);
    swap(integrated_facets_, other.integrated_facets_);
}

bool formatter_settings::operator==(const formatter_settings& rhs) const {
    return enabled_ == rhs.enabled_ &&
        file_path_ == rhs.file_path_ &&
        header_guard_ == rhs.header_guard_ &&
        inclusion_dependencies_ == rhs.inclusion_dependencies_ &&
        integrated_facets_ == rhs.integrated_facets_;
}

formatter_settings& formatter_settings::operator=(formatter_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool formatter_settings::enabled() const {
    return enabled_;
}

void formatter_settings::enabled(const bool v) {
    enabled_ = v;
}

const boost::filesystem::path& formatter_settings::file_path() const {
    return file_path_;
}

boost::filesystem::path& formatter_settings::file_path() {
    return file_path_;
}

void formatter_settings::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void formatter_settings::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const boost::optional<std::string>& formatter_settings::header_guard() const {
    return header_guard_;
}

boost::optional<std::string>& formatter_settings::header_guard() {
    return header_guard_;
}

void formatter_settings::header_guard(const boost::optional<std::string>& v) {
    header_guard_ = v;
}

void formatter_settings::header_guard(const boost::optional<std::string>&& v) {
    header_guard_ = std::move(v);
}

const std::list<std::string>& formatter_settings::inclusion_dependencies() const {
    return inclusion_dependencies_;
}

std::list<std::string>& formatter_settings::inclusion_dependencies() {
    return inclusion_dependencies_;
}

void formatter_settings::inclusion_dependencies(const std::list<std::string>& v) {
    inclusion_dependencies_ = v;
}

void formatter_settings::inclusion_dependencies(const std::list<std::string>&& v) {
    inclusion_dependencies_ = std::move(v);
}

const std::set<std::string>& formatter_settings::integrated_facets() const {
    return integrated_facets_;
}

std::set<std::string>& formatter_settings::integrated_facets() {
    return integrated_facets_;
}

void formatter_settings::integrated_facets(const std::set<std::string>& v) {
    integrated_facets_ = v;
}

void formatter_settings::integrated_facets(const std::set<std::string>&& v) {
    integrated_facets_ = std::move(v);
}

} } }