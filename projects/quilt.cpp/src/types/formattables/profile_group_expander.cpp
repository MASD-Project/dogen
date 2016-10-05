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
#include <unordered_set>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/dynamic/io/field_definition_io.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/io/formattables/profile_types_io.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group_hydrator.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group_merger.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group_expander.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("quilt.cpp.formattables.profile_group_expander"));

const std::string invalid_facet_name("Invalid facet name: ");
const std::string invalid_formatter_name("Invalid formatter name: ");
const std::string no_profile_groups("Expected at least one profile group.");
const std::string parent_not_found(
    "Parent not found in profile group container: ");
const std::string invalid_profile_configuration(
    "Invalid profile configuration: ");
const std::string missing_profile_configuration(
    "Missing profile configuration: ");
const std::string  duplicate_bind(
    "More than one profile configuration bind to the same stereotype: ");
const std::string too_many_binds("Stereotype bound more than once: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

inline std::ostream& operator<<(std::ostream& s,
    const profile_group_expander::field_definitions& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "profile_group_expander::field_definitions\"" << ", "
      << "\"profile\": " << v.profile
      << " }";

    return s;
}

profile_group_expander::field_definitions
profile_group_expander::make_field_definitions(
    const dynamic::repository& drp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating field definitions.";

    field_definitions r;
    const dynamic::repository_selector s(drp);
    const auto& mn(formatters::traits::model_name());
    r.profile = s.select_field_by_name(mn, "profile");

    BOOST_LOG_SEV(lg, debug) << "Created field definitions. Result: " << r;
    return r;
}

std::string profile_group_expander::obtain_profile_configuration(
    const field_definitions& fd, const dynamic::object& root_object) const {
    BOOST_LOG_SEV(lg, debug) << "Reading profile configuration.";
    const dynamic::field_selector fs(root_object);
    const auto r(fs.get_text_content_or_default(fd.profile));
    BOOST_LOG_SEV(lg, debug) << "Profile configuration: " << r;
    return r;
}

profile_group_expander::profile_group_types
profile_group_expander::
hydrate(const std::forward_list<boost::filesystem::path>&
    data_directories) const {
    profile_group_hydrator h;
    return h.hydrate(data_directories);
}

void profile_group_expander::validate(const formatters::container& fc,
    const profile_group_types& pgs) const {
    BOOST_LOG_SEV(lg, debug) << "Validating profile groups.";

    /*
     * We expect at least one profile group. This is a simple sanity
     * check to avoid dodgy installations, etc.
     */
    if (pgs.empty()) {
        BOOST_LOG_SEV(lg, error) << no_profile_groups;
        BOOST_THROW_EXCEPTION(expansion_error(no_profile_groups));
    }

    /*
     * Gather all distinct facet and formater names.
     */
    std::unordered_set<std::string> facet_names;
    std::unordered_set<std::string> formatter_names;
    for (const auto ptr : fc.file_formatters()) {
        const auto& f(*ptr);
        const auto& oh(f.ownership_hierarchy());

        const auto fctn(oh.facet_name());
        facet_names.insert(fctn);

        const auto fmtn(oh.formatter_name());
        formatter_names.insert(fmtn);
    }

    for (const auto& pair : pgs) {
        const auto& pgn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Validating: " << pgn;

        /*
         * All parents must exist in the container.
         */
        const auto& pg(pair.second);
        for (const auto parent : pg.parents()) {
            const auto i(pgs.find(parent));
            if (i == pgs.end()) {
                BOOST_LOG_SEV(lg, error) << parent_not_found << parent;
                BOOST_THROW_EXCEPTION(
                    expansion_error(parent_not_found + parent));
            }
        }

        /*
         * Facet names used in profiles must have been defined in
         * formatter container.
         */
        for (const auto& pair : pg.facet_profiles()) {
            const auto fctn(pair.first);
            const auto i(facet_names.find(fctn));
            if (i == facet_names.end()) {
                BOOST_LOG_SEV(lg, error) << invalid_facet_name << fctn;
                BOOST_THROW_EXCEPTION(
                    expansion_error(invalid_facet_name + fctn));
            }
        }

        /*
         * Formatter names used in profiles must have been defined in
         * formatter container.
         */
        for (const auto& pair : pg.formatter_profiles()) {
            const auto fmtn(pair.first);
            const auto i(formatter_names.find(fmtn));
            if (i == formatter_names.end()) {
                BOOST_LOG_SEV(lg, error) << invalid_formatter_name << fmtn;
                BOOST_THROW_EXCEPTION(
                    expansion_error(invalid_formatter_name + fmtn));
            }
        }
        BOOST_LOG_SEV(lg, debug) << "Validated profile group.";
    }
}

profile_group_expander::profile_group_types
profile_group_expander::merge(const profile_group_types& original) const {
    profile_group_expander::profile_group_types r;
    profile_group_merger mg;
    return mg.merge(original);
}

void profile_group_expander::populate_model(const dynamic::repository& drp,
    const dynamic::object& root_object, const profile_group_types& pgs,
    model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Populating model with profile groups.";

    /*
     * First setup the global profile.
     */
    const auto fd(make_field_definitions(drp));
    const auto global_cfg(obtain_profile_configuration(fd, root_object));
    const auto i(pgs.find(global_cfg));
    if (i == pgs.end()) {
        BOOST_LOG_SEV(lg, error) << invalid_profile_configuration << global_cfg;
        BOOST_THROW_EXCEPTION(
            expansion_error(invalid_profile_configuration + global_cfg));
    }

    const auto& gpg(i->second);
    fm.global_profile_group(gpg);

    /*
     * Create a map of configurations to binding stereotypes.
     */
    profile_group_types binding_stereotypes;
    for (const auto& pair : pgs) {
        const auto pgn(pair.first);
        const auto& pg(pair.second);
        const auto bts(pg.bind_to_stereotype());
        if (bts.empty())
            continue;

        const auto stereotype_pair(std::make_pair(bts, pg));
        const auto inserted(binding_stereotypes.insert(stereotype_pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_bind << bts
                                     << " profile: " << pgn;
            BOOST_THROW_EXCEPTION(expansion_error(duplicate_bind + bts));
        }
    }

    /*
     * Now go through all the master segments and setup the local
     * configuration.
     */
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);

        auto& formattable(pair.second);
        const auto& e(*formattable.master_segment());

        /*
         * We only care about the target model elements.
         */
        if (e.origin_type() != yarn::origin_types::target)
            continue;

        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        /*
         * First see if we bind to any of the defined stereotypes. We
         * can only bind to one.
         */
        boost::optional<profile_group> bound;
        for (const auto s : e.stereotypes()) {
            // FIXME: hack until stereotypes are strings
            std::string str;
            if (s == yarn::stereotypes::formatter)
                str = "formatter";
            else if (s == yarn::stereotypes::handcrafted)
                str = "handcrafted";

            const auto i(binding_stereotypes.find(str));
            if (i != binding_stereotypes.end()) {
                if (bound) {
                    BOOST_LOG_SEV(lg, error) << too_many_binds << str
                                             << " type: " << id;
                    BOOST_THROW_EXCEPTION(
                        expansion_error(too_many_binds + str));
                }
                const auto& lpg(i->second);
                bound = lpg;
            }
        }

        if (bound) {
            auto& ecfg(formattable.element_configuration());
            ecfg.local_profile_group(*bound);
            BOOST_LOG_SEV(lg, debug) << "Stereotype-bound profile group: "
                                     << bound->name();
            continue;
        }

        /*
         * Now look at the profile configuration. We only care about
         * cases where the local profile configuration is different
         * from the global profile configuration; if they are the
         * same, there is no point in setting it up.
         */
        const auto local_cfg(obtain_profile_configuration(fd,e.extensions()));
        if (local_cfg == global_cfg) {
            BOOST_LOG_SEV(lg, debug) << "Local profile group configuration "
                                     << "is same as global: " << local_cfg;
            continue;
        }

        /*
         * Locate the profile group for the configuration, ensuring
         * its of the correct type, and slot it in.
         */
        const auto i(pgs.find(local_cfg));
        if (i == pgs.end()) {
            BOOST_LOG_SEV(lg, error) << missing_profile_configuration
                                     << local_cfg;
            BOOST_THROW_EXCEPTION(
                expansion_error(missing_profile_configuration + local_cfg));
        }

        const auto& lpg(i->second);
        if (lpg.profile_type() != profile_types::local) {
            BOOST_LOG_SEV(lg, error) << invalid_profile_configuration
                                     << local_cfg
                                     << " expected type to be local but is: "
                                     << lpg.profile_type();
            BOOST_THROW_EXCEPTION(
                expansion_error(invalid_profile_configuration + local_cfg));
        }

        auto& ecfg(formattable.element_configuration());
        ecfg.local_profile_group(lpg);
        BOOST_LOG_SEV(lg, debug) << "Set profile group: " << local_cfg;
    }

    BOOST_LOG_SEV(lg, debug) << "Populated model with profile groups.";
}

void profile_group_expander::expand(
    const std::forward_list<boost::filesystem::path>& data_directories,
    const dynamic::repository& drp, const dynamic::object& root_object,
    const formatters::container& fc, model& fm) const {

    const auto original(hydrate(data_directories));
    validate(fc, original);
    const auto merged(merge(original));
    populate_model(drp, root_object, merged, fm);
}

} } } }
