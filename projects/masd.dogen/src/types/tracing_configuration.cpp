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
    : level_(static_cast<masd::dogen::tracing_level>(0)),
      format_(static_cast<masd::dogen::tracing_format>(0)),
      guids_enabled_(static_cast<bool>(0)),
      use_short_names_(static_cast<bool>(0)) { }

tracing_configuration::tracing_configuration(
    const masd::dogen::tracing_level level,
    const masd::dogen::tracing_format format,
    const bool guids_enabled,
    const std::string& logging_impact,
    const bool use_short_names)
    : level_(level),
      format_(format),
      guids_enabled_(guids_enabled),
      logging_impact_(logging_impact),
      use_short_names_(use_short_names) { }

void tracing_configuration::swap(tracing_configuration& other) noexcept {
    using std::swap;
    swap(level_, other.level_);
    swap(format_, other.format_);
    swap(guids_enabled_, other.guids_enabled_);
    swap(logging_impact_, other.logging_impact_);
    swap(use_short_names_, other.use_short_names_);
}

bool tracing_configuration::operator==(const tracing_configuration& rhs) const {
    return level_ == rhs.level_ &&
        format_ == rhs.format_ &&
        guids_enabled_ == rhs.guids_enabled_ &&
        logging_impact_ == rhs.logging_impact_ &&
        use_short_names_ == rhs.use_short_names_;
}

tracing_configuration& tracing_configuration::operator=(tracing_configuration other) {
    using std::swap;
    swap(*this, other);
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

bool tracing_configuration::guids_enabled() const {
    return guids_enabled_;
}

tracing_configuration& tracing_configuration::guids_enabled(const bool v) {
    guids_enabled_ = v;
    return *this;
}

const std::string& tracing_configuration::logging_impact() const {
    return logging_impact_;
}

std::string& tracing_configuration::logging_impact() {
    return logging_impact_;
}

tracing_configuration& tracing_configuration::logging_impact(const std::string& v) {
    logging_impact_ = v;
    return *this;
}

tracing_configuration& tracing_configuration::logging_impact(const std::string&& v) {
    logging_impact_ = std::move(v);
    return *this;
}

bool tracing_configuration::use_short_names() const {
    return use_short_names_;
}

tracing_configuration& tracing_configuration::use_short_names(const bool v) {
    use_short_names_ = v;
    return *this;
}

}
