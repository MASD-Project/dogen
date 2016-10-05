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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/quilt.cpp/types/formattables/merge_error.hpp"
#include "dogen/quilt.cpp/io/formattables/profile_group_io.hpp"
#include "dogen/quilt.cpp/io/formattables/profile_types_io.hpp"
#include "dogen/quilt.cpp/io/formattables/facet_profile_io.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group_merger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("quilt.cpp.formattables.profile_group_merger"));

const std::string profile_type_conflict(
    "Profile type defined in multiple places.");
const std::string licence_name_conflict(
    "Licence name defined in multiple places.");
const std::string copyright_notices_conflict(
    "Copyright notices defined in multiple places.");
const std::string modeline_group_name_conflict(
    "Modeline group name defined in multiple places.");
const std::string default_facet_profile_conflict(
    "Default facet profile defined in multiple places.");
const std::string default_formatter_profile_conflict(
    "Default formatter profile defined in multiple places.");
const std::string not_in_original(
    "Profile group not in original profile group container: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

decoration_profile profile_group_merger::merge(const decoration_profile& parent,
    const decoration_profile& child) const {

    decoration_profile r(child);

    /*
     * Parent and child cannot both have licence name set.
     */
    if (!r.licence_name().empty() &&
        r.licence_name() != parent.licence_name()) {
        BOOST_LOG_SEV(lg, error) << licence_name_conflict;
        BOOST_THROW_EXCEPTION(merge_error(licence_name_conflict));
    } else if (!parent.licence_name().empty())
        r.licence_name(parent.licence_name());

    /*
     * Parent and child cannot both have copyright notices set.
     */
    if (!r.copyright_notices().empty() &&
        r.copyright_notices() != parent.copyright_notices()) {
        BOOST_LOG_SEV(lg, error) << copyright_notices_conflict;
        BOOST_THROW_EXCEPTION(merge_error(copyright_notices_conflict));
    } else if (!parent.copyright_notices().empty())
        r.copyright_notices(parent.copyright_notices());

    /*
     * Parent and child cannot both have modeline group name set.
     */
    if (!r.modeline_group_name().empty() &&
        r.modeline_group_name() != parent.modeline_group_name()) {
        BOOST_LOG_SEV(lg, error) << modeline_group_name_conflict;
        BOOST_THROW_EXCEPTION(merge_error(modeline_group_name_conflict));
    } else if (!parent.modeline_group_name().empty())
        r.modeline_group_name(parent.modeline_group_name());

    return r;
}

profile_group profile_group_merger::
merge(const profile_group& parent, const profile_group& child) const {
    profile_group r(child);
    BOOST_LOG_SEV(lg, debug) << "Merging: " << child.name()
                             << " (child) with: " << parent.name();

    /*
     * We only expect a single profile type to be set across a tree.
     */
    const auto pt(profile_types::invalid);
    if (r.profile_type() != pt && r.profile_type() != parent.profile_type()) {
        BOOST_LOG_SEV(lg, error) << profile_type_conflict;
        BOOST_THROW_EXCEPTION(merge_error(profile_type_conflict));
    } else if (parent.profile_type() != pt) {
        r.profile_type(parent.profile_type());
        BOOST_LOG_SEV(lg, debug) << "Setting profile type: "
                                 << parent.profile_type();
    } else
        BOOST_LOG_SEV(lg, debug) << "Not merging profile types.";

    if (parent.decoration_profile()) {
        /*
         * If the parent has a decoration profile but we don't just
         * take the parent's.
         */
        if (!r.decoration_profile())
            r.decoration_profile(parent.decoration_profile());
        else {
            /*
             * If we both have a decoration profile we need to merge
             * them.
             */
            const auto pdprf(*parent.decoration_profile());
            const auto dprf(*r.decoration_profile());
            r.decoration_profile(merge(pdprf, dprf));
        }
    }

    /*
     * If the parent has a default facet profile but we don't just
     * take the parent's.
     */
    if (!r.default_facet_profile() && parent.default_facet_profile())
        r.default_facet_profile(parent.default_facet_profile());

    /*
     * If the parent has a default formatter profile but we don't just
     * take the parent's.
     */
    if (!r.default_formatter_profile() && parent.default_formatter_profile())
        r.default_formatter_profile(parent.default_formatter_profile());

    /*
     * Insert any facets and formatter profiles that exist in the
     * parent but not the child. Note that if they exist in both, the
     * child's entry takes priortiy.
     */
    for (const auto& pair : parent.facet_profiles())
        r.facet_profiles().insert(pair);

    for (const auto& pair : parent.formatter_profiles())
        r.formatter_profiles().insert(pair);

    return r;
}

profile_group profile_group_merger::walk_up_parent_tree_and_process(
    const std::string& current,
    const std::unordered_map<std::string, profile_group>& original,
    std::unordered_map<std::string, profile_group>& done) const {

    BOOST_LOG_SEV(lg, debug) << "Merging: " << current;

    /*
     * If we're in the done container we've already been merged.
     */
    const auto i(done.find(current));
    if (i != done.end()) {
        BOOST_LOG_SEV(lg, debug) << "Already merged.";
        return i->second;
    }

    /*
     * Locate the original state of the current. It must exist due to
     * validation, but just in case we check.
     */
    const auto j(original.find(current));
    if (j == original.end()) {
        BOOST_LOG_SEV(lg, error) << not_in_original << current;
        BOOST_THROW_EXCEPTION(merge_error(not_in_original + current));
    }

    /*
     * If we have no parents then we're done.
     */
    const auto original_pg(j->second);
    if (original_pg.parents().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No parents so nothing to merge.";
        done.insert(std::make_pair(current, original_pg));
        return original_pg;
    }

    /*
     * Merge current with each of its parents. If they haven't been
     * merged yet, recursion will take care of it.
     */
    profile_group r;
    for (const auto parent_name : original_pg.parents()) {
        BOOST_LOG_SEV(lg, debug) << "Parent: " << parent_name;
        const auto parent(
            walk_up_parent_tree_and_process(parent_name, original, done));
        r = merge(parent, original_pg);
    }

    done.insert(std::make_pair(current, r));
    BOOST_LOG_SEV(lg, debug) << "Done merging profile group.";
    return r;
}

std::unordered_map<std::string, profile_group> profile_group_merger::
merge(const std::unordered_map<std::string, profile_group>& original) const {
    BOOST_LOG_SEV(lg, debug) << "Merging profile groups. Total: "
                             << original.size();

    std::unordered_map<std::string, profile_group> r;
    for (const auto& pair : original) {
        const auto pgn(pair.first);
        walk_up_parent_tree_and_process(pgn, original, r);
    }
    BOOST_LOG_SEV(lg, debug) << "Merged profile groups. Total: " << r.size();
    BOOST_LOG_SEV(lg, debug) << "Profile groups: " << r;

    return r;
}

} } } }
