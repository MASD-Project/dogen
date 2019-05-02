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
#include "masd.dogen.variability/io/meta_model/profile_io.hpp"
#include "masd.dogen.variability/io/meta_model/profile_repository_io.hpp"
#include "masd.dogen.variability/types/helpers/configuration_point_merger.hpp"
#include "masd.dogen.variability/types/transforms/transformation_error.hpp"
#include "masd.dogen.variability/types/transforms/profile_merging_transform.hpp"

namespace {

const std::string transform_id(
    "variability.transforms.profile_merging_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_profile_name("Duplicate profile name: ");
const std::string no_profiles("Expected at least one profile.");
const std::string profile_not_found("Profile not found: ");
const std::string parent_not_found(
    "Parent not found in profile container: ");
const std::string duplicate_label("Label applied more than once to profile: ");
const std::string empty_label("Profile has an empty label: ");

}

namespace masd::dogen::variability::transforms {

const meta_model::profile& profile_merging_transform::
walk_up_parent_tree_and_merge(const std::string& current,
    std::unordered_map<std::string, meta_model::profile>& pm) {
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

std::unordered_map<std::string, meta_model::profile> profile_merging_transform::
create_profile_map(const std::list<meta_model::profile>& profiles) {
    std::unordered_map<std::string, meta_model::profile> r;
    for (const auto& prf : profiles) {
        const auto prfn(prf.name().qualified());
        const auto pair(std::make_pair(prfn, prf));
        const auto inserted(r.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, warn) << duplicate_profile_name << prfn;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_profile_name + prfn));
        }
    }
    return r;
}

void profile_merging_transform::
validate(const std::unordered_map<std::string, meta_model::profile>& pm) {
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
             * Note that configuration point templates are validated
             * by the instantiator, so we neeed not bother here.
             */
        }

        /*
         * We don't expect users to define the same label multiple
         * times on a profile. Nit-picking somewhat but this may be
         * useful in picking up configuration errors.
         */
        std::unordered_set<std::string> done;
        for (const auto label : prf.labels()) {
            if (label.empty()) {
                BOOST_LOG_SEV(lg, error) << empty_label << prfn;
                BOOST_THROW_EXCEPTION(transformation_error(empty_label + prfn));
            }

            if (done.find(label) != done.end()) {
                BOOST_LOG_SEV(lg, error) << duplicate_label << label;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_label + label));
            }
            done.insert(label);
        }

        BOOST_LOG_SEV(lg, debug) << "Validated profile.";
    }
    BOOST_LOG_SEV(lg, debug) << "Validated all profiles.";
}

void profile_merging_transform::
merge(std::unordered_map<std::string, meta_model::profile>& pm) {
    BOOST_LOG_SEV(lg, debug) << "Merging profiles. Total: " << pm.size();
    for (const auto& pair : pm) {
        const auto current(pair.first);
        walk_up_parent_tree_and_merge(current, pm);
    }
    BOOST_LOG_SEV(lg, debug) << "Merged profiles.";
}

meta_model::profile_repository profile_merging_transform::create_repository(
    const std::unordered_map<std::string, meta_model::profile>& pm) {

    /*
     * First we insert the annotation against the profile name. This
     * is just a copy of the map as it already exists.
     */
    meta_model::profile_repository r;
    r.by_name(pm);

    /*
     * Then we insert it against all the labels. Labels must be
     * unique across all profiles.
     */
    for (const auto& first_pair : pm) {
        const auto& prf(first_pair.second);
        for (const auto l : prf.labels()) {
            const auto label_pair(std::make_pair(l, prf));
            const auto inserted(r.by_labels().insert(label_pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_label << l
                                         << " Profile: " << first_pair.first;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_label + l));
            }
        }
    }
    return r;
}

meta_model::profile_repository profile_merging_transform::
apply(const context& ctx, const std::list<meta_model::profile>& profiles) {
    tracing::scoped_transform_tracer stp(lg, "profile merging transform",
        transform_id, transform_id, *ctx.tracer(), profiles);

    /*
     * We create a map by profile name of those profiles and ensure
     * they look vaguely valid.
     */
    auto pm(create_profile_map(profiles));

    /*
     * Ensure the map is vaguely valid.
     */
    validate(pm);

    /*
     * Merge the profiles according to their inheritance tree.
     */
    merge(pm);

    /*
     * Use the merged profile map to create the repository.
     */
    const auto r(create_repository(pm));

    stp.end_transform(r);
    return r;
}

}
