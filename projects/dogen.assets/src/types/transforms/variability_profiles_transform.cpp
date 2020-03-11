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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.variability/lexical_cast/meta_model/binding_point_lc.hpp"
#include "dogen.variability/lexical_cast/meta_model/template_kind_lc.hpp"
#include "dogen.assets/io/meta_model/model_set_io.hpp"
#include "dogen.assets/types/meta_model/variability/profile.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template.hpp"
#include "dogen.assets/types/transforms/variability_profiles_transform.hpp"

namespace {

const std::string transform_id(
    "assets.transforms.variability_profiles_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string missing_value("Must supply a value for entry: ");
const std::string conflicting_values(
    "Entry has a value as meta-data and as a property: ");

}

namespace dogen::assets::transforms {

void variability_profiles_transform::
update(const features::variability_profile::feature_group& fg,
    meta_model::variability::abstract_profile& ap) {

    using vp = assets::features::variability_profile;
    const auto scfg1(vp::make_static_configuration(fg, ap));
    ap.stereotype(scfg1.stereotype);
}

void variability_profiles_transform::
update(const features::variability_entry::feature_group& fg,
    meta_model::variability::abstract_profile_entry& ape) {

    const auto& k(ape.key());
    BOOST_LOG_SEV(lg, trace) << "Adapting entry: " << k;

    using assets::features::variability_entry;
    const auto scfg(variability_entry::make_static_configuration(fg, ape));

    using boost::lexical_cast;
    using variability::meta_model::template_kind;
    using meta_model::variability::profile_template_entry;
    auto pte(dynamic_cast<profile_template_entry*>(&ape));
    if (pte)
        pte->template_kind(lexical_cast<template_kind>(scfg.template_kind));

    /*
     * FIXME: not yet reading binding point.
     */
    archetypes::location al;
    al.kernel(scfg.kernel);
    al.backend(scfg.backend);
    al.facet(scfg.facet);
    al.archetype(scfg.archetype);

    /*
     * We must supply the value for the entry _either_ via meta-data
     * or via the value attribute; they can't both be empty or both be
     * populated.
     */
    if (!scfg.value.empty() && !ape.value().empty()) {
        BOOST_LOG_SEV(lg, error) << conflicting_values << k;
        BOOST_THROW_EXCEPTION(transformation_error(conflicting_values + k));
    } else if (scfg.value.empty() && ape.value().empty()) {
        BOOST_LOG_SEV(lg, error) << missing_value << k;
        BOOST_THROW_EXCEPTION(transformation_error(missing_value + k));
    }

    if (!scfg.value.empty())
        ape.value(scfg.value);

    BOOST_LOG_SEV(lg, trace) << "Untyped value: " << ape.value();
}

void variability_profiles_transform::process_profile_templates(
    const variability::meta_model::feature_model& fm, meta_model::model& m) {
    /*
     * If there are no profile templates, there is no work to do.
     */
    auto& pts(m.variability_elements().profile_templates());
    if (pts.empty())
        return;

    /*
     * Create feature groups for all required features.
     */
    using features::variability_profile;
    const auto fg1(variability_profile::make_feature_group(fm));

    using features::variability_entry;
    const auto fg2(features::variability_entry::make_feature_group(fm));

    /*
     * Process all profile templates and contained entries.
     */
    for (auto& pair : pts) {
        auto& pt(*pair.second);
        update(fg1, pt);

        for (auto& e : pt.entries())
            update(fg2, e);
    }
}

void variability_profiles_transform::process_profiles(
    const variability::meta_model::feature_model& fm, meta_model::model& m) {
    /*
     * If there are no profiles, there is no work to do.
     */
    auto& ps(m.variability_elements().profiles());
    if (ps.empty())
        return;

    /*
     * Create feature groups for all required features.
     */
    using features::variability_profile;
    const auto fg1(variability_profile::make_feature_group(fm));

    using features::variability_entry;
    const auto fg2(features::variability_entry::make_feature_group(fm));

    /*
     * Process all profile templates and contained entries.
     */
    for (auto& pair : ps) {
        auto& p(*pair.second);
        update(fg1, p);

        for (auto& e : p.entries())
            update(fg2, e);
    }
}

void variability_profiles_transform::
apply(const context& ctx, assets::meta_model::model_set& ms) {
    const auto model_name(ms.target().name().qualified().dot());
    tracing::scoped_transform_tracer stp(lg, "variability profiles",
        transform_id, model_name, *ctx.tracer());

    const auto& fm(*ctx.feature_model());
    const auto lambda(
        [&](auto& model) {
            process_profiles(fm, model);
            process_profile_templates(fm, model);
        });

    lambda(ms.target());
    for (auto& m : ms.references())
        lambda(m);
}

}
