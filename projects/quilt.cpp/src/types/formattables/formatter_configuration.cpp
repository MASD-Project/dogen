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
#include "dogen/quilt.cpp/types/formattables/formatter_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

formatter_configuration::formatter_configuration()
    : enabled_(static_cast<bool>(0)) { }

formatter_configuration::formatter_configuration(formatter_configuration&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      file_path_(std::move(rhs.file_path_)),
      header_guard_(std::move(rhs.header_guard_)),
      inclusion_dependencies_(std::move(rhs.inclusion_dependencies_)),
      opaque_configuration_(std::move(rhs.opaque_configuration_)) { }

formatter_configuration::formatter_configuration(
    const bool enabled,
    const boost::filesystem::path& file_path,
    const std::string& header_guard,
    const std::list<std::string>& inclusion_dependencies,
    const dogen::quilt::cpp::formattables::opaque_configuration& opaque_configuration)
    : enabled_(enabled),
      file_path_(file_path),
      header_guard_(header_guard),
      inclusion_dependencies_(inclusion_dependencies),
      opaque_configuration_(opaque_configuration) { }

void formatter_configuration::swap(formatter_configuration& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(file_path_, other.file_path_);
    swap(header_guard_, other.header_guard_);
    swap(inclusion_dependencies_, other.inclusion_dependencies_);
    swap(opaque_configuration_, other.opaque_configuration_);
}

bool formatter_configuration::operator==(const formatter_configuration& rhs) const {
    return enabled_ == rhs.enabled_ &&
        file_path_ == rhs.file_path_ &&
        header_guard_ == rhs.header_guard_ &&
        inclusion_dependencies_ == rhs.inclusion_dependencies_ &&
        opaque_configuration_ == rhs.opaque_configuration_;
}

formatter_configuration& formatter_configuration::operator=(formatter_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool formatter_configuration::enabled() const {
    return enabled_;
}

void formatter_configuration::enabled(const bool v) {
    enabled_ = v;
}

const boost::filesystem::path& formatter_configuration::file_path() const {
    return file_path_;
}

boost::filesystem::path& formatter_configuration::file_path() {
    return file_path_;
}

void formatter_configuration::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void formatter_configuration::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const std::string& formatter_configuration::header_guard() const {
    return header_guard_;
}

std::string& formatter_configuration::header_guard() {
    return header_guard_;
}

void formatter_configuration::header_guard(const std::string& v) {
    header_guard_ = v;
}

void formatter_configuration::header_guard(const std::string&& v) {
    header_guard_ = std::move(v);
}

const std::list<std::string>& formatter_configuration::inclusion_dependencies() const {
    return inclusion_dependencies_;
}

std::list<std::string>& formatter_configuration::inclusion_dependencies() {
    return inclusion_dependencies_;
}

void formatter_configuration::inclusion_dependencies(const std::list<std::string>& v) {
    inclusion_dependencies_ = v;
}

void formatter_configuration::inclusion_dependencies(const std::list<std::string>&& v) {
    inclusion_dependencies_ = std::move(v);
}

const dogen::quilt::cpp::formattables::opaque_configuration& formatter_configuration::opaque_configuration() const {
    return opaque_configuration_;
}

dogen::quilt::cpp::formattables::opaque_configuration& formatter_configuration::opaque_configuration() {
    return opaque_configuration_;
}

void formatter_configuration::opaque_configuration(const dogen::quilt::cpp::formattables::opaque_configuration& v) {
    opaque_configuration_ = v;
}

void formatter_configuration::opaque_configuration(const dogen::quilt::cpp::formattables::opaque_configuration&& v) {
    opaque_configuration_ = std::move(v);
}

} } } }
