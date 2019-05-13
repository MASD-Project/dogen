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
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.coding/io/meta_model/technical_space_io.hpp"
#include "dogen.coding/io/helpers/mapping_io.hpp"
#include "dogen.coding/io/helpers/mapping_set_io.hpp"
#include "dogen.coding/io/helpers/mapping_set_repository_io.hpp"
#include "dogen.coding/io/helpers/mapping_actions_io.hpp"
#include "dogen.coding/types/helpers/building_error.hpp"
#include "dogen.coding/types/helpers/mappings_hydrator.hpp"
#include "dogen.coding/types/helpers/mappings_validator.hpp"
#include "dogen.coding/types/helpers/mapping_set_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("coding.helpers.mapping_set_repository_factory"));

const std::string mappings_dir("mappings");

const std::string duplicate_agnostic_id("Duplicate agnostic id: ");
const std::string default_mapping_set_name("default.mapping_set");
const std::string duplicate_mapping_set(
    "Found more than one mapping set with name: ");

}

namespace dogen::coding::helpers {

std::unordered_map<std::string, std::list<mapping>>
mapping_set_repository_factory::
obtain_mappings(const std::vector<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, debug) << "Reading all mappings.";

    mappings_hydrator h;
    std::unordered_map<std::string, std::list<mapping>> r;
    for (const auto& top_level_dir : dirs) {
        const boost::filesystem::path mdir(top_level_dir / mappings_dir);
        BOOST_LOG_SEV(lg, trace) << "Mapping directory: "
                                 << mdir.generic_string();

        using namespace dogen::utility::filesystem;
        const auto files(find_files(mdir));

        BOOST_LOG_SEV(lg, trace) << "Found " << files.size()
                                 << " mapping files.";

        for (const auto& f : files) {
            BOOST_LOG_SEV(lg, trace) << "Mapping file: " << f.generic_string();

            const auto n(f.stem().string());
            const auto mappings(h.hydrate(f));
            const auto pair(std::make_pair(n, mappings));
            const auto inserted(r.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_mapping_set << n;
                BOOST_THROW_EXCEPTION(
                    building_error(duplicate_mapping_set + n));
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Read all mappings. Result: " << r;
    return r;
}

void mapping_set_repository_factory::validate_mappings(
    const std::unordered_map<std::string, std::list<mapping>>& mappings) const {
    mappings_validator v;
    v.validate(mappings);
}

void mapping_set_repository_factory::
insert(const std::string& agnostic_id, const meta_model::name& n,
    const meta_model::technical_space ts,
    std::unordered_map<meta_model::technical_space,
    std::unordered_map<std::string, meta_model::name>>& map) const {

    auto& by_id(map[ts]);
    const auto pair(std::make_pair(agnostic_id, n));
    const auto inserted(by_id.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_agnostic_id << agnostic_id;
        BOOST_THROW_EXCEPTION(
            building_error(duplicate_agnostic_id + agnostic_id));
    }

    BOOST_LOG_SEV(lg, debug) << "Mapped: '" << agnostic_id
                             << "' to '" << n.qualified().dot() << "'";
}

void mapping_set_repository_factory::populate_mapping_set(
    const std::list<mapping>& mappings, mapping_set& ms) const {

    for (const auto& mapping : mappings) {
        const auto agnostic_id(mapping.agnostic_id());

        for (const auto& pair : mapping.by_technical_space()) {
            const auto l(pair.first);
            const auto& mv(pair.second);

            BOOST_LOG_SEV(lg, debug) << "Processing mapping action: "
                                     << mv.mapping_action();

            if (mv.mapping_action() == mapping_actions::erase) {
                ms.erasures_by_technical_space()[l].insert(agnostic_id);
                continue;
            }

            const auto n(*mv.default_name());
            insert(agnostic_id, n, l, ms.by_agnostic_id());
        }
    }
}

mapping_set_repository mapping_set_repository_factory::
create_repository(const std::unordered_map<std::string, std::list<mapping>>&
    mappings_by_set_name) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating mapping set repository.";
    mapping_set_repository r;

    /*
     * Loop through each supplied list of mappings - pertaining to
     * different files originally - and add each one to the mapping
     * repository as a different mapping set.
     */
    for (const auto& pair : mappings_by_set_name) {
        const auto& n(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Populating mapping set: " << n;

        /*
         * The default mapping set is special, and has its own place
         * in the repository. All other mapping sets are stored by
         * their names.
         */
        const auto& mappings(pair.second);
        const auto& is_default(n == default_mapping_set_name);
        auto& ms(is_default ? r.default_mapping_set() : r.by_name()[n]);
        populate_mapping_set(mappings, ms);

        BOOST_LOG_SEV(lg, debug) << "Finished populating mapping set.";
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating mapping set repository.";
    return r;
}

mapping_set_repository mapping_set_repository_factory::make(
    const std::vector<boost::filesystem::path>& dirs) const {
    const auto mappings(obtain_mappings(dirs));
    validate_mappings(mappings);
    return create_repository(mappings);
}

}
