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
#include "dogen.m2t.csharp/types/formattables/artefact_properties.hpp"

namespace dogen::m2t::csharp::formattables {

artefact_properties::artefact_properties()
    : enabled_(static_cast<bool>(0)),
      overwrite_(static_cast<bool>(0)) { }

artefact_properties::artefact_properties(artefact_properties&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      overwrite_(std::move(rhs.overwrite_)),
      file_path_(std::move(rhs.file_path_)),
      relative_path_(std::move(rhs.relative_path_)),
      using_dependencies_(std::move(rhs.using_dependencies_)) { }

artefact_properties::artefact_properties(
    const bool enabled,
    const bool overwrite,
    const boost::filesystem::path& file_path,
    const boost::filesystem::path& relative_path,
    const std::list<std::string>& using_dependencies)
    : enabled_(enabled),
      overwrite_(overwrite),
      file_path_(file_path),
      relative_path_(relative_path),
      using_dependencies_(using_dependencies) { }

void artefact_properties::swap(artefact_properties& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(overwrite_, other.overwrite_);
    swap(file_path_, other.file_path_);
    swap(relative_path_, other.relative_path_);
    swap(using_dependencies_, other.using_dependencies_);
}

bool artefact_properties::operator==(const artefact_properties& rhs) const {
    return enabled_ == rhs.enabled_ &&
        overwrite_ == rhs.overwrite_ &&
        file_path_ == rhs.file_path_ &&
        relative_path_ == rhs.relative_path_ &&
        using_dependencies_ == rhs.using_dependencies_;
}

artefact_properties& artefact_properties::operator=(artefact_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool artefact_properties::enabled() const {
    return enabled_;
}

void artefact_properties::enabled(const bool v) {
    enabled_ = v;
}

bool artefact_properties::overwrite() const {
    return overwrite_;
}

void artefact_properties::overwrite(const bool v) {
    overwrite_ = v;
}

const boost::filesystem::path& artefact_properties::file_path() const {
    return file_path_;
}

boost::filesystem::path& artefact_properties::file_path() {
    return file_path_;
}

void artefact_properties::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void artefact_properties::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const boost::filesystem::path& artefact_properties::relative_path() const {
    return relative_path_;
}

boost::filesystem::path& artefact_properties::relative_path() {
    return relative_path_;
}

void artefact_properties::relative_path(const boost::filesystem::path& v) {
    relative_path_ = v;
}

void artefact_properties::relative_path(const boost::filesystem::path&& v) {
    relative_path_ = std::move(v);
}

const std::list<std::string>& artefact_properties::using_dependencies() const {
    return using_dependencies_;
}

std::list<std::string>& artefact_properties::using_dependencies() {
    return using_dependencies_;
}

void artefact_properties::using_dependencies(const std::list<std::string>& v) {
    using_dependencies_ = v;
}

void artefact_properties::using_dependencies(const std::list<std::string>&& v) {
    using_dependencies_ = std::move(v);
}

}
