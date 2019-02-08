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
#include "masd.dogen/types/generation_configuration.hpp"

namespace masd::dogen {

generation_configuration::generation_configuration()
    : force_write_(static_cast<bool>(0)),
      compatibility_mode_enabled_(static_cast<bool>(0)),
      delete_extra_files_(static_cast<bool>(0)) { }

generation_configuration::generation_configuration(generation_configuration&& rhs)
    : output_directory_(std::move(rhs.output_directory_)),
      reference_model_directories_(std::move(rhs.reference_model_directories_)),
      force_write_(std::move(rhs.force_write_)),
      compatibility_mode_enabled_(std::move(rhs.compatibility_mode_enabled_)),
      target_(std::move(rhs.target_)),
      delete_extra_files_(std::move(rhs.delete_extra_files_)),
      ignore_files_matching_regex_(std::move(rhs.ignore_files_matching_regex_)),
      cpp_headers_output_directory_(std::move(rhs.cpp_headers_output_directory_)) { }

generation_configuration::generation_configuration(
    const boost::filesystem::path& output_directory,
    const std::vector<boost::filesystem::path>& reference_model_directories,
    const bool force_write,
    const bool compatibility_mode_enabled,
    const boost::filesystem::path& target,
    const bool delete_extra_files,
    const std::vector<std::string>& ignore_files_matching_regex,
    const boost::filesystem::path& cpp_headers_output_directory)
    : output_directory_(output_directory),
      reference_model_directories_(reference_model_directories),
      force_write_(force_write),
      compatibility_mode_enabled_(compatibility_mode_enabled),
      target_(target),
      delete_extra_files_(delete_extra_files),
      ignore_files_matching_regex_(ignore_files_matching_regex),
      cpp_headers_output_directory_(cpp_headers_output_directory) { }

void generation_configuration::swap(generation_configuration& other) noexcept {
    using std::swap;
    swap(output_directory_, other.output_directory_);
    swap(reference_model_directories_, other.reference_model_directories_);
    swap(force_write_, other.force_write_);
    swap(compatibility_mode_enabled_, other.compatibility_mode_enabled_);
    swap(target_, other.target_);
    swap(delete_extra_files_, other.delete_extra_files_);
    swap(ignore_files_matching_regex_, other.ignore_files_matching_regex_);
    swap(cpp_headers_output_directory_, other.cpp_headers_output_directory_);
}

bool generation_configuration::operator==(const generation_configuration& rhs) const {
    return output_directory_ == rhs.output_directory_ &&
        reference_model_directories_ == rhs.reference_model_directories_ &&
        force_write_ == rhs.force_write_ &&
        compatibility_mode_enabled_ == rhs.compatibility_mode_enabled_ &&
        target_ == rhs.target_ &&
        delete_extra_files_ == rhs.delete_extra_files_ &&
        ignore_files_matching_regex_ == rhs.ignore_files_matching_regex_ &&
        cpp_headers_output_directory_ == rhs.cpp_headers_output_directory_;
}

generation_configuration& generation_configuration::operator=(generation_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& generation_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& generation_configuration::output_directory() {
    return output_directory_;
}

generation_configuration& generation_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
    return *this;
}

generation_configuration& generation_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
    return *this;
}

const std::vector<boost::filesystem::path>& generation_configuration::reference_model_directories() const {
    return reference_model_directories_;
}

std::vector<boost::filesystem::path>& generation_configuration::reference_model_directories() {
    return reference_model_directories_;
}

generation_configuration& generation_configuration::reference_model_directories(const std::vector<boost::filesystem::path>& v) {
    reference_model_directories_ = v;
    return *this;
}

generation_configuration& generation_configuration::reference_model_directories(const std::vector<boost::filesystem::path>&& v) {
    reference_model_directories_ = std::move(v);
    return *this;
}

bool generation_configuration::force_write() const {
    return force_write_;
}

generation_configuration& generation_configuration::force_write(const bool v) {
    force_write_ = v;
    return *this;
}

bool generation_configuration::compatibility_mode_enabled() const {
    return compatibility_mode_enabled_;
}

generation_configuration& generation_configuration::compatibility_mode_enabled(const bool v) {
    compatibility_mode_enabled_ = v;
    return *this;
}

const boost::filesystem::path& generation_configuration::target() const {
    return target_;
}

boost::filesystem::path& generation_configuration::target() {
    return target_;
}

generation_configuration& generation_configuration::target(const boost::filesystem::path& v) {
    target_ = v;
    return *this;
}

generation_configuration& generation_configuration::target(const boost::filesystem::path&& v) {
    target_ = std::move(v);
    return *this;
}

bool generation_configuration::delete_extra_files() const {
    return delete_extra_files_;
}

generation_configuration& generation_configuration::delete_extra_files(const bool v) {
    delete_extra_files_ = v;
    return *this;
}

const std::vector<std::string>& generation_configuration::ignore_files_matching_regex() const {
    return ignore_files_matching_regex_;
}

std::vector<std::string>& generation_configuration::ignore_files_matching_regex() {
    return ignore_files_matching_regex_;
}

generation_configuration& generation_configuration::ignore_files_matching_regex(const std::vector<std::string>& v) {
    ignore_files_matching_regex_ = v;
    return *this;
}

generation_configuration& generation_configuration::ignore_files_matching_regex(const std::vector<std::string>&& v) {
    ignore_files_matching_regex_ = std::move(v);
    return *this;
}

const boost::filesystem::path& generation_configuration::cpp_headers_output_directory() const {
    return cpp_headers_output_directory_;
}

boost::filesystem::path& generation_configuration::cpp_headers_output_directory() {
    return cpp_headers_output_directory_;
}

generation_configuration& generation_configuration::cpp_headers_output_directory(const boost::filesystem::path& v) {
    cpp_headers_output_directory_ = v;
    return *this;
}

generation_configuration& generation_configuration::cpp_headers_output_directory(const boost::filesystem::path&& v) {
    cpp_headers_output_directory_ = std::move(v);
    return *this;
}

}
