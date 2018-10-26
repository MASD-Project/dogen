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
#include "masd.dogen/types/tracing_configuration.hpp"

namespace masd::dogen {

tracing_configuration::tracing_configuration()
    : enabled_(static_cast<bool>(0)),
      level_(static_cast<masd::dogen::tracing_level>(0)),
      format_(static_cast<masd::dogen::tracing_format>(0)),
      enable_guids_(static_cast<bool>(0)) { }

tracing_configuration::tracing_configuration(tracing_configuration&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      output_directory_(std::move(rhs.output_directory_)),
      level_(std::move(rhs.level_)),
      format_(std::move(rhs.format_)),
      enable_guids_(std::move(rhs.enable_guids_)) { }

tracing_configuration::tracing_configuration(
    const bool enabled,
    const boost::filesystem::path& output_directory,
    const masd::dogen::tracing_level level,
    const masd::dogen::tracing_format format,
    const bool enable_guids)
    : enabled_(enabled),
      output_directory_(output_directory),
      level_(level),
      format_(format),
      enable_guids_(enable_guids) { }

void tracing_configuration::swap(tracing_configuration& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(output_directory_, other.output_directory_);
    swap(level_, other.level_);
    swap(format_, other.format_);
    swap(enable_guids_, other.enable_guids_);
}

bool tracing_configuration::operator==(const tracing_configuration& rhs) const {
    return enabled_ == rhs.enabled_ &&
        output_directory_ == rhs.output_directory_ &&
        level_ == rhs.level_ &&
        format_ == rhs.format_ &&
        enable_guids_ == rhs.enable_guids_;
}

tracing_configuration& tracing_configuration::operator=(tracing_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool tracing_configuration::enabled() const {
    return enabled_;
}

tracing_configuration& tracing_configuration::enabled(const bool v) {
    enabled_ = v;
    return *this;
}

const boost::filesystem::path& tracing_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& tracing_configuration::output_directory() {
    return output_directory_;
}

tracing_configuration& tracing_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
    return *this;
}

tracing_configuration& tracing_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
    return *this;
}

masd::dogen::tracing_level tracing_configuration::level() const {
    return level_;
}

tracing_configuration& tracing_configuration::level(const masd::dogen::tracing_level v) {
    level_ = v;
    return *this;
}

masd::dogen::tracing_format tracing_configuration::format() const {
    return format_;
}

tracing_configuration& tracing_configuration::format(const masd::dogen::tracing_format v) {
    format_ = v;
    return *this;
}

bool tracing_configuration::enable_guids() const {
    return enable_guids_;
}

tracing_configuration& tracing_configuration::enable_guids(const bool v) {
    enable_guids_ = v;
    return *this;
}

}
