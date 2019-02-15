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
#include "masd.dogen.cli/types/configuration.hpp"

namespace masd::dogen::cli {

configuration::configuration(configuration&& rhs)
    : logging_(std::move(rhs.logging_)),
      tracing_(std::move(rhs.tracing_)),
      diffing_(std::move(rhs.diffing_)),
      error_handling_(std::move(rhs.error_handling_)),
      byproduct_output_directory_(std::move(rhs.byproduct_output_directory_)),
      activity_(std::move(rhs.activity_)) { }

configuration::configuration(
    const boost::optional<masd::dogen::utility::log::logging_configuration>& logging,
    const boost::optional<masd::dogen::tracing_configuration>& tracing,
    const boost::optional<masd::dogen::diffing_configuration>& diffing,
    const boost::optional<masd::dogen::error_handling_configuration>& error_handling,
    const boost::filesystem::path& byproduct_output_directory,
    const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& activity)
    : logging_(logging),
      tracing_(tracing),
      diffing_(diffing),
      error_handling_(error_handling),
      byproduct_output_directory_(byproduct_output_directory),
      activity_(activity) { }

void configuration::swap(configuration& other) noexcept {
    using std::swap;
    swap(logging_, other.logging_);
    swap(tracing_, other.tracing_);
    swap(diffing_, other.diffing_);
    swap(error_handling_, other.error_handling_);
    swap(byproduct_output_directory_, other.byproduct_output_directory_);
    swap(activity_, other.activity_);
}

bool configuration::operator==(const configuration& rhs) const {
    return logging_ == rhs.logging_ &&
        tracing_ == rhs.tracing_ &&
        diffing_ == rhs.diffing_ &&
        error_handling_ == rhs.error_handling_ &&
        byproduct_output_directory_ == rhs.byproduct_output_directory_ &&
        activity_ == rhs.activity_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<masd::dogen::utility::log::logging_configuration>& configuration::logging() const {
    return logging_;
}

boost::optional<masd::dogen::utility::log::logging_configuration>& configuration::logging() {
    return logging_;
}

void configuration::logging(const boost::optional<masd::dogen::utility::log::logging_configuration>& v) {
    logging_ = v;
}

void configuration::logging(const boost::optional<masd::dogen::utility::log::logging_configuration>&& v) {
    logging_ = std::move(v);
}

const boost::optional<masd::dogen::tracing_configuration>& configuration::tracing() const {
    return tracing_;
}

boost::optional<masd::dogen::tracing_configuration>& configuration::tracing() {
    return tracing_;
}

void configuration::tracing(const boost::optional<masd::dogen::tracing_configuration>& v) {
    tracing_ = v;
}

void configuration::tracing(const boost::optional<masd::dogen::tracing_configuration>&& v) {
    tracing_ = std::move(v);
}

const boost::optional<masd::dogen::diffing_configuration>& configuration::diffing() const {
    return diffing_;
}

boost::optional<masd::dogen::diffing_configuration>& configuration::diffing() {
    return diffing_;
}

void configuration::diffing(const boost::optional<masd::dogen::diffing_configuration>& v) {
    diffing_ = v;
}

void configuration::diffing(const boost::optional<masd::dogen::diffing_configuration>&& v) {
    diffing_ = std::move(v);
}

const boost::optional<masd::dogen::error_handling_configuration>& configuration::error_handling() const {
    return error_handling_;
}

boost::optional<masd::dogen::error_handling_configuration>& configuration::error_handling() {
    return error_handling_;
}

void configuration::error_handling(const boost::optional<masd::dogen::error_handling_configuration>& v) {
    error_handling_ = v;
}

void configuration::error_handling(const boost::optional<masd::dogen::error_handling_configuration>&& v) {
    error_handling_ = std::move(v);
}

const boost::filesystem::path& configuration::byproduct_output_directory() const {
    return byproduct_output_directory_;
}

boost::filesystem::path& configuration::byproduct_output_directory() {
    return byproduct_output_directory_;
}

void configuration::byproduct_output_directory(const boost::filesystem::path& v) {
    byproduct_output_directory_ = v;
}

void configuration::byproduct_output_directory(const boost::filesystem::path&& v) {
    byproduct_output_directory_ = std::move(v);
}

const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& configuration::activity() const {
    return activity_;
}

boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& configuration::activity() {
    return activity_;
}

void configuration::activity(const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>& v) {
    activity_ = v;
}

void configuration::activity(const boost::variant<masd::dogen::cli::generation_configuration, masd::dogen::cli::conversion_configuration, masd::dogen::cli::weaving_configuration>&& v) {
    activity_ = std::move(v);
}

}
