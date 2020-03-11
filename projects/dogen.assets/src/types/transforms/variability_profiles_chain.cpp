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
#include "dogen.variability/types/transforms/profile_binding_transform.hpp"
#include "dogen.variability/types/transforms/profile_repository_production_chain.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.variability/lexical_cast/meta_model/binding_point_lc.hpp"
#include "dogen.variability/lexical_cast/meta_model/template_kind_lc.hpp"
#include "dogen.assets/io/meta_model/model_set_io.hpp"
#include "dogen.assets/types/helpers/profile_adapter.hpp"
#include "dogen.assets/types/meta_model/variability/profile.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template.hpp"
#include "dogen.assets/types/helpers/configuration_model_set_adapter.hpp"
#include "dogen.assets/types/transforms/variability_profiles_chain.hpp"

namespace {

const std::string transform_id(
    "assets.transforms.variability_profiles_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string missing_value("Must supply a value for entry: ");
const std::string duplicate_label("Profile has a duplicate label: ");
const std::string conflicting_values(
    "Entry has a value as meta-data and as a property: ");

}

namespace dogen::assets::transforms {

void variability_profiles_chain::
update(const features::variability_profile::feature_group& fg,
    meta_model::variability::abstract_profile& ap) {

    using vp = assets::features::variability_profile;
    const auto scfg1(vp::make_static_configuration(fg, ap));

    std::unordered_set<std::string> labels;
    for (const auto& l : scfg1.labels) {
        const auto inserted(labels.insert(l).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_label << l;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_label + l));
        }
    }
    ap.labels(labels);
}

void variability_profiles_chain::
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

void variability_profiles_chain::process_profile_templates(
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

void variability_profiles_chain::process_profiles(
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

variability::transforms::context
variability_profiles_chain::adapt(const context& ctx) {
    variability::transforms::context r;
    r.archetype_location_repository(ctx.archetype_location_repository());
    r.tracer(ctx.tracer());
    r.compatibility_mode(ctx.compatibility_mode());
    return r;
}

void variability_profiles_chain::process_all_profiles(
    const variability::meta_model::feature_model& fm,
    meta_model::model_set& ms) {
    /*
     * First process the target.
     */
    process_profiles(fm, ms.target());
    process_profile_templates(fm, ms.target());

    /*
     * Now process the references.
     */
    for (auto& m : ms.references()) {
        process_profiles(fm, m);
        process_profile_templates(fm, m);
    }
}

void variability_profiles_chain::
apply(const context& ctx, assets::meta_model::model_set& ms) {
    const auto model_name(ms.target().name().qualified().dot());
    tracing::scoped_chain_tracer stp(lg, "variability profiles",
        transform_id, model_name, *ctx.tracer());

    /*
     * We start by updating all the profile-like meta-model elements
     * (e.g. profiles and profile templates). This entails reading any
     * associated meta-data and populating the respective attributes
     * with it.
     */
    const auto& fm(*ctx.feature_model());
    process_all_profiles(fm, ms);

    /*
     * Now we adapt all the profile-like elements into their
     * variability counterparts.
     */
    using assets::helpers::profile_adapter;
    const auto pts(profile_adapter::adapt_profile_templates(ms));

    /*
     * If there are no profile-like elements, we have nothing to do.
     */
    if (pts.empty())
        return;

    /*
     * We need to expand all profile templates into proper
     * profiles. We start by creating a repository of all profiles,
     * organised for querying. The chain takes care of instantiating
     * templates into profiles.
     */
    const auto vctx(adapt(ctx));
    using variability::transforms::profile_repository_production_chain;
    const auto prp(profile_repository_production_chain::apply(vctx, pts, fm));

    /*
     * Then we need to extract the configuration models from the
     * assets model set. It is against these that the binding will
     * take place.
     */
    using assets::helpers::configuration_model_set_adapter;
    auto cms(configuration_model_set_adapter::adapt(ms));

    /*
     * Finally, we bind the profiles to the relevant configurations.
     */
    using variability::transforms::profile_binding_transform;
    profile_binding_transform::apply(vctx, fm, prp, cms);
}

}
