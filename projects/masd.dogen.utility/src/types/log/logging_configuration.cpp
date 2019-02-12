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
#include "masd.dogen.utility/types/log/logging_configuration.hpp"

namespace masd::dogen::utility::log {

logging_configuration::logging_configuration()
    : output_to_console_(static_cast<bool>(0)) { }

logging_configuration::logging_configuration(logging_configuration&& rhs)
    : level_(std::move(rhs.level_)),
      filename_(std::move(rhs.filename_)),
      output_to_console_(std::move(rhs.output_to_console_)),
      output_directory_(std::move(rhs.output_directory_)) { }

logging_configuration::logging_configuration(
    const masd::dogen::utility::log::severity_level& level,
    const std::string& filename,
    const bool output_to_console,
    const boost::filesystem::path& output_directory)
    : level_(level),
      filename_(filename),
      output_to_console_(output_to_console),
      output_directory_(output_directory) { }

void logging_configuration::swap(logging_configuration& other) noexcept {
    using std::swap;
    swap(level_, other.level_);
    swap(filename_, other.filename_);
    swap(output_to_console_, other.output_to_console_);
    swap(output_directory_, other.output_directory_);
}

bool logging_configuration::operator==(const logging_configuration& rhs) const {
    return level_ == rhs.level_ &&
        filename_ == rhs.filename_ &&
        output_to_console_ == rhs.output_to_console_ &&
        output_directory_ == rhs.output_directory_;
}

logging_configuration& logging_configuration::operator=(logging_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::utility::log::severity_level& logging_configuration::level() const {
    return level_;
}

masd::dogen::utility::log::severity_level& logging_configuration::level() {
    return level_;
}

logging_configuration& logging_configuration::level(const masd::dogen::utility::log::severity_level& v) {
    level_ = v;
    return *this;
}

logging_configuration& logging_configuration::level(const masd::dogen::utility::log::severity_level&& v) {
    level_ = std::move(v);
    return *this;
}

const std::string& logging_configuration::filename() const {
    return filename_;
}

std::string& logging_configuration::filename() {
    return filename_;
}

logging_configuration& logging_configuration::filename(const std::string& v) {
    filename_ = v;
    return *this;
}

logging_configuration& logging_configuration::filename(const std::string&& v) {
    filename_ = std::move(v);
    return *this;
}

bool logging_configuration::output_to_console() const {
    return output_to_console_;
}

logging_configuration& logging_configuration::output_to_console(const bool v) {
    output_to_console_ = v;
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

}
