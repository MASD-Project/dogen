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
#include "masd.dogen/types/logging_configuration.hpp"

namespace masd::dogen {

logging_configuration::logging_configuration()
    : enabled_(static_cast<bool>(0)),
      level_(static_cast<masd::dogen::log_level>(0)),
      output_to_console_(static_cast<bool>(0)) { }

logging_configuration::logging_configuration(logging_configuration&& rhs)
    : enabled_(std::move(rhs.enabled_)),
      output_directory_(std::move(rhs.output_directory_)),
      level_(std::move(rhs.level_)),
      file_name_(std::move(rhs.file_name_)),
      output_to_console_(std::move(rhs.output_to_console_)) { }

logging_configuration::logging_configuration(
    const bool enabled,
    const boost::filesystem::path& output_directory,
    const masd::dogen::log_level level,
    const std::string& file_name,
    const bool output_to_console)
    : enabled_(enabled),
      output_directory_(output_directory),
      level_(level),
      file_name_(file_name),
      output_to_console_(output_to_console) { }

void logging_configuration::swap(logging_configuration& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(output_directory_, other.output_directory_);
    swap(level_, other.level_);
    swap(file_name_, other.file_name_);
    swap(output_to_console_, other.output_to_console_);
}

bool logging_configuration::operator==(const logging_configuration& rhs) const {
    return enabled_ == rhs.enabled_ &&
        output_directory_ == rhs.output_directory_ &&
        level_ == rhs.level_ &&
        file_name_ == rhs.file_name_ &&
        output_to_console_ == rhs.output_to_console_;
}

logging_configuration& logging_configuration::operator=(logging_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool logging_configuration::enabled() const {
    return enabled_;
}

logging_configuration& logging_configuration::enabled(const bool v) {
    enabled_ = v;
    return *this;
}

const boost::filesystem::path& logging_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& logging_configuration::output_directory() {
    return output_directory_;
}

logging_configuration& logging_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
    return *this;
}

logging_configuration& logging_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
    return *this;
}

masd::dogen::log_level logging_configuration::level() const {
    return level_;
}

logging_configuration& logging_configuration::level(const masd::dogen::log_level v) {
    level_ = v;
    return *this;
}

const std::string& logging_configuration::file_name() const {
    return file_name_;
}

std::string& logging_configuration::file_name() {
    return file_name_;
}

logging_configuration& logging_configuration::file_name(const std::string& v) {
    file_name_ = v;
    return *this;
}

logging_configuration& logging_configuration::file_name(const std::string&& v) {
    file_name_ = std::move(v);
    return *this;
}

bool logging_configuration::output_to_console() const {
    return output_to_console_;
}

logging_configuration& logging_configuration::output_to_console(const bool v) {
    output_to_console_ = v;
    return *this;
}

}
