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
#include "dogen.generation/types/transforms/context.hpp"
#include "dogen.archetypes/types/location_repository.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::archetypes::location_repository>& lhs,
const boost::shared_ptr<dogen::archetypes::location_repository>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::feature_model>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::feature_model>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::tracing::tracer>& lhs,
const boost::shared_ptr<dogen::tracing::tracer>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::generation::transforms {

context::context(context&& rhs)
    : archetype_location_repository_(std::move(rhs.archetype_location_repository_)),
      intra_backend_segment_properties_(std::move(rhs.intra_backend_segment_properties_)),
      output_directory_path_(std::move(rhs.output_directory_path_)),
      feature_model_(std::move(rhs.feature_model_)),
      tracer_(std::move(rhs.tracer_)),
      generation_timestamp_(std::move(rhs.generation_timestamp_)) { }

context::context(
    const boost::shared_ptr<dogen::archetypes::location_repository>& archetype_location_repository,
    const std::unordered_map<std::string, dogen::generation::meta_model::intra_backend_segment_properties>& intra_backend_segment_properties,
    const boost::filesystem::path& output_directory_path,
    const boost::shared_ptr<dogen::variability::meta_model::feature_model>& feature_model,
    const boost::shared_ptr<dogen::tracing::tracer>& tracer,
    const std::string& generation_timestamp)
    : archetype_location_repository_(archetype_location_repository),
      intra_backend_segment_properties_(intra_backend_segment_properties),
      output_directory_path_(output_directory_path),
      feature_model_(feature_model),
      tracer_(tracer),
      generation_timestamp_(generation_timestamp) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(archetype_location_repository_, other.archetype_location_repository_);
    swap(intra_backend_segment_properties_, other.intra_backend_segment_properties_);
    swap(output_directory_path_, other.output_directory_path_);
    swap(feature_model_, other.feature_model_);
    swap(tracer_, other.tracer_);
    swap(generation_timestamp_, other.generation_timestamp_);
}

bool context::operator==(const context& rhs) const {
    return archetype_location_repository_ == rhs.archetype_location_repository_ &&
        intra_backend_segment_properties_ == rhs.intra_backend_segment_properties_ &&
        output_directory_path_ == rhs.output_directory_path_ &&
        feature_model_ == rhs.feature_model_ &&
        tracer_ == rhs.tracer_ &&
        generation_timestamp_ == rhs.generation_timestamp_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::archetypes::location_repository>& context::archetype_location_repository() const {
    return archetype_location_repository_;
}

boost::shared_ptr<dogen::archetypes::location_repository>& context::archetype_location_repository() {
    return archetype_location_repository_;
}

void context::archetype_location_repository(const boost::shared_ptr<dogen::archetypes::location_repository>& v) {
    archetype_location_repository_ = v;
}

void context::archetype_location_repository(const boost::shared_ptr<dogen::archetypes::location_repository>&& v) {
    archetype_location_repository_ = std::move(v);
}

const std::unordered_map<std::string, dogen::generation::meta_model::intra_backend_segment_properties>& context::intra_backend_segment_properties() const {
    return intra_backend_segment_properties_;
}

std::unordered_map<std::string, dogen::generation::meta_model::intra_backend_segment_properties>& context::intra_backend_segment_properties() {
    return intra_backend_segment_properties_;
}

void context::intra_backend_segment_properties(const std::unordered_map<std::string, dogen::generation::meta_model::intra_backend_segment_properties>& v) {
    intra_backend_segment_properties_ = v;
}

void context::intra_backend_segment_properties(const std::unordered_map<std::string, dogen::generation::meta_model::intra_backend_segment_properties>&& v) {
    intra_backend_segment_properties_ = std::move(v);
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

const boost::shared_ptr<dogen::variability::meta_model::feature_model>& context::feature_model() const {
    return feature_model_;
}

boost::shared_ptr<dogen::variability::meta_model::feature_model>& context::feature_model() {
    return feature_model_;
}

void context::feature_model(const boost::shared_ptr<dogen::variability::meta_model::feature_model>& v) {
    feature_model_ = v;
}

void context::feature_model(const boost::shared_ptr<dogen::variability::meta_model::feature_model>&& v) {
    feature_model_ = std::move(v);
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

const std::string& context::generation_timestamp() const {
    return generation_timestamp_;
}

std::string& context::generation_timestamp() {
    return generation_timestamp_;
}

void context::generation_timestamp(const std::string& v) {
    generation_timestamp_ = v;
}

void context::generation_timestamp(const std::string&& v) {
    generation_timestamp_ = std::move(v);
}

}
