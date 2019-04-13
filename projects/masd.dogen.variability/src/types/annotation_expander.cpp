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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.variability/io/type_io.hpp"
#include "masd.dogen.variability/io/annotation_io.hpp"
#include "masd.dogen.variability/io/scope_types_io.hpp"
#include "masd.dogen.variability/types/merger.hpp"
#include "masd.dogen.variability/types/profiler.hpp"
#include "masd.dogen.variability/types/value_factory.hpp"
#include "masd.dogen.variability/types/building_error.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.variability/types/annotation_expander.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("annotations.annotation_expander"));

const std::string empty;
const std::string missing_profile(
    "Annotation uses a profile that could not be found: ");
const std::string too_many_binds(
    "Too many candidate labels bind to a profile: ");
const std::string type_name("masd.annotations.profile");
const std::string default_root("default.root_module");

}

namespace masd::dogen::variability {

annotation_expander::annotation_expander(
    const std::vector<boost::filesystem::path>& data_dirs,
    const archetypes::location_repository& alrp,
    const type_repository& trp, const bool compatibility_mode)
    : data_dirs_(data_dirs), archetype_location_repository_(alrp),
      type_repository_(trp),
      profiles_(create_annotation_profiles(compatibility_mode)),
      type_group_(make_type_group()) {}

inline std::ostream&
operator<<(std::ostream& s, const annotation_expander::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"masd::dogen::variability::"
      << "annotation_expander::type_group\"" << ", "
      << "\"profile\": " << v.profile
      << " }";

    return s;
}

annotation_expander::type_group
annotation_expander::make_type_group() const {
    BOOST_LOG_SEV(lg, debug) << "Creating annotation types.";

    type_group r;
    const type_repository_selector s(type_repository_);
    r.profile = s.select_type_by_name(type_name);

    BOOST_LOG_SEV(lg, debug) << "Created annotation types. Result: " << r;
    return r;
}

std::string annotation_expander::
obtain_profile_name(const type_group& tg, const annotation& a) const {
    BOOST_LOG_SEV(lg, debug) << "Reading profile name.";
    const entry_selector s(a);
    std::string r;
    if (s.has_entry(tg.profile))
        r = s.get_text_content(tg.profile);

    BOOST_LOG_SEV(lg, debug) << "Profile name: '" << r << "'";
    return r;
}

boost::optional<type>
annotation_expander::try_obtain_type(const std::string& n) const {
    /*
     * First try a full match; if it exists, return the type.
     */
    const auto i(type_repository_.types_by_name().find(n));
    if (i != type_repository_.types_by_name().end())
        return i->second;

    /*
     * Now try the partial matches. Note that we can be sure there
     * will only be one match due to the logic of partial matching, as
     * two types cannot have the same name.
     */
    for (const auto& pair : type_repository_.partially_matchable_types()) {
        const auto& qn(pair.first);
        const auto& t(pair.second);
        if (boost::starts_with(n, qn))
            return t;
    }

    return boost::optional<type>();
}

std::string annotation_expander::
get_default_profile_name_for_scope(const scope_types scope) const {
    if (scope == scope_types::root_module)
        return default_root;

    return empty;
}

std::list<std::string> annotation_expander::
get_bound_labels(const std::unordered_map<std::string, annotation>& profiles,
    const std::list<std::string>& candidate_labels) const {

    std::list<std::string> r;
    for (const auto& cl : candidate_labels) {
        if (profiles.find(cl) != profiles.end())
            r.push_back(cl);
    }
    return r;
}

std::unordered_map<std::string, annotation> annotation_expander::
create_annotation_profiles(const bool compatibility_mode) const {
    profiler prf(compatibility_mode);
    const auto& alrp(archetype_location_repository_);
    const auto& trp(type_repository_);
    return prf.generate(data_dirs_, alrp, trp);
}

annotation annotation_expander::expand(
    const std::list<std::string>& candidate_labels, const annotation& a) const {

    BOOST_LOG_SEV(lg, debug) << "Started expanding profiles for annotation.";
    BOOST_LOG_SEV(lg, debug) << "Original: " << a;

    /*
     * If a profile name was specified via the meta-data, it must
     * exist on our profile collection. Locate it, merge it with the
     * original annotation and return that.
     */
    const auto profn(obtain_profile_name(type_group_, a));
    if (!profn.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Configured profile: " << profn;
        const auto i(profiles_.find(profn));
        if (i == profiles_.end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile << profn;
            BOOST_THROW_EXCEPTION(building_error(missing_profile + profn));
        }

        merger mg;
        const auto annotation_profile(i->second);
        const annotation r(mg.merge(a, annotation_profile));
        BOOST_LOG_SEV(lg, debug) << "Merged profile: " << r;
        return r;
    } else
        BOOST_LOG_SEV(lg, debug) << "Profile not set in meta-data.";

    /*
     * Lets try each of the candidate labels instead and see if any of
     * them bind to a profile.
     */
    const auto bound_labels(get_bound_labels(profiles_, candidate_labels));
    if (bound_labels.size() > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_binds << bound_labels;
        BOOST_THROW_EXCEPTION(building_error(too_many_binds));
    }

    for (const auto& bl : bound_labels) {
        BOOST_LOG_SEV(lg, debug) << "Bound label: " << bl;
        const auto i(profiles_.find(bl));
        if (i == profiles_.end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile << bl;
            BOOST_THROW_EXCEPTION(building_error(missing_profile + bl));
        }

        merger mg;
        const auto annotation_profile(i->second);
        const annotation r(mg.merge(a, annotation_profile));
        BOOST_LOG_SEV(lg, debug) << "Merged profile: " << r;
        return r;
    }

    /*
     * If no profile name was found by now, we need to try looking for
     * the well-known default profiles, based on the scope of the
     * annotation. Not all scope types have a mapping, and the default
     * profiles do not necessarily exist.
     */
    const auto def_profn(get_default_profile_name_for_scope(a.scope()));
    if (!def_profn.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Looking for default profile: "
                                 << def_profn;

        const auto i(profiles_.find(def_profn));
        if (i != profiles_.end()) {
            merger mg;
            const auto annotation_profile(i->second);
            const annotation r(mg.merge(a, annotation_profile));
            BOOST_LOG_SEV(lg, debug) << "Merged profile: " << r;
            return r;
        }
    } else
        BOOST_LOG_SEV(lg, debug) << "Scope does not have a default profile.";

    /*
     * If we could find nothing suitable, just return the original.
     */
    BOOST_LOG_SEV(lg, debug) << "No profiles found, using original.";
    return a;
}

annotation annotation_expander::expand(const annotation& a) const {
    std::list<std::string> candidate_labels;
    return expand(candidate_labels, a);
}

}
