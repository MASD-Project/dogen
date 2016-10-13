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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/annotations/io/profile_io.hpp"
#include "dogen/annotations/types/profile_hydrator.hpp"
#include "dogen/annotations/types/profiling_error.hpp"
#include "dogen/annotations/types/profiler.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("annotations.profiler"));

const std::string profile_dir("profiles_v2");

const std::string duplicate_profile_name("Duplicate profile name: ");
const std::string invalid_facet_name("Invalid facet name: ");
const std::string invalid_formatter_name("Invalid formatter name: ");
const std::string no_profiles("Expected at least one profile.");
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

void profiler::instantiate_value_templates(
    std::unordered_map<std::string, prof_ann>& /*pa*/) const {

}

void profiler::walk_up_parent_tree_and_merge(const std::string& /*current*/,
    std::unordered_map<std::string, prof_ann>& /*pa*/) const {
}

void profiler::merge(std::unordered_map<std::string, prof_ann>& /*pa*/) const {

}

std::unordered_map<std::string, profiler::prof_ann>
profiler::create_annotation_map(
    const std::unordered_map<std::string, prof_ann>& /*pa*/) const {
    std::unordered_map<std::string, profiler::prof_ann> r;
    return r;
}

std::unordered_map<std::string, annotation>
profiler::generate(const std::vector<boost::filesystem::path>& data_dirs,
    const ownership_hierarchy_repository& /*ohrp*/) const {

    const auto prf_dirs(to_profile_directories(data_dirs));
    const auto profiles(hydrate_profiles(prf_dirs));
    const auto pas(create_prof_ann_map(profiles));
    validate(pas);
    std::unordered_map<std::string, annotation> r;
    return r;
}

} }
