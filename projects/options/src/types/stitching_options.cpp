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
#include "dogen/options/types/stitching_options.hpp"

namespace dogen {
namespace options {

stitching_options::stitching_options()
    : force_write_(static_cast<bool>(0)),
      compatibility_mode_(static_cast<bool>(0)) { }

stitching_options::stitching_options(stitching_options&& rhs)
    : log_level_(std::move(rhs.log_level_)),
      target_(std::move(rhs.target_)),
      force_write_(std::move(rhs.force_write_)),
      log_directory_(std::move(rhs.log_directory_)),
      compatibility_mode_(std::move(rhs.compatibility_mode_)) { }

stitching_options::stitching_options(
    const std::string& log_level,
    const boost::filesystem::path& target,
    const bool force_write,
    const boost::filesystem::path& log_directory,
    const bool compatibility_mode)
    : log_level_(log_level),
      target_(target),
      force_write_(force_write),
      log_directory_(log_directory),
      compatibility_mode_(compatibility_mode) { }

void stitching_options::swap(stitching_options& other) noexcept {
    using std::swap;
    swap(log_level_, other.log_level_);
    swap(target_, other.target_);
    swap(force_write_, other.force_write_);
    swap(log_directory_, other.log_directory_);
    swap(compatibility_mode_, other.compatibility_mode_);
}

bool stitching_options::operator==(const stitching_options& rhs) const {
    return log_level_ == rhs.log_level_ &&
        target_ == rhs.target_ &&
        force_write_ == rhs.force_write_ &&
        log_directory_ == rhs.log_directory_ &&
        compatibility_mode_ == rhs.compatibility_mode_;
}

stitching_options& stitching_options::operator=(stitching_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& stitching_options::log_level() const {
    return log_level_;
}

std::string& stitching_options::log_level() {
    return log_level_;
}

void stitching_options::log_level(const std::string& v) {
    log_level_ = v;
}

void stitching_options::log_level(const std::string&& v) {
    log_level_ = std::move(v);
}

const boost::filesystem::path& stitching_options::target() const {
    return target_;
}

boost::filesystem::path& stitching_options::target() {
    return target_;
}

void stitching_options::target(const boost::filesystem::path& v) {
    target_ = v;
}

void stitching_options::target(const boost::filesystem::path&& v) {
    target_ = std::move(v);
}

bool stitching_options::force_write() const {
    return force_write_;
}

void stitching_options::force_write(const bool v) {
    force_write_ = v;
}

const boost::filesystem::path& stitching_options::log_directory() const {
    return log_directory_;
}

boost::filesystem::path& stitching_options::log_directory() {
    return log_directory_;
}

void stitching_options::log_directory(const boost::filesystem::path& v) {
    log_directory_ = v;
}

void stitching_options::log_directory(const boost::filesystem::path&& v) {
    log_directory_ = std::move(v);
}

bool stitching_options::compatibility_mode() const {
    return compatibility_mode_;
}

void stitching_options::compatibility_mode(const bool v) {
    compatibility_mode_ = v;
}

} }
