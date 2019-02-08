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
    : enabled_(static_cast<bool>(0)),
      force_write_(static_cast<bool>(0)),
      enable_compatibility_mode_(static_cast<bool>(0)) { }

generation_configuration::generation_configuration(generation_configuration&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      output_directory_(std::move(rhs.output_directory_)),
      reference_model_directories_(std::move(rhs.reference_model_directories_)),
      force_write_(std::move(rhs.force_write_)),
      enable_compatibility_mode_(std::move(rhs.enable_compatibility_mode_)),
      target_(std::move(rhs.target_)) { }

generation_configuration::generation_configuration(
    const bool enabled,
    const boost::filesystem::path& output_directory,
    const std::list<boost::filesystem::path>& reference_model_directories,
    const bool force_write,
    const bool enable_compatibility_mode,
    const boost::filesystem::path& target)
    : enabled_(enabled),
      output_directory_(output_directory),
      reference_model_directories_(reference_model_directories),
      force_write_(force_write),
      enable_compatibility_mode_(enable_compatibility_mode),
      target_(target) { }

void generation_configuration::swap(generation_configuration& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(output_directory_, other.output_directory_);
    swap(reference_model_directories_, other.reference_model_directories_);
    swap(force_write_, other.force_write_);
    swap(enable_compatibility_mode_, other.enable_compatibility_mode_);
    swap(target_, other.target_);
}

bool generation_configuration::operator==(const generation_configuration& rhs) const {
    return enabled_ == rhs.enabled_ &&
        output_directory_ == rhs.output_directory_ &&
        reference_model_directories_ == rhs.reference_model_directories_ &&
        force_write_ == rhs.force_write_ &&
        enable_compatibility_mode_ == rhs.enable_compatibility_mode_ &&
        target_ == rhs.target_;
}

generation_configuration& generation_configuration::operator=(generation_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool generation_configuration::enabled() const {
    return enabled_;
}

generation_configuration& generation_configuration::enabled(const bool v) {
    enabled_ = v;
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

const std::list<boost::filesystem::path>& generation_configuration::reference_model_directories() const {
    return reference_model_directories_;
}

std::list<boost::filesystem::path>& generation_configuration::reference_model_directories() {
    return reference_model_directories_;
}

generation_configuration& generation_configuration::reference_model_directories(const std::list<boost::filesystem::path>& v) {
    reference_model_directories_ = v;
    return *this;
}

generation_configuration& generation_configuration::reference_model_directories(const std::list<boost::filesystem::path>&& v) {
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

bool generation_configuration::enable_compatibility_mode() const {
    return enable_compatibility_mode_;
}

generation_configuration& generation_configuration::enable_compatibility_mode(const bool v) {
    enable_compatibility_mode_ = v;
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

}
