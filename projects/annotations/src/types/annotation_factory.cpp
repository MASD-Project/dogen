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
#include <boost/algorithm/string/erase.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/io/annotation_io.hpp"
#include "dogen/annotations/io/scope_types_io.hpp"
#include "dogen/annotations/types/merger.hpp"
#include "dogen/annotations/types/profiler.hpp"
#include "dogen/annotations/types/value_factory.hpp"
#include "dogen/annotations/types/building_error.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/types/annotation_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.annotation_factory"));

const std::string empty;
const std::string expected_scope(" Expected scope: ");
const std::string actual_scope(" Actual scope: ");
const std::string duplicate_type("Type already inserted: ");
const std::string duplicate_key("Key already inserted: ");
const std::string too_many_values("More than one value supplied against key: ");
const std::string type_not_found("Type not found: ");
const std::string field_used_in_invalid_scope("Field used in invalid scope: ");
const std::string missing_profile(
    "Annotation uses a profile that could not be found: ");
const std::string too_many_binds(
    "Too many candidate labels bind to a profile: ");

const std::string kernel_name("annotations");
const std::string type_name("profile");

const std::string default_root("default.root_module");

}

namespace dogen {
namespace annotations {

annotation_factory::annotation_factory(
    const std::vector<boost::filesystem::path>& data_dirs,
    const archetype_location_repository& alrp,
    const type_repository& trp, const bool compatibility_mode)
    : data_dirs_(data_dirs), archetype_location_repository_(alrp),
      type_repository_(trp), profiles_(create_annotation_profiles()),
      type_group_(make_type_group()), compatibility_mode_(compatibility_mode) {}

inline std::ostream&
operator<<(std::ostream& s, const annotation_factory::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::annotations::"
      << "annotation_factory::type_group\"" << ", "
      << "\"profile\": " << v.profile
      << " }";

    return s;
}

annotation_factory::type_group
annotation_factory::make_type_group() const {
    BOOST_LOG_SEV(lg, debug) << "Creating annotation types.";

    type_group r;
    const type_repository_selector s(type_repository_);
    r.profile = s.select_type_by_name(kernel_name, type_name);

    BOOST_LOG_SEV(lg, debug) << "Created annotation types. Result: " << r;
    return r;
}

std::string annotation_factory::
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
annotation_factory::try_obtain_type(const std::string& n) const {
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

void annotation_factory::validate_scope(const type& t,
    const scope_types current_scope) const {
    if (t.scope() != scope_types::any &&
        t.scope() != scope_types::not_applicable &&
        t.scope() != current_scope) {

        std::stringstream s;
        s << field_used_in_invalid_scope << t.name().qualified()
          << expected_scope << t.scope()
          << actual_scope << current_scope;
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(building_error(s.str()));
    }
}

std::string annotation_factory::
get_default_profile_name_for_scope(const scope_types scope) const {
    if (scope == scope_types::root_module)
        return default_root;

    return empty;
}

annotation annotation_factory::create_annotation(const scope_types scope,
    const std::unordered_map<std::string, std::list<std::string>>&
    aggregated_entries) const {

    annotation r;
    r.scope(scope);

    value_factory f;
    std::unordered_map<std::string, boost::shared_ptr<value>> entries;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
        all_kvps;
    for (auto kvp : aggregated_entries) {
        const auto& k(kvp.first);
        const auto ot(try_obtain_type(k));

        /*
         * If we're in compatibility mode, skip any types for which we
         * do not have definitions. This is for forward compatibility
         * purposes (i.e. diagrams using types that we do not yet know
         * about).
         */
        if (!ot && compatibility_mode_)
            continue;
        else if (!ot) {
            /*
             * If we are not in compatibility mode and nothing
             * matches, we need to throw.
             */
            BOOST_LOG_SEV(lg, error) << type_not_found << k;
            BOOST_THROW_EXCEPTION(building_error(type_not_found + k));
        }

        /*
         * Ensure the entry is valid with regards to scope.
         */
        const auto& t(*ot);
        validate_scope(t, r.scope());

        const auto& v(kvp.second);
        if (t.value_type() == value_types::key_value_pair) {
            BOOST_LOG_SEV(lg, debug) << "Adding kvp for key: " << k;
            if (v.size() != 1) {
                BOOST_LOG_SEV(lg, debug) << too_many_values << k;
                BOOST_THROW_EXCEPTION(building_error(too_many_values + k));
            }

            const auto qn(t.name().qualified());
            const auto new_key(boost::erase_first_copy(k, qn + "."));
            BOOST_LOG_SEV(lg, debug) << "Actual key: " << new_key;

            const auto pair(std::make_pair(new_key, v.front()));
            const auto inserted(all_kvps[qn].insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, debug) << duplicate_key << new_key;
                BOOST_THROW_EXCEPTION(building_error(duplicate_key + new_key));
            }
        } else
            r.entries()[k] = f.make(t, v);
    }

    for (const auto& pair : all_kvps) {
        BOOST_LOG_SEV(lg, debug) << "Processing kvp:: " << pair;

        const auto k(pair.first);
        const auto kvps(pair.second);
        r.entries()[k] = f.make_kvp(kvps);
    }

    return r;
}

std::unordered_map<std::string, std::list<std::string>>
annotation_factory::aggregate_entries(
    const std::list<std::pair<std::string, std::string>>& entries) const {
    std::unordered_map<std::string, std::list<std::string> > r;

    for (const auto& entry : entries)
        r[entry.first].push_front(entry.second);

    return r;
}

std::list<std::string> annotation_factory::
get_bound_labels(const std::unordered_map<std::string, annotation>& profiles,
    const std::list<std::string>& candidate_labels) const {

    std::list<std::string> r;
    for (const auto& cl : candidate_labels) {
        if (profiles.find(cl) != profiles.end())
            r.push_back(cl);
    }
    return r;
}

std::unordered_map<std::string, annotation> annotation_factory::
create_annotation_profiles() const {
    profiler prf;
    const auto& alrp(archetype_location_repository_);
    const auto& trp(type_repository_);
    return prf.generate(data_dirs_, alrp, trp);
}

annotation annotation_factory::
handle_profiles(const type_group& tg, const std::unordered_map<std::string,
    annotation>& profiles, const std::list<std::string>& candidate_labels,
    const annotation& original) const {

    BOOST_LOG_SEV(lg, debug) << "Started handling profiles. Original: "
                             << original;

    /*
     * If a profile name was specified via the meta-data, it must
     * exist on our profile collection. Locate it, merge it with the
     * original annotation and return that.
     */
    const auto profn(obtain_profile_name(tg, original));
    if (!profn.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Configured profile: " << profn;
        const auto i(profiles.find(profn));
        if (i == profiles.end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile << profn;
            BOOST_THROW_EXCEPTION(building_error(missing_profile + profn));
        }

        merger mg;
        const auto annotation_profile(i->second);
        const annotation r(mg.merge(original, annotation_profile));
        BOOST_LOG_SEV(lg, debug) << "Merged profile: " << r;
        return r;
    } else
        BOOST_LOG_SEV(lg, debug) << "Profile not set in meta-data.";

    /*
     * Lets try each of the candidate labels instead and see if any of
     * them bind to a profile.
     */
    const auto bound_labels(get_bound_labels(profiles, candidate_labels));
    if (bound_labels.size() > 1) {
        BOOST_LOG_SEV(lg, error) << too_many_binds << bound_labels;
        BOOST_THROW_EXCEPTION(building_error(too_many_binds));
    }

    for (const auto& bl : bound_labels) {
        BOOST_LOG_SEV(lg, debug) << "Bound label: " << bl;
        const auto i(profiles.find(bl));
        if (i == profiles.end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile << bl;
            BOOST_THROW_EXCEPTION(building_error(missing_profile + bl));
        }

        merger mg;
        const auto annotation_profile(i->second);
        const annotation r(mg.merge(original, annotation_profile));
        BOOST_LOG_SEV(lg, debug) << "Merged profile: " << r;
        return r;
    }

    /*
     * If no profile name was found by now, we need to try looking for
     * the well-known default profiles, based on the scope of the
     * annotation. Not all scope types have a mapping, and the default
     * profiles do not necessarily exist.
     */
    const auto def_profn(get_default_profile_name_for_scope(original.scope()));
    if (!def_profn.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Looking for default profile; " << def_profn;

        const auto i(profiles.find(def_profn));
        if (i != profiles.end()) {
            merger mg;
            const auto annotation_profile(i->second);
            const annotation r(mg.merge(original, annotation_profile));
            BOOST_LOG_SEV(lg, debug) << "Merged profile: " << r;
            return r;
        }
    } else
        BOOST_LOG_SEV(lg, debug) << "Scope does not have a default profile.";

    /*
     * If we could find nothing suitable, just return the original.
     */
    BOOST_LOG_SEV(lg, debug) << "No profiles found, using original.";
    return original;
}

annotation annotation_factory::make(
    const std::list<std::pair<std::string, std::string>>& entries,
    const scope_types scope) const {
    const std::list<std::string> candidate_labels;
    return make(entries, scope, candidate_labels);
}

annotation annotation_factory::make(
    const std::list<std::pair<std::string, std::string>>& entries,
    const scope_types scope,
    const std::list<std::string>& candidate_labels) const {
    auto aggregated_entries(aggregate_entries(entries));
    const auto original(create_annotation(scope, aggregated_entries));
    const auto& cl(candidate_labels);
    const auto r(handle_profiles(type_group_, profiles_, cl, original));
    return r;
}

} }
