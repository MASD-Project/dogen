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
#include "dogen/config/types/stitching_options.hpp"

namespace dogen {
namespace config {

stitching_options::stitching_options()
    : verbose_(static_cast<bool>(0)),
      force_write_(static_cast<bool>(0)),
      output_to_file_(static_cast<bool>(0)),
      output_to_stdout_(static_cast<bool>(0)) { }

stitching_options::stitching_options(stitching_options&& rhs)
    : verbose_(std::move(rhs.verbose_)),
      target_(std::move(rhs.target_)),
      force_write_(std::move(rhs.force_write_)),
      output_to_file_(std::move(rhs.output_to_file_)),
      output_to_stdout_(std::move(rhs.output_to_stdout_)) { }

stitching_options::stitching_options(
    const bool verbose,
    const boost::filesystem::path& target,
    const bool force_write,
    const bool output_to_file,
    const bool output_to_stdout)
    : verbose_(verbose),
      target_(target),
      force_write_(force_write),
      output_to_file_(output_to_file),
      output_to_stdout_(output_to_stdout) { }

void stitching_options::swap(stitching_options& other) noexcept {
    using std::swap;
    swap(verbose_, other.verbose_);
    swap(target_, other.target_);
    swap(force_write_, other.force_write_);
    swap(output_to_file_, other.output_to_file_);
    swap(output_to_stdout_, other.output_to_stdout_);
}

bool stitching_options::operator==(const stitching_options& rhs) const {
    return verbose_ == rhs.verbose_ &&
        target_ == rhs.target_ &&
        force_write_ == rhs.force_write_ &&
        output_to_file_ == rhs.output_to_file_ &&
        output_to_stdout_ == rhs.output_to_stdout_;
}

stitching_options& stitching_options::operator=(stitching_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool stitching_options::verbose() const {
    return verbose_;
}

void stitching_options::verbose(const bool v) {
    verbose_ = v;
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

bool stitching_options::output_to_file() const {
    return output_to_file_;
}

void stitching_options::output_to_file(const bool v) {
    output_to_file_ = v;
}

bool stitching_options::output_to_stdout() const {
    return output_to_stdout_;
}

void stitching_options::output_to_stdout(const bool v) {
    output_to_stdout_ = v;
}

} }