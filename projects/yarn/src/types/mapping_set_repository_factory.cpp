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
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/io/mapping_io.hpp"
#include "dogen/yarn/io/mapping_set_io.hpp"
#include "dogen/yarn/io/mapping_set_repository_io.hpp"
#include "dogen/yarn/io/mapping_actions_io.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/mappings_hydrator.hpp"
#include "dogen/yarn/types/mappings_validator.hpp"
#include "dogen/yarn/types/mapping_set_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.mapping_set_repository_factory"));

const std::string duplicate_lam_id("Duplicate language agnostic id: ");
const std::string duplicate_upsilon_id("Duplicate upsilon id: ");
const std::string default_mapping_set_name("default.mapping_set");
const std::string duplicate_mapping_set(
    "Found more than one mapping set with name: ");

const std::string mappings_dir("mappings");


}

namespace dogen {
namespace yarn {

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
insert(const std::string& upsilon_id, const std::string& lam_id,
    std::unordered_map<std::string, std::string>& map) const {

    const auto pair(std::make_pair(upsilon_id, lam_id));
    const auto inserted(map.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_upsilon_id << upsilon_id;
        BOOST_THROW_EXCEPTION(
            building_error(duplicate_upsilon_id + upsilon_id));
    }

    BOOST_LOG_SEV(lg, debug) << "Mapped: '" << upsilon_id
                             << "' to '" << lam_id << "'";
}

void mapping_set_repository_factory::
insert(const std::string& lam_id, const name& n, const languages l,
    std::unordered_map<languages, std::unordered_map<std::string, name>>&
    by_languages) const {

    auto& by_id(by_languages[l]);
    const auto pair(std::make_pair(lam_id, n));
    const auto inserted(by_id.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_lam_id << lam_id;
        BOOST_THROW_EXCEPTION(building_error(duplicate_lam_id + lam_id));
    }

    BOOST_LOG_SEV(lg, debug) << "Mapped: '" << lam_id << "' to '"
                             << n.id() << "'";
}

void mapping_set_repository_factory::populate_upsilon_data(
    const std::string& lam_id, const mapping& mapping,
    const mapping_value& upsilon_mv, mapping_set& ms) const {

    /*
     * A given LAM ID may map to zero, one or many upsilon names. We
     * are only interested in creating a map between the upsilon ID
     * and all other IDs: the concrete programming languages and LAM
     * itself. We need the concrete programming languages because the
     * key use case is to code-generate a upsilon model as a concrete
     * programming language model. We also need LAM because we may
     * want to generate a JSON representation of upsilon, translated
     * to LAM.
     *
     * First we map the default upsilon ID to all available
     * programming languages. We only care about non-upsilon -
     * identity mapping is not useful - and we only care about the
     * default type - we don't expect aliases for other languages
     * (validated above us).
     */
    const auto default_upsilon_id(upsilon_mv.default_name()->id());
    for (const auto& pair : mapping.by_language()) {
        const auto l(pair.first);
        if (l == languages::upsilon)
            continue;

        const auto& n(*(pair.second.default_name()));
        insert(default_upsilon_id, n, l, ms.by_upsilon_id());
    }

    /*
     * Map the default upsilon ID to the LAM ID.
     */
    auto& utl(ms.upsilon_id_to_lam_id());
    insert(default_upsilon_id, lam_id, utl);

    /*
     * Now we repeat the exercise for the aliases.
     */
    for (const auto& un : upsilon_mv.aliases()) {
        for (const auto& pair : mapping.by_language()) {
            const auto l(pair.first);
            if (l == languages::upsilon)
                continue;

            const auto& n(*(pair.second.default_name()));
            insert(un.id(), n, l, ms.by_upsilon_id());
        }

        insert(un.id(), lam_id, utl);
    }
}

void mapping_set_repository_factory::populate_mapping_set(
    const std::list<mapping>& mappings, mapping_set& ms) const {

    for (const auto& mapping : mappings) {
        const auto lam_id(mapping.lam_id());

        for (const auto& pair : mapping.by_language()) {
            const auto l(pair.first);
            const auto& mv(pair.second);

            BOOST_LOG_SEV(lg, debug) << "Processing mapping action: "
                                     << mv.mapping_action();

            if (mv.mapping_action() == mapping_actions::erase) {
                ms.erasures_by_language()[l].insert(lam_id);
                continue;
            }

            if (l == languages::upsilon) {
                /*
                 * For upsilon we need to perform additional (complex)
                 * processing.
                 */
                populate_upsilon_data(lam_id, mapping, mv, ms);
            } else {
                /*
                 * Note that we only process the default name, and
                 * ignore aliases. This is because we don't expect
                 * aliases for languages other than upsilon (validated
                 * above us).
                 */
                const auto n(*mv.default_name());
                insert(lam_id, n, l, ms.by_language_agnostic_id());
            }
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

} }
