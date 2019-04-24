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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_point_merger.hpp"
#include "masd.dogen.variability/io/meta_model/configuration_io.hpp"
#include "masd.dogen.variability/io/meta_model/configuration_model_io.hpp"
#include "masd.dogen.variability/types/transforms/transformation_error.hpp"
#include "masd.dogen.variability/types/transforms/profile_binding_transform.hpp"

namespace {

const std::string
transform_id("variability.transforms.profile_binding_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string profile_field("masd.annotations.profile");
const std::string default_root("default.root_module");

const std::string missing_profile(
    "Configuration references a profile that could not be found: ");
const std::string too_many_binds(
    "Too many candidate labels bind to a profile: ");

}

namespace masd::dogen::variability::transforms {

profile_binding_transform::feature_group profile_binding_transform::
make_feature_group(const meta_model::feature_model& fm) {
    BOOST_LOG_SEV(lg, debug) << "Creating feature group.";

    profile_binding_transform::feature_group r;
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

std::list<std::string>
profile_binding_transform::get_bindable_profile_names(
    const meta_model::profile_repository& prp,
    const std::unordered_set<std::string>& candidates)  {

    std::list<std::string> r;
    for (const auto& c : candidates) {
        if (prp.by_labels().find(c) != prp.by_labels().end())
            r.push_back(c);
    }
    return r;
}

void profile_binding_transform::bind(const meta_model::profile_repository& prp,
    const feature_group& fg, meta_model::configuration& cfg) {
    BOOST_LOG_SEV(lg, debug) << "Started binding profiles for configuration: "
                             << cfg.name().qualified();
    BOOST_LOG_SEV(lg, trace) << "Original: " << cfg;

    /*
     * If a profile name was specified via the meta-data, it must
     * exist on our profile collection. Locate it, merge it with the
     * original annotation and return that.
     */
    const auto profn(obtain_profile_name(fg, cfg));
    if (!profn.empty()) {
        BOOST_LOG_SEV(lg, trace) << "Configured profile: " << profn;
        const auto i(prp.by_name().find(profn));
        if (i == prp.by_name().end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile << profn;
            BOOST_THROW_EXCEPTION(
                transformation_error(missing_profile + profn));
        }

        helpers::configuration_point_merger mg;
        const auto profile(i->second);
        const auto cps(mg.merge(
                cfg.name().qualified(),
                cfg.configuration_points(),
                profile.name().qualified(),
                profile.configuration_points()));
        cfg.configuration_points(cps);
        BOOST_LOG_SEV(lg, trace) << "After Merging profile: " << cfg;
    } else
        BOOST_LOG_SEV(lg, trace) << "Profile not set in meta-data.";

    /*
     * Lets try to see if any of the candidate labels binds to a
     * profile. We only allow one to bind at most.
     */
    const auto bpfn(get_bindable_profile_names(prp, cfg.profile_bindings()));
    if (bpfn.size() > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_binds << bpfn;
        BOOST_THROW_EXCEPTION(transformation_error(too_many_binds));
    }

    for (const auto& bl : bpfn) {
        BOOST_LOG_SEV(lg, debug) << "Bound label: " << bl;
        const auto i(prp.by_labels().find(bl));
        if (i == prp.by_labels().end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile << bl;
            BOOST_THROW_EXCEPTION(transformation_error(missing_profile + bl));
        }

        helpers::configuration_point_merger mg;
        const auto profile(i->second);
        const auto cps(mg.merge(
                cfg.name().qualified(),
                cfg.configuration_points(),
                profile.name().qualified(),
                profile.configuration_points()));
        cfg.configuration_points(cps);
        BOOST_LOG_SEV(lg, debug) << "Merged profile: " << cfg;
    }

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
            BOOST_LOG_SEV(lg, debug) << "Merged profile: " << cfg;
        }
    } else
        BOOST_LOG_SEV(lg, debug) << "Scope does not have a default profile.";

    /*
     * If we could find nothing suitable, just return the original.
     */
    BOOST_LOG_SEV(lg, debug) << "No profiles found, using original.";
}

void profile_binding_transform::apply(const context& ctx,
    const meta_model::profile_repository& prp,
    const meta_model::feature_model& fm,
    meta_model::configuration_model& cm) {
    tracing::scoped_transform_tracer stp(lg, "profile binding transform",
        transform_id, transform_id, *ctx.tracer(), cm);

    const auto fg(make_feature_group(fm));
    bind(prp, fg, *cm.global());

    for (auto& pair : cm.local()) {
        auto& cfg(*pair.second);
        bind(prp, fg, cfg);
    }

    stp.end_transform(cm);
}

}
