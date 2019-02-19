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
#include "masd.dogen.cli/types/cli_configuration.hpp"

namespace masd::dogen::cli {

cli_configuration::cli_configuration(cli_configuration&& rhs)
    : activity_(std::move(rhs.activity_)),
      tracing_output_directory_(std::move(rhs.tracing_output_directory_)),
      diffing_output_directory_(std::move(rhs.diffing_output_directory_)) { }

cli_configuration::cli_configuration(
    const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& activity,
    const boost::filesystem::path& tracing_output_directory,
    const boost::filesystem::path& diffing_output_directory)
    : activity_(activity),
      tracing_output_directory_(tracing_output_directory),
      diffing_output_directory_(diffing_output_directory) { }

void cli_configuration::swap(cli_configuration& other) noexcept {
    using std::swap;
    swap(activity_, other.activity_);
    swap(tracing_output_directory_, other.tracing_output_directory_);
    swap(diffing_output_directory_, other.diffing_output_directory_);
}

bool cli_configuration::operator==(const cli_configuration& rhs) const {
    return activity_ == rhs.activity_ &&
        tracing_output_directory_ == rhs.tracing_output_directory_ &&
        diffing_output_directory_ == rhs.diffing_output_directory_;
}

cli_configuration& cli_configuration::operator=(cli_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& cli_configuration::activity() const {
    return activity_;
}

boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& cli_configuration::activity() {
    return activity_;
}

cli_configuration& cli_configuration::activity(const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& v) {
    activity_ = v;
    return *this;
}

cli_configuration& cli_configuration::activity(const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>&& v) {
    activity_ = std::move(v);
    return *this;
}

const boost::filesystem::path& cli_configuration::tracing_output_directory() const {
    return tracing_output_directory_;
}

boost::filesystem::path& cli_configuration::tracing_output_directory() {
    return tracing_output_directory_;
}

cli_configuration& cli_configuration::tracing_output_directory(const boost::filesystem::path& v) {
    tracing_output_directory_ = v;
    return *this;
}

cli_configuration& cli_configuration::tracing_output_directory(const boost::filesystem::path&& v) {
    tracing_output_directory_ = std::move(v);
    return *this;
}

const boost::filesystem::path& cli_configuration::diffing_output_directory() const {
    return diffing_output_directory_;
}

boost::filesystem::path& cli_configuration::diffing_output_directory() {
    return diffing_output_directory_;
}

cli_configuration& cli_configuration::diffing_output_directory(const boost::filesystem::path& v) {
    diffing_output_directory_ = v;
    return *this;
}

cli_configuration& cli_configuration::diffing_output_directory(const boost::filesystem::path&& v) {
    diffing_output_directory_ = std::move(v);
    return *this;
}

}
