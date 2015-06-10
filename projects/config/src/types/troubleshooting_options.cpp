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
#include "dogen/config/types/troubleshooting_options.hpp"

namespace dogen {
namespace config {

troubleshooting_options::troubleshooting_options()
    : save_dia_model_(static_cast<dogen::config::archive_types>(0)),
      save_sml_model_(static_cast<dogen::config::archive_types>(0)),
      stop_after_formatting_(static_cast<bool>(0)),
      stop_after_merging_(static_cast<bool>(0)) { }

troubleshooting_options::troubleshooting_options(troubleshooting_options&& rhs)
    : debug_dir_(std::move(rhs.debug_dir_)),
      save_dia_model_(std::move(rhs.save_dia_model_)),
      save_sml_model_(std::move(rhs.save_sml_model_)),
      stop_after_formatting_(std::move(rhs.stop_after_formatting_)),
      stop_after_merging_(std::move(rhs.stop_after_merging_)) { }

troubleshooting_options::troubleshooting_options(
    const boost::filesystem::path& debug_dir,
    const dogen::config::archive_types save_dia_model,
    const dogen::config::archive_types save_sml_model,
    const bool stop_after_formatting,
    const bool stop_after_merging)
    : debug_dir_(debug_dir),
      save_dia_model_(save_dia_model),
      save_sml_model_(save_sml_model),
      stop_after_formatting_(stop_after_formatting),
      stop_after_merging_(stop_after_merging) { }

void troubleshooting_options::swap(troubleshooting_options& other) noexcept {
    using std::swap;
    swap(debug_dir_, other.debug_dir_);
    swap(save_dia_model_, other.save_dia_model_);
    swap(save_sml_model_, other.save_sml_model_);
    swap(stop_after_formatting_, other.stop_after_formatting_);
    swap(stop_after_merging_, other.stop_after_merging_);
}

bool troubleshooting_options::operator==(const troubleshooting_options& rhs) const {
    return debug_dir_ == rhs.debug_dir_ &&
        save_dia_model_ == rhs.save_dia_model_ &&
        save_sml_model_ == rhs.save_sml_model_ &&
        stop_after_formatting_ == rhs.stop_after_formatting_ &&
        stop_after_merging_ == rhs.stop_after_merging_;
}

troubleshooting_options& troubleshooting_options::operator=(troubleshooting_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& troubleshooting_options::debug_dir() const {
    return debug_dir_;
}

boost::filesystem::path& troubleshooting_options::debug_dir() {
    return debug_dir_;
}

void troubleshooting_options::debug_dir(const boost::filesystem::path& v) {
    debug_dir_ = v;
}

void troubleshooting_options::debug_dir(const boost::filesystem::path&& v) {
    debug_dir_ = std::move(v);
}

dogen::config::archive_types troubleshooting_options::save_dia_model() const {
    return save_dia_model_;
}

void troubleshooting_options::save_dia_model(const dogen::config::archive_types v) {
    save_dia_model_ = v;
}

dogen::config::archive_types troubleshooting_options::save_sml_model() const {
    return save_sml_model_;
}

void troubleshooting_options::save_sml_model(const dogen::config::archive_types v) {
    save_sml_model_ = v;
}

bool troubleshooting_options::stop_after_formatting() const {
    return stop_after_formatting_;
}

void troubleshooting_options::stop_after_formatting(const bool v) {
    stop_after_formatting_ = v;
}

bool troubleshooting_options::stop_after_merging() const {
    return stop_after_merging_;
}

void troubleshooting_options::stop_after_merging(const bool v) {
    stop_after_merging_ = v;
}

} }
