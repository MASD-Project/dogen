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
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.variability/lexical_cast/entities/binding_point_lc.hpp"
#include "dogen.logical/io/entities/input_model_set_io.hpp"
#include "dogen.logical/types/entities/variability/profile.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/entities/variability/profile_template.hpp"
#include "dogen.logical/types/transforms/variability_profiles_transform.hpp"

namespace {

const std::string transform_id(
    "logical.transforms.variability_profiles_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string dot(".");
const std::string empty_domain("Domain name cannot be empty: ");
const std::string missing_value("Must supply a value for entry: ");
const std::string conflicting_values(
    "Entry has a value as meta-data and as a property: ");

}

namespace dogen::logical::transforms {

std::string variability_profiles_transform::
compute_key(const std::string& key_prefix, const std::string& original_key) {
    /*
     * If a key prefix was supplied, we must merge the original key
     * with the key prefix. Otherwise, use the original key as the
     * key.
     */
    if (!key_prefix.empty())
        return key_prefix + dot + original_key;

    return original_key;
}

void variability_profiles_transform::
update(const features::variability_entry::feature_group& fg,
    entities::variability::abstract_profile_entry& ape) {
    const auto& k(ape.key());
    BOOST_LOG_SEV(lg, trace) << "Adapting entry: " << k;

    using logical::features::variability_entry;
    const auto scfg(variability_entry::make_static_configuration(fg, ape));

    using boost::lexical_cast;
    using entities::variability::profile_template_entry;
    auto pte(dynamic_cast<profile_template_entry*>(&ape));
    if (pte) {
        if (scfg.instantiation_domain_name.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_domain << k;
            BOOST_THROW_EXCEPTION(transformation_error(empty_domain + k));
        }
        pte->instantiation_domain_name(scfg.instantiation_domain_name);
    }

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
    const variability::entities::feature_model& fm, entities::model& m) {
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
    using vp = logical::features::variability_profile;
    for (auto& pair : pts) {
        auto& pt(*pair.second);
        const auto scfg(vp::make_static_configuration(fg1, pt));
        pt.stereotype(scfg.stereotype);
        pt.key_prefix(scfg.key_prefix);

        for (auto& e : pt.entries()) {
            e.key(compute_key(pt.key_prefix(), e.original_key()));
            update(fg2, e);
        }
    }
}

void variability_profiles_transform::process_profiles(
    const variability::entities::feature_model& fm, entities::model& m) {
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
    using vp = logical::features::variability_profile;
    for (auto& pair : ps) {
        auto& p(*pair.second);
        const auto scfg(vp::make_static_configuration(fg1, p));
        p.stereotype(scfg.stereotype);
        p.key_prefix(scfg.key_prefix);
        p.binding_point(scfg.binding_point);

        for (auto& e : p.entries()) {
            e.key(compute_key(p.key_prefix(), e.original_key()));
            update(fg2, e);
        }
    }
}

void variability_profiles_transform::
apply(const context& ctx, logical::entities::input_model_set& ms) {
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
