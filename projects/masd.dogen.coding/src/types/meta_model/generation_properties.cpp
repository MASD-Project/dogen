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
#include "masd.dogen.coding/types/meta_model/generation_properties.hpp"

namespace masd::dogen::coding::meta_model {

generation_properties::generation_properties()
    : force_write_(static_cast<bool>(0)),
      compatibility_mode_enabled_(static_cast<bool>(0)),
      delete_extra_files_(static_cast<bool>(0)) { }

generation_properties::generation_properties(generation_properties&& rhs)
    : force_write_(std::move(rhs.force_write_)),
      compatibility_mode_enabled_(std::move(rhs.compatibility_mode_enabled_)),
      delete_extra_files_(std::move(rhs.delete_extra_files_)),
      ignore_files_matching_regex_(std::move(rhs.ignore_files_matching_regex_)),
      cpp_headers_output_directory_(std::move(rhs.cpp_headers_output_directory_)) { }

generation_properties::generation_properties(
    const bool force_write,
    const bool compatibility_mode_enabled,
    const bool delete_extra_files,
    const std::vector<std::string>& ignore_files_matching_regex,
    const boost::filesystem::path& cpp_headers_output_directory)
    : force_write_(force_write),
      compatibility_mode_enabled_(compatibility_mode_enabled),
      delete_extra_files_(delete_extra_files),
      ignore_files_matching_regex_(ignore_files_matching_regex),
      cpp_headers_output_directory_(cpp_headers_output_directory) { }

void generation_properties::swap(generation_properties& other) noexcept {
    using std::swap;
    swap(force_write_, other.force_write_);
    swap(compatibility_mode_enabled_, other.compatibility_mode_enabled_);
    swap(delete_extra_files_, other.delete_extra_files_);
    swap(ignore_files_matching_regex_, other.ignore_files_matching_regex_);
    swap(cpp_headers_output_directory_, other.cpp_headers_output_directory_);
}

bool generation_properties::operator==(const generation_properties& rhs) const {
    return force_write_ == rhs.force_write_ &&
        compatibility_mode_enabled_ == rhs.compatibility_mode_enabled_ &&
        delete_extra_files_ == rhs.delete_extra_files_ &&
        ignore_files_matching_regex_ == rhs.ignore_files_matching_regex_ &&
        cpp_headers_output_directory_ == rhs.cpp_headers_output_directory_;
}

generation_properties& generation_properties::operator=(generation_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool generation_properties::force_write() const {
    return force_write_;
}

void generation_properties::force_write(const bool v) {
    force_write_ = v;
}

bool generation_properties::compatibility_mode_enabled() const {
    return compatibility_mode_enabled_;
}

void generation_properties::compatibility_mode_enabled(const bool v) {
    compatibility_mode_enabled_ = v;
}

bool generation_properties::delete_extra_files() const {
    return delete_extra_files_;
}

void generation_properties::delete_extra_files(const bool v) {
    delete_extra_files_ = v;
}

const std::vector<std::string>& generation_properties::ignore_files_matching_regex() const {
    return ignore_files_matching_regex_;
}

std::vector<std::string>& generation_properties::ignore_files_matching_regex() {
    return ignore_files_matching_regex_;
}

void generation_properties::ignore_files_matching_regex(const std::vector<std::string>& v) {
    ignore_files_matching_regex_ = v;
}

void generation_properties::ignore_files_matching_regex(const std::vector<std::string>&& v) {
    ignore_files_matching_regex_ = std::move(v);
}

const boost::filesystem::path& generation_properties::cpp_headers_output_directory() const {
    return cpp_headers_output_directory_;
}

boost::filesystem::path& generation_properties::cpp_headers_output_directory() {
    return cpp_headers_output_directory_;
}

void generation_properties::cpp_headers_output_directory(const boost::filesystem::path& v) {
    cpp_headers_output_directory_ = v;
}

void generation_properties::cpp_headers_output_directory(const boost::filesystem::path&& v) {
    cpp_headers_output_directory_ = std::move(v);
}

}
