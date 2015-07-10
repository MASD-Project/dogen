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
#include "dogen/config/types/cpp_options.hpp"

namespace dogen {
namespace config {

cpp_options::cpp_options()
    : split_project_(static_cast<bool>(0)),
      disable_cmakelists_(static_cast<bool>(0)) { }

cpp_options::cpp_options(cpp_options&& rhs)
    : split_project_(std::move(rhs.split_project_)),
      project_directory_path_(std::move(rhs.project_directory_path_)),
      source_directory_path_(std::move(rhs.source_directory_path_)),
      include_directory_path_(std::move(rhs.include_directory_path_)),
      disable_cmakelists_(std::move(rhs.disable_cmakelists_)) { }

cpp_options::cpp_options(
    const bool split_project,
    const boost::filesystem::path& project_directory_path,
    const boost::filesystem::path& source_directory_path,
    const boost::filesystem::path& include_directory_path,
    const bool disable_cmakelists)
    : split_project_(split_project),
      project_directory_path_(project_directory_path),
      source_directory_path_(source_directory_path),
      include_directory_path_(include_directory_path),
      disable_cmakelists_(disable_cmakelists) { }

void cpp_options::swap(cpp_options& other) noexcept {
    using std::swap;
    swap(split_project_, other.split_project_);
    swap(project_directory_path_, other.project_directory_path_);
    swap(source_directory_path_, other.source_directory_path_);
    swap(include_directory_path_, other.include_directory_path_);
    swap(disable_cmakelists_, other.disable_cmakelists_);
}

bool cpp_options::operator==(const cpp_options& rhs) const {
    return split_project_ == rhs.split_project_ &&
        project_directory_path_ == rhs.project_directory_path_ &&
        source_directory_path_ == rhs.source_directory_path_ &&
        include_directory_path_ == rhs.include_directory_path_ &&
        disable_cmakelists_ == rhs.disable_cmakelists_;
}

cpp_options& cpp_options::operator=(cpp_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool cpp_options::split_project() const {
    return split_project_;
}

void cpp_options::split_project(const bool v) {
    split_project_ = v;
}

const boost::filesystem::path& cpp_options::project_directory_path() const {
    return project_directory_path_;
}

boost::filesystem::path& cpp_options::project_directory_path() {
    return project_directory_path_;
}

void cpp_options::project_directory_path(const boost::filesystem::path& v) {
    project_directory_path_ = v;
}

void cpp_options::project_directory_path(const boost::filesystem::path&& v) {
    project_directory_path_ = std::move(v);
}

const boost::filesystem::path& cpp_options::source_directory_path() const {
    return source_directory_path_;
}

boost::filesystem::path& cpp_options::source_directory_path() {
    return source_directory_path_;
}

void cpp_options::source_directory_path(const boost::filesystem::path& v) {
    source_directory_path_ = v;
}

void cpp_options::source_directory_path(const boost::filesystem::path&& v) {
    source_directory_path_ = std::move(v);
}

const boost::filesystem::path& cpp_options::include_directory_path() const {
    return include_directory_path_;
}

boost::filesystem::path& cpp_options::include_directory_path() {
    return include_directory_path_;
}

void cpp_options::include_directory_path(const boost::filesystem::path& v) {
    include_directory_path_ = v;
}

void cpp_options::include_directory_path(const boost::filesystem::path&& v) {
    include_directory_path_ = std::move(v);
}

bool cpp_options::disable_cmakelists() const {
    return disable_cmakelists_;
}

void cpp_options::disable_cmakelists(const bool v) {
    disable_cmakelists_ = v;
}

} }
