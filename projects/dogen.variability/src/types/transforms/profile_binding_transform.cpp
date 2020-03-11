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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.variability/types/helpers/configuration_point_merger.hpp"
#include "dogen.variability/io/meta_model/configuration_io.hpp"
#include "dogen.variability/io/meta_model/configuration_model_io.hpp"
#include "dogen.variability/io/meta_model/configuration_model_set_io.hpp"
#include "dogen.variability/types/transforms/transformation_error.hpp"
#include "dogen.variability/types/transforms/profile_binding_transform.hpp"

namespace {

const std::string
transform_id("variability.transforms.profile_binding_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string profile_field("masd.variability.profile");
const std::string default_root("default.root_module");

const std::string missing_profile(
    "Configuration references a profile that could not be found: ");
const std::string empty_potential_bind_name(
    "Potential bind has an empty name.");
const std::string missing_global_config(
    "Configuration model set does not have global configuration.");
const std::string null_local_config(
    "Configuration model set has a null configuration");
const std::string too_many_base_layers("More than one base layer found: ");
const std::string inconsistent_configuration(
    "Profiles have different base layers: ");

}

namespace dogen::variability::transforms {

profile_binding_transform::feature_group profile_binding_transform::
make_feature_group(const meta_model::feature_model& fm) {
    BOOST_LOG_SEV(lg, debug) << "Creating feature group.";

    feature_group r;
    const helpers::feature_selector s(fm);
    r.profile = s.get_by_name(profile_field);

    BOOST_LOG_SEV(lg, debug) << "Created feature group.";
    return r;
}

std::string profile_binding_transform::
obtain_profile_name(const feature_group& fg,
    const meta_model::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Reading profile name.";
    const helpers::configuration_selector s(cfg);
    std::string r;
    if (s.has_configuration_point(fg.profile))
        r = s.get_text_content(fg.profile);

    BOOST_LOG_SEV(lg, debug) << "Profile name: '" << r << "'";
    return r;
}

std::string
profile_binding_transform::get_default_profile_name_for_binding_point(
    const meta_model::binding_point bp) {
    if (bp == meta_model::binding_point::global)
        return default_root;

    return empty;
}

void profile_binding_transform::handle_potential_bindings(
    const bool has_base_layer, const meta_model::profile_repository& prp,
    meta_model::configuration& cfg) {

    /*
     * This method manages the merging against a set of potential
     * bindings on a configuration. The process is done in three
     * steps.
     *
     * 1. First we determine which potential bindings can be realised
     * into actual profiles.
     *
     * 2. For the realisable profiles, accumulate all of the
     * configuration points which are not related to the base
     * layer. These are stored into the accumulating_profile.
     *
     * 3. Finally, merge against the configuration. This must be done
     * in order: first the accumulating_profile, the base layer. This
     * ordering is *highly* non-intuitive. It derives from the fact
     * that, on a merge, lhs takes precedence over rhs. If we merge
     * the base layer first, as it is logical, this would mean that
     * the "overrides" would fail to override for all of the features
     * that the base layer has already set. Clearly base layer is not
     * a good name here; its more of a "default feature configuration"
     * or something of the sort.
     *
     */
    unsigned int bind_count(0);
    std::string base_layer_name;
    helpers::configuration_point_merger mg;
    meta_model::profile accumulating_profile;
    accumulating_profile.name().simple("accumulating_profile");
    accumulating_profile.name().qualified("accumulating_profile");
    for (auto& pb : cfg.profile_bindings()) {
        /*
         * Potential bind must have some kind of name.
         */
        const auto& pbn(pb.name());
        if (pbn.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_potential_bind_name;
            BOOST_THROW_EXCEPTION(
                transformation_error(empty_potential_bind_name));
        }

        /*
         * Check to see if the potential bind matches any of the
         * profiles on our repository, by stereotype - i.e. can be
         * "realised". If not, its not one of ours so we''re done.'
         */
        BOOST_LOG_SEV(lg, trace) << "Processing potential bind: " << pbn;
        const auto i(prp.by_stereotype().find(pbn));
        if (i == prp.by_stereotype().end()) {
            BOOST_LOG_SEV(lg, trace) << "Binding not realised.";
            continue;
        }
        pb.realized(true);
        ++bind_count;

        /*
         * Now handle the base profile layer for this profile, if any
         * exists. Its fine for a profile not to have a base layer
         * too.
         */
        const auto profile(i->second);
        const auto prf_bl(profile.base_layer_profile());
        if (!prf_bl.empty()) {
            /*
             * If the configuration had already requested a base
             * layer, we cannot allow it to bind to profiles that also
             * request base layers.
             */
            if (has_base_layer) {
                BOOST_LOG_SEV(lg, error) << too_many_base_layers << prf_bl;
                BOOST_THROW_EXCEPTION(
                    transformation_error(too_many_base_layers + prf_bl));
            }

            /*
             * If we have not yet seen a base layer, we just need to
             * remember its name.
             */
            if (base_layer_name.empty()) {
                base_layer_name = prf_bl;
                BOOST_LOG_SEV(lg, trace) << "Base layer name: "
                                         << base_layer_name;

            } else if (prf_bl != base_layer_name) {
                /*
                 * If we already had a base layer in this batch of
                 * profiles, they must all be the same; we cannot
                 * allow profiles to mix and match base layers.
                 */
                BOOST_LOG_SEV(lg, error) << inconsistent_configuration << prf_bl
                                         << " Previous base layer: "
                                         << base_layer_name;
                BOOST_THROW_EXCEPTION(
                    transformation_error(inconsistent_configuration + prf_bl));
            }
        } else
            BOOST_LOG_SEV(lg, trace) << "Profile has no Base layer.";

        /*
         * Merge the profile itself into the accumulating profile.
         */
        const auto cps(mg.merge(
                accumulating_profile.name().qualified(),
                accumulating_profile.configuration_points(),
                profile.name().qualified(),
                profile.configuration_points()));
        accumulating_profile.configuration_points(cps);
    }

    /*
     * Now we can merge against the configuration. First we merge the
     * accumulating profile.
     */
    if (!accumulating_profile.configuration_points().empty()) {
        BOOST_LOG_SEV(lg, trace) << "Merging accumulated profile.";
        const auto cps(mg.merge(cfg.name().qualified(),
                cfg.configuration_points(),
                accumulating_profile.name().qualified(),
                accumulating_profile.configuration_points()));
        cfg.configuration_points(cps);

        BOOST_LOG_SEV(lg, trace) << "Total potential bindings: "
                                 << cfg.profile_bindings().size()
                                 << " Realised bindings: " << bind_count;
    } else
        BOOST_LOG_SEV(lg, trace) << "Accumulated profile is empty.";

    /*
     * Finally, we merge the base layer, if one was supplied. Note
     * that if the user requested it specifically, it must exist on
     * our profile repository.
     */
    if (!base_layer_name.empty()) {
        BOOST_LOG_SEV(lg, trace) << "Merging profile's base layer: "
                                 << base_layer_name;
        const auto i(prp.by_name().find(base_layer_name));
        if (i == prp.by_name().end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile << base_layer_name;
            BOOST_THROW_EXCEPTION(
                transformation_error(missing_profile + base_layer_name));
        }

        const auto& base_layer_profile(i->second);
        const auto cps(mg.merge(
                cfg.name().qualified(),
                cfg.configuration_points(),
                base_layer_profile.name().qualified(),
                base_layer_profile.configuration_points()));
        cfg.configuration_points(cps);
    } else
        BOOST_LOG_SEV(lg, trace) << "No base layer found on all profiles.";
}

void profile_binding_transform::bind(const meta_model::profile_repository& prp,
    const feature_group& fg, meta_model::configuration& cfg) {
    BOOST_LOG_SEV(lg, debug) << "Started binding profiles for configuration: "
                             << cfg.name().qualified();

    /*
     * If a base layer profile name was specified via the meta-data at
     * the configuration level, it must exist on our profile
     * collection. Locate it, merge it with the original annotation
     * and return that. This is the case, for example, for the root
     * module.
     */
    bool has_base_layer(false);
    const auto cfg_bl(obtain_profile_name(fg, cfg));
    if (!cfg_bl.empty()) {
        BOOST_LOG_SEV(lg, trace) << "Configured base layer profile: "
                                 << cfg_bl;
        const auto i(prp.by_name().find(cfg_bl));
        if (i == prp.by_name().end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile << cfg_bl;
            BOOST_THROW_EXCEPTION(
                transformation_error(missing_profile + cfg_bl));
        }

        helpers::configuration_point_merger mg;
        const auto profile(i->second);
        const auto cps(mg.merge(
                cfg.name().qualified(),
                cfg.configuration_points(),
                profile.name().qualified(),
                profile.configuration_points()));
        cfg.configuration_points(cps);
        has_base_layer = true;
        BOOST_LOG_SEV(lg, trace) << "Merged profile.";
    } else
        BOOST_LOG_SEV(lg, trace) << "Profile not set in meta-data.";

    /*
     * Now handle the potential bindings specified for this
     * configuration.
     */
    handle_potential_bindings(has_base_layer, prp, cfg);

    /*
     * If no profile name was found by now, we need to try looking for
     * the well-known default profiles, based on the scope of the
     * annotation. Not all scope types have a mapping, and the default
     * profiles do not necessarily exist.
     */
    const auto bp(cfg.source_binding_point());
    const auto def_profn(get_default_profile_name_for_binding_point(bp));
    if (!def_profn.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Looking for default profile: "
                                 << def_profn;

        const auto i(prp.by_name().find(def_profn));
        if (i != prp.by_name().end()) {
            helpers::configuration_point_merger mg;
            const auto profile(i->second);
            const auto cps(mg.merge(
                    cfg.name().qualified(),
                    cfg.configuration_points(),
                    profile.name().qualified(),
                    profile.configuration_points()));
            cfg.configuration_points(cps);
        }
    } else
        BOOST_LOG_SEV(lg, debug) << "Scope does not have a default profile.";

    /*
     * If we could find nothing suitable, just return the original.
     */
    // BOOST_LOG_SEV(lg, debug) << "No profiles found, using original.";
}

void profile_binding_transform::apply(const meta_model::profile_repository& prp,
    const meta_model::feature_model& fm, meta_model::configuration_model& cm) {
    /*
     * All configuration models must have a global configuration set.
     */
    if (!cm.global()) {
        BOOST_LOG_SEV(lg, error) << missing_global_config;
        BOOST_THROW_EXCEPTION(transformation_error(missing_global_config));
    }

    const auto fg(make_feature_group(fm));
    bind(prp, fg, *cm.global());

    for (auto& pair : cm.local()) {
        /*
         * Local configurations cannot be null.
         */
        if (!pair.second) {
            BOOST_LOG_SEV(lg, error) << null_local_config;
            BOOST_THROW_EXCEPTION(transformation_error(null_local_config));
        }

        auto& cfg(*pair.second);
        bind(prp, fg, cfg);
    }
}

void profile_binding_transform::apply(const context& ctx,
    const meta_model::feature_model& fm,
    const meta_model::profile_repository& prp,
    meta_model::configuration_model_set& cms) {
    tracing::scoped_transform_tracer stp(lg,  "profile binding transform",
        transform_id, *ctx.tracer(), cms);

    for (auto& cm : cms.models())
        apply(prp, fm, cm);

    stp.end_transform(cms);
}

}
