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
#include "masd.dogen.coding/types/transforms/options.hpp"

namespace masd::dogen::coding::transforms {

options::options()
    : compatibility_mode_(static_cast<bool>(0)),
      probe_stats_(static_cast<bool>(0)),
      probe_stats_disable_guids_(static_cast<bool>(0)),
      probe_stats_org_mode_(static_cast<bool>(0)),
      probe_all_(static_cast<bool>(0)),
      probe_use_short_names_(static_cast<bool>(0)) { }

options::options(options&& rhs)
    : log_file_(std::move(rhs.log_file_)),
      log_level_(std::move(rhs.log_level_)),
      target_(std::move(rhs.target_)),
      output_directory_path_(std::move(rhs.output_directory_path_)),
      cpp_headers_output_directory_path_(std::move(rhs.cpp_headers_output_directory_path_)),
      compatibility_mode_(std::move(rhs.compatibility_mode_)),
      probe_stats_(std::move(rhs.probe_stats_)),
      probe_stats_disable_guids_(std::move(rhs.probe_stats_disable_guids_)),
      probe_stats_org_mode_(std::move(rhs.probe_stats_org_mode_)),
      probe_all_(std::move(rhs.probe_all_)),
      probe_directory_(std::move(rhs.probe_directory_)),
      probe_use_short_names_(std::move(rhs.probe_use_short_names_)) { }

options::options(
    const boost::filesystem::path& log_file,
    const std::string& log_level,
    const boost::filesystem::path& target,
    const boost::filesystem::path& output_directory_path,
    const boost::filesystem::path& cpp_headers_output_directory_path,
    const bool compatibility_mode,
    const bool probe_stats,
    const bool probe_stats_disable_guids,
    const bool probe_stats_org_mode,
    const bool probe_all,
    const boost::filesystem::path& probe_directory,
    const bool probe_use_short_names)
    : log_file_(log_file),
      log_level_(log_level),
      target_(target),
      output_directory_path_(output_directory_path),
      cpp_headers_output_directory_path_(cpp_headers_output_directory_path),
      compatibility_mode_(compatibility_mode),
      probe_stats_(probe_stats),
      probe_stats_disable_guids_(probe_stats_disable_guids),
      probe_stats_org_mode_(probe_stats_org_mode),
      probe_all_(probe_all),
      probe_directory_(probe_directory),
      probe_use_short_names_(probe_use_short_names) { }

void options::swap(options& other) noexcept {
    using std::swap;
    swap(log_file_, other.log_file_);
    swap(log_level_, other.log_level_);
    swap(target_, other.target_);
    swap(output_directory_path_, other.output_directory_path_);
    swap(cpp_headers_output_directory_path_, other.cpp_headers_output_directory_path_);
    swap(compatibility_mode_, other.compatibility_mode_);
    swap(probe_stats_, other.probe_stats_);
    swap(probe_stats_disable_guids_, other.probe_stats_disable_guids_);
    swap(probe_stats_org_mode_, other.probe_stats_org_mode_);
    swap(probe_all_, other.probe_all_);
    swap(probe_directory_, other.probe_directory_);
    swap(probe_use_short_names_, other.probe_use_short_names_);
}

bool options::operator==(const options& rhs) const {
    return log_file_ == rhs.log_file_ &&
        log_level_ == rhs.log_level_ &&
        target_ == rhs.target_ &&
        output_directory_path_ == rhs.output_directory_path_ &&
        cpp_headers_output_directory_path_ == rhs.cpp_headers_output_directory_path_ &&
        compatibility_mode_ == rhs.compatibility_mode_ &&
        probe_stats_ == rhs.probe_stats_ &&
        probe_stats_disable_guids_ == rhs.probe_stats_disable_guids_ &&
        probe_stats_org_mode_ == rhs.probe_stats_org_mode_ &&
        probe_all_ == rhs.probe_all_ &&
        probe_directory_ == rhs.probe_directory_ &&
        probe_use_short_names_ == rhs.probe_use_short_names_;
}

options& options::operator=(options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& options::log_file() const {
    return log_file_;
}

boost::filesystem::path& options::log_file() {
    return log_file_;
}

void options::log_file(const boost::filesystem::path& v) {
    log_file_ = v;
}

void options::log_file(const boost::filesystem::path&& v) {
    log_file_ = std::move(v);
}

const std::string& options::log_level() const {
    return log_level_;
}

std::string& options::log_level() {
    return log_level_;
}

void options::log_level(const std::string& v) {
    log_level_ = v;
}

void options::log_level(const std::string&& v) {
    log_level_ = std::move(v);
}

const boost::filesystem::path& options::target() const {
    return target_;
}

boost::filesystem::path& options::target() {
    return target_;
}

void options::target(const boost::filesystem::path& v) {
    target_ = v;
}

void options::target(const boost::filesystem::path&& v) {
    target_ = std::move(v);
}

const boost::filesystem::path& options::output_directory_path() const {
    return output_directory_path_;
}

boost::filesystem::path& options::output_directory_path() {
    return output_directory_path_;
}

void options::output_directory_path(const boost::filesystem::path& v) {
    output_directory_path_ = v;
}

void options::output_directory_path(const boost::filesystem::path&& v) {
    output_directory_path_ = std::move(v);
}

const boost::filesystem::path& options::cpp_headers_output_directory_path() const {
    return cpp_headers_output_directory_path_;
}

boost::filesystem::path& options::cpp_headers_output_directory_path() {
    return cpp_headers_output_directory_path_;
}

void options::cpp_headers_output_directory_path(const boost::filesystem::path& v) {
    cpp_headers_output_directory_path_ = v;
}

void options::cpp_headers_output_directory_path(const boost::filesystem::path&& v) {
    cpp_headers_output_directory_path_ = std::move(v);
}

bool options::compatibility_mode() const {
    return compatibility_mode_;
}

void options::compatibility_mode(const bool v) {
    compatibility_mode_ = v;
}

bool options::probe_stats() const {
    return probe_stats_;
}

void options::probe_stats(const bool v) {
    probe_stats_ = v;
}

bool options::probe_stats_disable_guids() const {
    return probe_stats_disable_guids_;
}

void options::probe_stats_disable_guids(const bool v) {
    probe_stats_disable_guids_ = v;
}

bool options::probe_stats_org_mode() const {
    return probe_stats_org_mode_;
}

void options::probe_stats_org_mode(const bool v) {
    probe_stats_org_mode_ = v;
}

bool options::probe_all() const {
    return probe_all_;
}

void options::probe_all(const bool v) {
    probe_all_ = v;
}

const boost::filesystem::path& options::probe_directory() const {
    return probe_directory_;
}

boost::filesystem::path& options::probe_directory() {
    return probe_directory_;
}

void options::probe_directory(const boost::filesystem::path& v) {
    probe_directory_ = v;
}

void options::probe_directory(const boost::filesystem::path&& v) {
    probe_directory_ = std::move(v);
}

bool options::probe_use_short_names() const {
    return probe_use_short_names_;
}

void options::probe_use_short_names(const bool v) {
    probe_use_short_names_ = v;
}

}
