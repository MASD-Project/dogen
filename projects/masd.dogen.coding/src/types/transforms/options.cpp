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
    : compatibility_mode_(static_cast<bool>(0)) { }

options::options(options&& rhs)
    : target_(std::move(rhs.target_)),
      output_directory_path_(std::move(rhs.output_directory_path_)),
      compatibility_mode_(std::move(rhs.compatibility_mode_)),
      probe_directory_(std::move(rhs.probe_directory_)),
      tracing_(std::move(rhs.tracing_)) { }

options::options(
    const boost::filesystem::path& target,
    const boost::filesystem::path& output_directory_path,
    const bool compatibility_mode,
    const boost::filesystem::path& probe_directory,
    const boost::optional<masd::dogen::tracing_configuration>& tracing)
    : target_(target),
      output_directory_path_(output_directory_path),
      compatibility_mode_(compatibility_mode),
      probe_directory_(probe_directory),
      tracing_(tracing) { }

void options::swap(options& other) noexcept {
    using std::swap;
    swap(target_, other.target_);
    swap(output_directory_path_, other.output_directory_path_);
    swap(compatibility_mode_, other.compatibility_mode_);
    swap(probe_directory_, other.probe_directory_);
    swap(tracing_, other.tracing_);
}

bool options::operator==(const options& rhs) const {
    return target_ == rhs.target_ &&
        output_directory_path_ == rhs.output_directory_path_ &&
        compatibility_mode_ == rhs.compatibility_mode_ &&
        probe_directory_ == rhs.probe_directory_ &&
        tracing_ == rhs.tracing_;
}

options& options::operator=(options other) {
    using std::swap;
    swap(*this, other);
    return *this;
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

bool options::compatibility_mode() const {
    return compatibility_mode_;
}

void options::compatibility_mode(const bool v) {
    compatibility_mode_ = v;
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

const boost::optional<masd::dogen::tracing_configuration>& options::tracing() const {
    return tracing_;
}

boost::optional<masd::dogen::tracing_configuration>& options::tracing() {
    return tracing_;
}

void options::tracing(const boost::optional<masd::dogen::tracing_configuration>& v) {
    tracing_ = v;
}

void options::tracing(const boost::optional<masd::dogen::tracing_configuration>&& v) {
    tracing_ = std::move(v);
}

}
