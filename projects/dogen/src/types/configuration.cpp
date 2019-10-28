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
#include "dogen/types/configuration.hpp"

namespace dogen {

configuration::configuration(configuration&& rhs)
    : model_processing_(std::move(rhs.model_processing_)),
      tracing_(std::move(rhs.tracing_)),
      diffing_(std::move(rhs.diffing_)),
      reporting_(std::move(rhs.reporting_)),
      byproduct_directory_(std::move(rhs.byproduct_directory_)),
      database_(std::move(rhs.database_)) { }

configuration::configuration(
    const dogen::model_processing_configuration& model_processing,
    const boost::optional<dogen::tracing_configuration>& tracing,
    const boost::optional<dogen::diffing_configuration>& diffing,
    const boost::optional<dogen::reporting_configuration>& reporting,
    const boost::filesystem::path& byproduct_directory,
    const boost::optional<dogen::database_configuration>& database)
    : model_processing_(model_processing),
      tracing_(tracing),
      diffing_(diffing),
      reporting_(reporting),
      byproduct_directory_(byproduct_directory),
      database_(database) { }

void configuration::swap(configuration& other) noexcept {
    using std::swap;
    swap(model_processing_, other.model_processing_);
    swap(tracing_, other.tracing_);
    swap(diffing_, other.diffing_);
    swap(reporting_, other.reporting_);
    swap(byproduct_directory_, other.byproduct_directory_);
    swap(database_, other.database_);
}

bool configuration::operator==(const configuration& rhs) const {
    return model_processing_ == rhs.model_processing_ &&
        tracing_ == rhs.tracing_ &&
        diffing_ == rhs.diffing_ &&
        reporting_ == rhs.reporting_ &&
        byproduct_directory_ == rhs.byproduct_directory_ &&
        database_ == rhs.database_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::model_processing_configuration& configuration::model_processing() const {
    return model_processing_;
}

dogen::model_processing_configuration& configuration::model_processing() {
    return model_processing_;
}

configuration& configuration::model_processing(const dogen::model_processing_configuration& v) {
    model_processing_ = v;
    return *this;
}

configuration& configuration::model_processing(const dogen::model_processing_configuration&& v) {
    model_processing_ = std::move(v);
    return *this;
}

const boost::optional<dogen::tracing_configuration>& configuration::tracing() const {
    return tracing_;
}

boost::optional<dogen::tracing_configuration>& configuration::tracing() {
    return tracing_;
}

configuration& configuration::tracing(const boost::optional<dogen::tracing_configuration>& v) {
    tracing_ = v;
    return *this;
}

configuration& configuration::tracing(const boost::optional<dogen::tracing_configuration>&& v) {
    tracing_ = std::move(v);
    return *this;
}

const boost::optional<dogen::diffing_configuration>& configuration::diffing() const {
    return diffing_;
}

boost::optional<dogen::diffing_configuration>& configuration::diffing() {
    return diffing_;
}

configuration& configuration::diffing(const boost::optional<dogen::diffing_configuration>& v) {
    diffing_ = v;
    return *this;
}

configuration& configuration::diffing(const boost::optional<dogen::diffing_configuration>&& v) {
    diffing_ = std::move(v);
    return *this;
}

const boost::optional<dogen::reporting_configuration>& configuration::reporting() const {
    return reporting_;
}

boost::optional<dogen::reporting_configuration>& configuration::reporting() {
    return reporting_;
}

configuration& configuration::reporting(const boost::optional<dogen::reporting_configuration>& v) {
    reporting_ = v;
    return *this;
}

configuration& configuration::reporting(const boost::optional<dogen::reporting_configuration>&& v) {
    reporting_ = std::move(v);
    return *this;
}

const boost::filesystem::path& configuration::byproduct_directory() const {
    return byproduct_directory_;
}

boost::filesystem::path& configuration::byproduct_directory() {
    return byproduct_directory_;
}

configuration& configuration::byproduct_directory(const boost::filesystem::path& v) {
    byproduct_directory_ = v;
    return *this;
}

configuration& configuration::byproduct_directory(const boost::filesystem::path&& v) {
    byproduct_directory_ = std::move(v);
    return *this;
}

const boost::optional<dogen::database_configuration>& configuration::database() const {
    return database_;
}

boost::optional<dogen::database_configuration>& configuration::database() {
    return database_;
}

configuration& configuration::database(const boost::optional<dogen::database_configuration>& v) {
    database_ = v;
    return *this;
}

configuration& configuration::database(const boost::optional<dogen::database_configuration>&& v) {
    database_ = std::move(v);
    return *this;
}

}
