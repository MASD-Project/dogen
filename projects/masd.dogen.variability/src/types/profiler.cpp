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
#include <boost/algorithm/string/predicate.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.utility/types/io/vector_io.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.variability/io/profiler_configuration_io.hpp"
#include "masd.dogen.variability/io/profile_io.hpp"
#include "masd.dogen.variability/io/annotation_io.hpp"
#include "masd.dogen.variability/types/profile_hydrator.hpp"
#include "masd.dogen.variability/types/profiling_error.hpp"
#include "masd.dogen.variability/types/instantiation_error.hpp"
#include "masd.dogen.variability/types/template_instantiator.hpp"
#include "masd.dogen.variability/types/merger.hpp"
#include "masd.dogen.variability/types/profiler.hpp"

using namespace masd::dogen::utility::log;

namespace {

auto lg(logger_factory("annotations.profiler"));

const std::string profile_dir("annotations");
const std::string profile_prefix("masd.annotations.profiles.");

const std::string duplicate_profile_name("Duplicate profile name: ");
const std::string invalid_facet_name("Invalid facet name: ");
const std::string invalid_formatter_name("Invalid formatter name: ");
const std::string no_profiles("Expected at least one profile.");
const std::string profile_not_found("Profile not found: ");
const std::string parent_not_found(
    "Parent not found in profile container: ");
const std::string duplicate_label("Label applied more than once to profile: ");
const std::string empty_label("Profile has an empty label: ");

}

namespace masd::dogen::variability {

profiler::profiler(const bool compatibility_mode)
    : compatibility_mode_(compatibility_mode) {}

std::vector<boost::filesystem::path> profiler::to_profile_directories(
    const std::vector<boost::filesystem::path>& data_dirs) const {
    std::vector<boost::filesystem::path> r;
    r.reserve(data_dirs.size());
    for (const auto& d : data_dirs)
        r.push_back(d / profile_dir);

    BOOST_LOG_SEV(lg, debug) << "Directory list: " << r;
    return r;
}

std::list<profile> profiler::hydrate_profiles(
    const std::vector<boost::filesystem::path>& profile_dirs) const {
    BOOST_LOG_SEV(lg, debug) << "Hydrating profile groups.";
    std::list<profile> r;
    profile_hydrator h;
    const auto files(dogen::utility::filesystem::find_files(profile_dirs));
    for (const auto& f : files) {
        const auto fn(f.filename().generic_string());
        if (!boost::starts_with(fn, profile_prefix)) {
            BOOST_LOG_SEV(lg, debug) << "Ignoring file: " << f.filename();
            continue;
        }

        BOOST_LOG_SEV(lg, debug) << "Hydrating file: " << f.generic_string();
        r.push_back(h.hydrate(f));
    }

    BOOST_LOG_SEV(lg, debug) << "Hydrated profiles. Found: " << r.size();
    BOOST_LOG_SEV(lg, debug) << "Profiles: " << r;
    return r;
}

profiler::profile_map_type profiler::
create_profile_map(const std::list<profile>& profiles) const {
    profiler::profile_map_type r;
    for (const auto& prf : profiles) {
        const auto prfn(prf.name());
        profiler_configuration pc;
        pc.profile(prf);
        pc.merged(false);

        const auto pair(std::make_pair(prfn, pc));
        const auto inserted(r.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, warn) << duplicate_profile_name << prfn;
            BOOST_THROW_EXCEPTION(
                profiling_error(duplicate_profile_name + prfn));
        }
    }

    return r;
}

void profiler::validate(const profile_map_type& pm) const {
    BOOST_LOG_SEV(lg, debug) << "Validating profiles.";
    /*
     * We expect at least one profile group. This is a simple sanity
     * check to avoid dodgy installations, etc.
     */
    if (pm.empty()) {
        BOOST_LOG_SEV(lg, error) << no_profiles;
        BOOST_THROW_EXCEPTION(profiling_error(no_profiles));
    }

    for (const auto& pair : pm) {
        const auto& prfn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Validating profile: " << prfn;

        /*
         * All parents must exist in the container.
         */
        const auto& pc(pair.second);
        for (const auto parent : pc.profile().parents()) {


            const auto i(pm.find(parent));
            if (i == pm.end()) {
                BOOST_LOG_SEV(lg, error) << parent_not_found << parent;
                BOOST_THROW_EXCEPTION(
                    profiling_error(parent_not_found + parent));
            }

            /*
             * Note that value templates are validated by the
             * instantiator, so we neeed not bother here.
             */
        }

        /*
         * We don't expect users to define the same label multiple
         * times on a profile. Nit-picking somewhat but this may be
         * useful in picking up configuration errors.
         */
        std::unordered_set<std::string> done;
        for (const auto label : pc.profile().labels()) {
            if (label.empty()) {
                BOOST_LOG_SEV(lg, error) << empty_label << prfn;
                BOOST_THROW_EXCEPTION(profiling_error(empty_label + prfn));
            }

            if (done.find(label) != done.end()) {
                BOOST_LOG_SEV(lg, error) << duplicate_label << label;
                BOOST_THROW_EXCEPTION(profiling_error(duplicate_label + label));
            }
            done.insert(label);
        }

        BOOST_LOG_SEV(lg, debug) << "Validated profile.";
    }
    BOOST_LOG_SEV(lg, debug) << "Validated all profiles.";
}

