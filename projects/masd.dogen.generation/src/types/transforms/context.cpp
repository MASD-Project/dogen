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
#include "masd.dogen.tracing/types/tracer.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.generation/types/transforms/context.hpp"
#include "masd.dogen.variability/types/annotation_factory.hpp"
#include "masd.dogen.variability/types/annotation_expander.hpp"
#include "masd.dogen.archetypes/types/location_repository.hpp"

namespace masd::dogen::generation::transforms {

context::context()
    : use_configuration_(false) {}

context::context(
    const bool use_configuration,
    const boost::shared_ptr<masd::dogen::variability::type_repository>& type_repository,
    const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& feature_model,
    const boost::shared_ptr<masd::dogen::archetypes::location_repository>& archetype_location_repository,
    const boost::shared_ptr<masd::dogen::variability::annotation_factory>& annotation_factory,
    const boost::shared_ptr<masd::dogen::variability::annotation_expander>& annotation_expander,
    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer,
    const std::unordered_map<std::string, masd::dogen::generation::meta_model::intra_backend_segment_properties>& intra_backend_segment_properties,
    const boost::filesystem::path& output_directory_path)
    : use_configuration_(use_configuration),
      type_repository_(type_repository),
      feature_model_(feature_model),
      archetype_location_repository_(archetype_location_repository),
      annotation_factory_(annotation_factory),
      annotation_expander_(annotation_expander),
      tracer_(tracer),
      intra_backend_segment_properties_(intra_backend_segment_properties),
      output_directory_path_(output_directory_path) { }

bool context::use_configuration() const {
    return use_configuration_;
}

void context::use_configuration(const bool v) {
    use_configuration_ = v;
}

const boost::shared_ptr<masd::dogen::variability::type_repository>& context::type_repository() const {
    return type_repository_;
}

void context::type_repository(const boost::shared_ptr<masd::dogen::variability::type_repository>& v) {
    type_repository_ = v;
}

const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& context::feature_model() const {
    return feature_model_;
}

void context::feature_model(const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& v) {
    feature_model_ = v;
}

const boost::shared_ptr<masd::dogen::archetypes::location_repository>& context::archetype_location_repository() const {
    return archetype_location_repository_;
}

void context::archetype_location_repository(const boost::shared_ptr<masd::dogen::archetypes::location_repository>& v) {
    archetype_location_repository_ = v;
}

const boost::shared_ptr<masd::dogen::variability::annotation_factory>& context::annotation_factory() const {
    return annotation_factory_;
}

void context::annotation_factory(const boost::shared_ptr<masd::dogen::variability::annotation_factory>& v) {
    annotation_factory_ = v;
}

const boost::shared_ptr<masd::dogen::variability::annotation_expander>& context::annotation_expander() const {
    return annotation_expander_;
}

void context::annotation_expander(const boost::shared_ptr<masd::dogen::variability::annotation_expander>& v) {
    annotation_expander_ = v;
}

const boost::shared_ptr<masd::dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v) {
    tracer_ = v;
}

const std::unordered_map<std::string, masd::dogen::generation::meta_model::intra_backend_segment_properties>& context::intra_backend_segment_properties() const {
    return intra_backend_segment_properties_;
}

void context::intra_backend_segment_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::intra_backend_segment_properties>& v) {
    intra_backend_segment_properties_ = v;
}

const boost::filesystem::path& context::output_directory_path() const {
    return output_directory_path_;
}

void context::output_directory_path(const boost::filesystem::path& v) {
    output_directory_path_ = v;
}

}
