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
#include "dogen.cli/types/cli_configuration.hpp"

namespace dogen::cli {

cli_configuration::cli_configuration()
    : dumpspecs_(static_cast<bool>(0)) { }

cli_configuration::cli_configuration(cli_configuration&& rhs)
    : activity_(std::move(rhs.activity_)),
      byproduct_directory_(std::move(rhs.byproduct_directory_)),
      dumpspecs_(std::move(rhs.dumpspecs_)) { }

cli_configuration::cli_configuration(
    const boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration>& activity,
    const boost::filesystem::path& byproduct_directory,
    const bool dumpspecs)
    : activity_(activity),
      byproduct_directory_(byproduct_directory),
      dumpspecs_(dumpspecs) { }

void cli_configuration::swap(cli_configuration& other) noexcept {
    using std::swap;
    swap(activity_, other.activity_);
    swap(byproduct_directory_, other.byproduct_directory_);
    swap(dumpspecs_, other.dumpspecs_);
}

bool cli_configuration::operator==(const cli_configuration& rhs) const {
    return activity_ == rhs.activity_ &&
        byproduct_directory_ == rhs.byproduct_directory_ &&
        dumpspecs_ == rhs.dumpspecs_;
}

cli_configuration& cli_configuration::operator=(cli_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration>& cli_configuration::activity() const {
    return activity_;
}

boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration>& cli_configuration::activity() {
    return activity_;
}

cli_configuration& cli_configuration::activity(const boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration>& v) {
    activity_ = v;
    return *this;
}

cli_configuration& cli_configuration::activity(const boost::variant<dogen::cli::generation_configuration, dogen::cli::conversion_configuration>&& v) {
    activity_ = std::move(v);
    return *this;
}

const boost::filesystem::path& cli_configuration::byproduct_directory() const {
    return byproduct_directory_;
}

boost::filesystem::path& cli_configuration::byproduct_directory() {
    return byproduct_directory_;
}

cli_configuration& cli_configuration::byproduct_directory(const boost::filesystem::path& v) {
    byproduct_directory_ = v;
    return *this;
}

cli_configuration& cli_configuration::byproduct_directory(const boost::filesystem::path&& v) {
    byproduct_directory_ = std::move(v);
    return *this;
}

bool cli_configuration::dumpspecs() const {
    return dumpspecs_;
}

cli_configuration& cli_configuration::dumpspecs(const bool v) {
    dumpspecs_ = v;
    return *this;
}

}
