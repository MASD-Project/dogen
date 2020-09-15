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
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::feature_model>& lhs,
const boost::shared_ptr<dogen::variability::entities::feature_model>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::physical::entities::meta_model>& lhs,
const boost::shared_ptr<dogen::physical::entities::meta_model>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::tracing::tracer>& lhs,
const boost::shared_ptr<dogen::tracing::tracer>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::physical::transforms {

context::context()
    : dry_run_mode_enabled_(static_cast<bool>(0)) { }

context::context(context&& rhs)
    : diffing_configuration_(std::move(rhs.diffing_configuration_)),
      reporting_configuration_(std::move(rhs.reporting_configuration_)),
      dry_run_mode_enabled_(std::move(rhs.dry_run_mode_enabled_)),
      feature_model_(std::move(rhs.feature_model_)),
      meta_model_(std::move(rhs.meta_model_)),
      tracer_(std::move(rhs.tracer_)),
      output_directory_path_(std::move(rhs.output_directory_path_)) { }

context::context(
    const boost::optional<dogen::diffing_configuration>& diffing_configuration,
    const boost::optional<dogen::reporting_configuration>& reporting_configuration,
    const bool dry_run_mode_enabled,
    const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model,
    const boost::shared_ptr<dogen::physical::entities::meta_model>& meta_model,
    const boost::shared_ptr<dogen::tracing::tracer>& tracer,
    const boost::filesystem::path& output_directory_path)
    : diffing_configuration_(diffing_configuration),
      reporting_configuration_(reporting_configuration),
      dry_run_mode_enabled_(dry_run_mode_enabled),
      feature_model_(feature_model),
      meta_model_(meta_model),
      tracer_(tracer),
      output_directory_path_(output_directory_path) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(diffing_configuration_, other.diffing_configuration_);
    swap(reporting_configuration_, other.reporting_configuration_);
    swap(dry_run_mode_enabled_, other.dry_run_mode_enabled_);
    swap(feature_model_, other.feature_model_);
    swap(meta_model_, other.meta_model_);
    swap(tracer_, other.tracer_);
    swap(output_directory_path_, other.output_directory_path_);
}

bool context::operator==(const context& rhs) const {
    return diffing_configuration_ == rhs.diffing_configuration_ &&
        reporting_configuration_ == rhs.reporting_configuration_ &&
        dry_run_mode_enabled_ == rhs.dry_run_mode_enabled_ &&
        feature_model_ == rhs.feature_model_ &&
        meta_model_ == rhs.meta_model_ &&
        tracer_ == rhs.tracer_ &&
        output_directory_path_ == rhs.output_directory_path_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::diffing_configuration>& context::diffing_configuration() const {
    return diffing_configuration_;
}

boost::optional<dogen::diffing_configuration>& context::diffing_configuration() {
    return diffing_configuration_;
}

void context::diffing_configuration(const boost::optional<dogen::diffing_configuration>& v) {
    diffing_configuration_ = v;
}

void context::diffing_configuration(const boost::optional<dogen::diffing_configuration>&& v) {
    diffing_configuration_ = std::move(v);
}

const boost::optional<dogen::reporting_configuration>& context::reporting_configuration() const {
    return reporting_configuration_;
}

boost::optional<dogen::reporting_configuration>& context::reporting_configuration() {
    return reporting_configuration_;
}

void context::reporting_configuration(const boost::optional<dogen::reporting_configuration>& v) {
    reporting_configuration_ = v;
}

void context::reporting_configuration(const boost::optional<dogen::reporting_configuration>&& v) {
    reporting_configuration_ = std::move(v);
}

bool context::dry_run_mode_enabled() const {
    return dry_run_mode_enabled_;
}

void context::dry_run_mode_enabled(const bool v) {
    dry_run_mode_enabled_ = v;
}

const boost::shared_ptr<dogen::variability::entities::feature_model>& context::feature_model() const {
    return feature_model_;
}

boost::shared_ptr<dogen::variability::entities::feature_model>& context::feature_model() {
    return feature_model_;
}

void context::feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>& v) {
    feature_model_ = v;
}

void context::feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>&& v) {
    feature_model_ = std::move(v);
}

const boost::shared_ptr<dogen::physical::entities::meta_model>& context::meta_model() const {
    return meta_model_;
}

boost::shared_ptr<dogen::physical::entities::meta_model>& context::meta_model() {
    return meta_model_;
}

void context::meta_model(const boost::shared_ptr<dogen::physical::entities::meta_model>& v) {
    meta_model_ = v;
}

void context::meta_model(const boost::shared_ptr<dogen::physical::entities::meta_model>&& v) {
    meta_model_ = std::move(v);
}

const boost::shared_ptr<dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

boost::shared_ptr<dogen::tracing::tracer>& context::tracer() {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>& v) {
    tracer_ = v;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v) {
    tracer_ = std::move(v);
}

const boost::filesystem::path& context::output_directory_path() const {
    return output_directory_path_;
}

boost::filesystem::path& context::output_directory_path() {
    return output_directory_path_;
}

void context::output_directory_path(const boost::filesystem::path& v) {
    output_directory_path_ = v;
}

void context::output_directory_path(const boost::filesystem::path&& v) {
    output_directory_path_ = std::move(v);
}

}
