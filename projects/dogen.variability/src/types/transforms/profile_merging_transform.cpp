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
#include "dogen.variability/io/entities/profile_io.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.variability/io/entities/profile_repository_io.hpp"
#include "dogen.variability/types/helpers/configuration_point_merger.hpp"
#include "dogen.variability/types/transforms/transformation_error.hpp"
#include "dogen.variability/types/transforms/profile_merging_transform.hpp"

namespace {

const std::string transform_id(
    "variability.transforms.profile_merging_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_profile_name("Duplicate profile name: ");
const std::string no_profiles("Expected at least one profile.");
const std::string profile_not_found("Profile not found: ");
const std::string parent_not_found(
    "Parent not found in profile container: ");
const std::string duplicate_stereotype(
    "Stereotype used by more than one profile: ");
const std::string profile_field("masd.variability.profile");

}

namespace dogen::variability::transforms {

profile_merging_transform::feature_group profile_merging_transform::
make_feature_group(const entities::feature_model& fm) {
    BOOST_LOG_SEV(lg, debug) << "Creating feature group.";

    feature_group r;
    const helpers::feature_selector s(fm);
    r.profile = s.get_by_name(profile_field);

    BOOST_LOG_SEV(lg, debug) << "Created feature group.";
    return r;
}

std::string
profile_merging_transform::obtain_profile_name(const feature_group& fg,
    const entities::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Reading profile name.";
    const helpers::configuration_selector s(cfg);
    std::string r;
    if (s.has_configuration_point(fg.profile))
        r = s.get_text_content(fg.profile);

    BOOST_LOG_SEV(lg, debug) << "Profile name: '" << r << "'";
    return r;
}


const entities::profile& profile_merging_transform::
walk_up_parent_tree_and_merge(const std::string& current,
    std::unordered_map<std::string, entities::profile>& pm) {
    BOOST_LOG_SEV(lg, debug) << "Merging profile: " << current;

    /*
     * Locate the original state of the current. It must exist due to
     * validation, but just in case we check.
     */
    const auto i(pm.find(current));
    if (i == pm.end()) {
        BOOST_LOG_SEV(lg, error) << profile_not_found << current;
        BOOST_THROW_EXCEPTION(
            transformation_error(profile_not_found + current));
    }

    auto& prf(i->second);
    /*
     *  If we're already merged then there is nothing to do.
     */
    if (prf.merged()) {
        BOOST_LOG_SEV(lg, debug) << "Already merged.";
        return prf;
    }

    /*
     * If we have no parents then we're done.
     */
    if (prf.parents().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No parents so nothing to merge.";
        prf.merged(true);
        return prf;
    }

    /*
     * Merge current with each of its parents. If they haven't been
     * merged yet, recursion will take care of it.
     */
    for (const auto parent_name : prf.parents()) {
        BOOST_LOG_SEV(lg, debug) << "Parent: " << parent_name;
        const auto parent(walk_up_parent_tree_and_merge(parent_name, pm));
        helpers::configuration_point_merger mg;
        prf.configuration_points(
            mg.merge(prf.name().qualified(),
                prf.configuration_points(),
                parent.name().qualified(),
                parent.configuration_points()));
        prf.merged(true);
    }

    BOOST_LOG_SEV(lg, debug) << "Done merging profile.";
    return i->second;
}

std::unordered_map<std::string, entities::profile> profile_merging_transform::
create_profile_map(const std::list<entities::profile>& profiles) {
    std::unordered_map<std::string, entities::profile> r;
    for (const auto& prf : profiles) {
        const auto prfn(prf.name().qualified());
        const auto pair(std::make_pair(prfn, prf));
        const auto inserted(r.insert(pair).second);
        if (inserted)
            continue;

        /*
         * Profile names must be globally unique. Stereotypes too,
         * though we check that elsewhere.
         */
        BOOST_LOG_SEV(lg, warn) << duplicate_profile_name << prfn;
        BOOST_THROW_EXCEPTION(
            transformation_error(duplicate_profile_name + prfn));
    }
    return r;
}

void profile_merging_transform::
validate(const std::unordered_map<std::string, entities::profile>& pm) {
    BOOST_LOG_SEV(lg, debug) << "Validating profiles.";
    /*
     * We expect at least one profile. If there are no profiles, there
     * is no need to execute this transform or its containing chain.
     */
    if (pm.empty()) {
        BOOST_LOG_SEV(lg, error) << no_profiles;
        BOOST_THROW_EXCEPTION(transformation_error(no_profiles));
    }

    for (const auto& pair : pm) {
        const auto& prfn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Validating profile: " << prfn;

        /*
         * All parents must exist in the container.
         */
        const auto& prf(pair.second);
        for (const auto parent : prf.parents()) {
            const auto i(pm.find(parent));
            if (i == pm.end()) {
                BOOST_LOG_SEV(lg, error) << parent_not_found << parent;
                BOOST_THROW_EXCEPTION(
                    transformation_error(parent_not_found + parent));
            }

            /*
             * Note that configuration point templates have been
             * validated by the instantiator, so we neeed not bother
             * here.
             */
        }

        /*
         * Stereotypes can be empty - e.g. for when we are creating
         * base profiles that are designed to be inherited from and
         * not used directly. However, since this could have been done
         * by mistake, might as well log something so that we can at
         * least grep for it.
         */
        if (prf.stereotype().empty()) {
            BOOST_LOG_SEV(lg, warn) << "Profile has an empty stereotype: "
                                    << prfn;
        }

        BOOST_LOG_SEV(lg, debug) << "Validated profile.";
    }
    BOOST_LOG_SEV(lg, debug) << "Validated all profiles.";
}

void profile_merging_transform::
merge(std::unordered_map<std::string, entities::profile>& pm) {
    BOOST_LOG_SEV(lg, debug) << "Merging profiles. Total: " << pm.size();
    for (const auto& pair : pm) {
        const auto current(pair.first);
        walk_up_parent_tree_and_merge(current, pm);
    }
    BOOST_LOG_SEV(lg, debug) << "Merged profiles.";
}

void profile_merging_transform::
populate_base_layer(const entities::feature_model& fm,
    std::unordered_map<std::string, entities::profile>& pm) {

    const auto fg(make_feature_group(fm));
    for (auto& pair : pm) {
        auto& profile(pair.second);

        /*
         * FIXME: big hack. Create a temporary configuration just so
         * we can read the base profile name from the profile.
         */
        entities::configuration cfg;
        cfg.configuration_points(profile.configuration_points());
        const auto bl(obtain_profile_name(fg, cfg));
        if (!bl.empty()) {
            BOOST_LOG_SEV(lg, trace) << "Read base layer name: " << bl;
            profile.base_layer_profile(bl);
        }
    }
}

entities::profile_repository profile_merging_transform::create_repository(
    const std::unordered_map<std::string, entities::profile>& pm) {
    /*
     * First we insert the profile against its name. This is just a
     * copy of the map as it already exists.
     */
    entities::profile_repository r;
    r.by_name(pm);

    /*
     * Then we insert it against the stereotype. It must be unique
     * globally.
     */
    for (const auto& first_pair : pm) {
        const auto& prf(first_pair.second);
        const auto s(prf.stereotype());

        /*
         * If the user did not bother providing us with a stereotype,
         * then there is nothing to do.
         */
        if (s.empty())
            continue;

        const auto second_pair(std::make_pair(s, prf));
        const auto inserted(r.by_stereotype().insert(second_pair).second);
        if (inserted)
            continue;

        BOOST_LOG_SEV(lg, error) << duplicate_stereotype << s
                                 << " Profile: " << first_pair.first;
        BOOST_THROW_EXCEPTION(transformation_error(duplicate_stereotype + s));
    }
    return r;
}

entities::profile_repository
profile_merging_transform::apply(const context& ctx,
    const entities::feature_model& fm,
    const std::list<entities::profile>& profiles) {
    tracing::scoped_transform_tracer stp(lg, "profile merging transform",
        transform_id, transform_id, *ctx.tracer(), profiles);

    /*
     * We create a map by profile name of those profiles and ensure
     * they look vaguely valid.
     */
    auto pm(create_profile_map(profiles));

    /*
     * Ensure the map itself is vaguely valid.
     */
    validate(pm);

    /*
     * Merge the profiles according to their inheritance tree.
     */
    merge(pm);

    /*
     * Populate the base layer field.
     */
    populate_base_layer(fm, pm);

    /*
     * Use the merged profile map to create the repository.
     */
    const auto r(create_repository(pm));

    stp.end_transform(r);
    return r;
}

}
