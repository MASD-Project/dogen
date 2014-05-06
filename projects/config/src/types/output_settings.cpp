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
#include "dogen/config/types/output_settings.hpp"

namespace dogen {
namespace config {

output_settings::output_settings()
    : output_to_stdout_(static_cast<bool>(0)),
      output_to_file_(static_cast<bool>(0)),
      delete_extra_files_(static_cast<bool>(0)),
      force_write_(static_cast<bool>(0)) { }

output_settings::output_settings(
    const bool output_to_stdout,
    const bool output_to_file,
    const bool delete_extra_files,
    const bool force_write,
    const std::vector<std::string>& ignore_patterns)
    : output_to_stdout_(output_to_stdout),
      output_to_file_(output_to_file),
      delete_extra_files_(delete_extra_files),
      force_write_(force_write),
      ignore_patterns_(ignore_patterns) { }

void output_settings::swap(output_settings& other) noexcept {
    using std::swap;
    swap(output_to_stdout_, other.output_to_stdout_);
    swap(output_to_file_, other.output_to_file_);
    swap(delete_extra_files_, other.delete_extra_files_);
    swap(force_write_, other.force_write_);
    swap(ignore_patterns_, other.ignore_patterns_);
}

bool output_settings::operator==(const output_settings& rhs) const {
    return output_to_stdout_ == rhs.output_to_stdout_ &&
        output_to_file_ == rhs.output_to_file_ &&
        delete_extra_files_ == rhs.delete_extra_files_ &&
        force_write_ == rhs.force_write_ &&
        ignore_patterns_ == rhs.ignore_patterns_;
}

output_settings& output_settings::operator=(output_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool output_settings::output_to_stdout() const {
    return output_to_stdout_;
}

void output_settings::output_to_stdout(const bool v) {
    output_to_stdout_ = v;
}

bool output_settings::output_to_file() const {
    return output_to_file_;
}

void output_settings::output_to_file(const bool v) {
    output_to_file_ = v;
}

bool output_settings::delete_extra_files() const {
    return delete_extra_files_;
}

void output_settings::delete_extra_files(const bool v) {
    delete_extra_files_ = v;
}

bool output_settings::force_write() const {
    return force_write_;
}

void output_settings::force_write(const bool v) {
    force_write_ = v;
}

const std::vector<std::string>& output_settings::ignore_patterns() const {
    return ignore_patterns_;
}

std::vector<std::string>& output_settings::ignore_patterns() {
    return ignore_patterns_;
}

void output_settings::ignore_patterns(const std::vector<std::string>& v) {
    ignore_patterns_ = v;
}

void output_settings::ignore_patterns(const std::vector<std::string>&& v) {
    ignore_patterns_ = std::move(v);
}

} }