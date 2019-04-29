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
#include "masd.dogen.extraction/types/transforms/context.hpp"

namespace masd::dogen::extraction::transforms {

context::context()
    : use_configuration_(false) {}

context::context(
    const bool use_configuration,
    const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& feature_model,
    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer,
    const boost::optional<masd::dogen::diffing_configuration>& diffing_configuration,
    const boost::optional<masd::dogen::reporting_configuration>& reporting_configuration,
    const bool dry_run_mode_enabled)
    : use_configuration_(use_configuration),
      feature_model_(feature_model),
      tracer_(tracer),
      diffing_configuration_(diffing_configuration),
      reporting_configuration_(reporting_configuration),
      dry_run_mode_enabled_(dry_run_mode_enabled) { }

bool context::use_configuration() const {
    return use_configuration_;
}

void context::use_configuration(const bool v) {
    use_configuration_ = v;
}

const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& context::feature_model() const {
    return feature_model_;
}

void context::feature_model(const boost::shared_ptr<masd::dogen::variability::meta_model::feature_model>& v) {
    feature_model_ = v;
}

const boost::shared_ptr<masd::dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v) {
    tracer_ = v;
}

const boost::optional<masd::dogen::diffing_configuration>& context::diffing_configuration() const {
    return diffing_configuration_;
}

void context::diffing_configuration(const boost::optional<masd::dogen::diffing_configuration>& v) {
    diffing_configuration_ = v;
}

const boost::optional<masd::dogen::reporting_configuration>& context::reporting_configuration() const {
    return reporting_configuration_;
}

void context::reporting_configuration(const boost::optional<masd::dogen::reporting_configuration>& v) {
    reporting_configuration_ = v;
}

bool context::dry_run_mode_enabled() const {
    return dry_run_mode_enabled_;
}

void context::dry_run_mode_enabled(const bool v) {
    dry_run_mode_enabled_ = v;
}

}
