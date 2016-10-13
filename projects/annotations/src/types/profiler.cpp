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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/annotations/io/profile_io.hpp"
#include "dogen/annotations/io/annotation_io.hpp"
#include "dogen/annotations/types/profile_hydrator.hpp"
#include "dogen/annotations/types/profiling_error.hpp"
#include "dogen/annotations/types/template_instantiator.hpp"
#include "dogen/annotations/types/merger.hpp"
#include "dogen/annotations/types/profiler.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("annotations.profiler"));

const std::string profile_dir("profiles_v2");

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

namespace dogen {
namespace annotations {

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
        BOOST_LOG_SEV(lg, debug) << "Hydrating file: " << f.generic_string();
        r.push_back(h.hydrate(f));
    }

    BOOST_LOG_SEV(lg, debug) << "Hydrated profiles. Found: " << r.size();
    BOOST_LOG_SEV(lg, debug) << "Profiles: " << r;
    return r;
}

std::unordered_map<std::string, profiler::prof_ann> profiler::
create_prof_ann_map(const std::list<profile>& profiles) const {
    std::unordered_map<std::string, profiler::prof_ann> r;
    for (const auto& prf : profiles) {
        const auto prfn(prf.name());
        profiler::prof_ann pa;
        pa.prof = prf;
        pa.merged = false;

        const auto pair(std::make_pair(prfn, pa));
        const auto inserted(r.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, warn) << duplicate_profile_name << prfn;
            BOOST_THROW_EXCEPTION(
                profiling_error(duplicate_profile_name + prfn));
        }
    }

    return r;
}

void profiler::
validate(const std::unordered_map<std::string, prof_ann>& pas) const {
    BOOST_LOG_SEV(lg, debug) << "Validating profiles.";
    /*
     * We expect at least one profile group. This is a simple sanity
     * check to avoid dodgy installations, etc.
     */
    if (pas.empty()) {
        BOOST_LOG_SEV(lg, error) << no_profiles;
        BOOST_THROW_EXCEPTION(profiling_error(no_profiles));
    }

    for (const auto& pair : pas) {
        const auto& prfn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Validating profile: " << prfn;

        /*
         * All parents must exist in the container.
         */
        const auto& pa(pair.second);
        for (const auto parent : pa.prof.parents()) {
            const auto i(pas.find(parent));
            if (i == pas.end()) {
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
        for (const auto label : pa.prof.labels()) {
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

void profiler::instantiate_entry_templates(
    const ownership_hierarchy_repository& ohrp,
    const type_repository& trp,
    std::unordered_map<std::string, prof_ann>& pas) const {
    BOOST_LOG_SEV(lg, debug) << "Instantiating value templates.";

    template_instantiator ti(ohrp);
    for (auto& pair : pas) {
        auto& pa(pair.second);
        for (const auto& tpl : pa.prof.templates()) {
            const auto entries(ti.instantiate(trp, tpl));
            for (const auto& entry : entries)
                pa.ann.entries().insert(entry);

            BOOST_LOG_SEV(lg, debug) << "Instantiated template: "
                                     << pair.first
                                     << " Result: " << pa.ann;
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Instanted value templates.";
}

const profiler::prof_ann& profiler::
walk_up_parent_tree_and_merge(const std::string& current,
    std::unordered_map<std::string, prof_ann>& pas) const {

    BOOST_LOG_SEV(lg, debug) << "Merging profile: " << current;

    /*
     * Locate the original state of the current. It must exist due to
     * validation, but just in case we check.
     */
    const auto i(pas.find(current));
    if (i == pas.end()) {
        BOOST_LOG_SEV(lg, error) << profile_not_found << current;
        BOOST_THROW_EXCEPTION(profiling_error(profile_not_found + current));
    }

    /*
     *  If we're already merged then there is nothing to do.
     */
    if (i->second.merged) {
        BOOST_LOG_SEV(lg, debug) << "Already merged.";
        return i->second;
    }

    /*
     * If we have no parents then we're done.
     */
    if (i->second.prof.parents().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No parents so nothing to merge.";
        i->second.merged = true;
        return i->second;
    }

    /*
     * Merge current with each of its parents. If they haven't been
     * merged yet, recursion will take care of it.
     */
    for (const auto parent_name : i->second.prof.parents()) {
        BOOST_LOG_SEV(lg, debug) << "Parent: " << parent_name;
        const auto parent(walk_up_parent_tree_and_merge(parent_name, pas));
        merger mg;
        i->second.ann = mg.merge(i->second.ann, parent.ann);
        i->second.merged = true;
    }

    BOOST_LOG_SEV(lg, debug) << "Done merging profile.";
    return i->second;
}

void profiler::merge(std::unordered_map<std::string, prof_ann>& pas) const {
    BOOST_LOG_SEV(lg, debug) << "Merging profiles. Total: " << pas.size();

    for (const auto& pair : pas) {
        const auto current(pair.first);
        walk_up_parent_tree_and_merge(current, pas);
    }
    BOOST_LOG_SEV(lg, debug) << "Merged profiles.";
}

std::unordered_map<std::string, annotation>
profiler::create_annotation_map(
    const std::unordered_map<std::string, prof_ann>& pas) const {

    std::unordered_map<std::string, annotation> r;
    for (const auto& pair : pas)
        r[pair.first] = pair.second.ann;

    return r;
}

std::unordered_map<std::string, annotation>
profiler::generate(const std::vector<boost::filesystem::path>& data_dirs,
    const ownership_hierarchy_repository& ohrp,
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
    auto pas(create_prof_ann_map(profiles));
    validate(pas);

    /*
     * We then instantiate all of the entry templates contained within
     * each profile and slap the results in the profile's annotation
     * result.
     */
    instantiate_entry_templates(ohrp, trp, pas);

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

} }