void profiler::
setup_annotations(const archetypes::archetype_location_repository& alrp,
    const type_repository& trp, profile_map_type& pm) const {
    BOOST_LOG_SEV(lg, debug) << "Instantiating value templates.";

    template_instantiator ti(alrp);
    for (auto& pair : pm) {
        const auto prfn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Instantiating templates for profile: "
                                 << prfn;

        auto& pc(pair.second);
        pc.annotation().scope(scope_types::not_applicable);
        for (const auto& tpl : pc.profile().templates()) {
            try {
                const auto tagged_values(ti.instantiate(trp, tpl));
                for (const auto& tv : tagged_values)
                    pc.annotation().tagged_values().insert(tv);

                BOOST_LOG_SEV(lg, debug) << "Instantiated template: "
                                         << tpl.name().qualified()
                                         << " Result: " << pc.annotation();
            } catch (const instantiation_error& e) {
                BOOST_LOG_SEV(lg, error) << "compatibility_mode_: "
                                         << compatibility_mode_;
                if (!compatibility_mode_) {
                    BOOST_LOG_SEV(lg, error) << "Error instantiating profile: "
                                             << prfn << ". Message: "
                                             << e.what() << ".";

                    /*
                     * Note: we are skipping profiles that fail with
                     * instantiation errors. This is because its not
                     * always the case that all profiles are instantiable;
                     * for example, a profile for knitter may not work for
                     * stitch, because its missing all of the
                     * formatters. This is not a very elegant solution,
                     * but it will do until we think of something
                     * better. Note that this only happens for stitch
                     * tests at present (because there we do not want a
                     * dependency on the rest of the code base). FIXME:
                     * this is a hack that needs to be removed.
                     */
                    // throw e;
                }

                BOOST_LOG_SEV(lg, warn) << "Error instantiating profile: "
                                        << prfn << ". Message: " << e.what()
                                        << ". Skipping profile.";
            }
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Instanted value templates.";
}

const profiler_configuration& profiler:: walk_up_parent_tree_and_merge(
    const std::string& current, profile_map_type& pm) const {

    BOOST_LOG_SEV(lg, debug) << "Merging profile: " << current;

    /*
     * Locate the original state of the current. It must exist due to
     * validation, but just in case we check.
     */
    const auto i(pm.find(current));
    if (i == pm.end()) {
        BOOST_LOG_SEV(lg, error) << profile_not_found << current;
        BOOST_THROW_EXCEPTION(profiling_error(profile_not_found + current));
    }

    auto& pc(i->second);
    /*
     *  If we're already merged then there is nothing to do.
     */
    if (pc.merged()) {
        BOOST_LOG_SEV(lg, debug) << "Already merged.";
        return pc;
    }

    /*
     * If we have no parents then we're done.
     */
    if (pc.profile().parents().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No parents so nothing to merge.";
        pc.merged(true);
        return pc;
    }

    /*
     * Merge current with each of its parents. If they haven't been
     * merged yet, recursion will take care of it.
     */
    for (const auto parent_name : pc.profile().parents()) {
        BOOST_LOG_SEV(lg, debug) << "Parent: " << parent_name;
        const auto parent(walk_up_parent_tree_and_merge(parent_name, pm));
        merger mg;
        pc.annotation(mg.merge(pc.annotation(), parent.annotation()));
        pc.merged(true);
    }

    BOOST_LOG_SEV(lg, debug) << "Done merging profile.";
    return i->second;
}

void profiler::merge(profile_map_type& pm) const {
    BOOST_LOG_SEV(lg, debug) << "Merging profiles. Total: " << pm.size();

    for (const auto& pair : pm) {
        const auto current(pair.first);
        walk_up_parent_tree_and_merge(current, pm);
    }
    BOOST_LOG_SEV(lg, debug) << "Merged profiles.";
}

std::unordered_map<std::string, annotation>
profiler::create_annotation_map(const profile_map_type& pm) const {

    std::unordered_map<std::string, annotation> r;
    for (const auto& pair : pm) {
        const auto prfn(pair.first);
        const auto& pc(pair.second);

        /*
         * First we insert the annotation against the profile name.
         */
        const auto annotation_pair(std::make_pair(prfn, pc.annotation()));
        const auto inserted(r.insert(annotation_pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, warn) << duplicate_profile_name << prfn;
            BOOST_THROW_EXCEPTION(
                profiling_error(duplicate_profile_name + prfn));
        }

        /*
         * Then we insert it against all the labels. Labels must be
         * unique across all profiles.
         */
        for (const auto l : pc.profile().labels()) {
            const auto annotation_pair(std::make_pair(l, pc.annotation()));
            const auto inserted(r.insert(annotation_pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, warn) << duplicate_profile_name << prfn;
                BOOST_THROW_EXCEPTION(
                    profiling_error(duplicate_profile_name + prfn));
            }
        }
    }

    return r;
}

std::unordered_map<std::string, annotation>
profiler::generate(const std::vector<boost::filesystem::path>& data_dirs,
    const archetypes::archetype_location_repository& alrp,
    const type_repository& trp) const {

    BOOST_LOG_SEV(lg, debug) << "Generating profiles.";
    /*
     * First we obtain the set of directories that contain profile
     * data, by looking into the supplied data directories at a
     * well-known location.
     */
    const auto prf_dirs(to_profile_directories(data_dirs));

    /*
     * We then read out all profiles contained within that set of
     * directories.
     */
    const auto profiles(hydrate_profiles(prf_dirs));

    /*
     * We create a map by profile name of those profiles and ensure
     * they look vaguely valid.
     */
    auto pas(create_profile_map(profiles));
    validate(pas);

    /*
     * We then setup all annotations. This includes instantiating all
     * of the entry templates contained within each profile and
     * copying the results in the profile's annotation result.
     */
    setup_annotations(alrp, trp, pas);

    /*
     * We now merge the annotation objects according to the profile
     * inheritance tree and format the results for the expected
     * output.
     */
    merge(pas);
    const auto r(create_annotation_map(pas));
    BOOST_LOG_SEV(lg, debug) << "Generated profiles. Result: " << r;
    return r;
}

}
