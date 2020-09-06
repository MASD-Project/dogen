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
#include "dogen.identification/types/helpers/building_error.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_indices_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.identification/types/helpers/meta_name_index_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("identification.helpers.meta_name_index_builder"));

const std::string empty_backend("Backend name cannot be empty. Archetype: ");
const std::string empty_facet("Facet name cannot be empty. Archetype: ");
const std::string empty_archetype("Archetype name cannot be empty.");
const std::string duplicate_family("Duplicate family: ");
const std::string duplicate_archetype("Archetype name already inserted: ");

}

namespace dogen::identification::helpers {

void meta_name_index_builder::
validate(const std::list<entities::physical_meta_name>& mns) const {
    BOOST_LOG_SEV(lg, debug) << "Validating physical names.";

    for (const auto& mn : mns) {
        /*
         * We expect all three key coordinates of the location to be
         * populated.
         */
        const auto& l(mn.location());
        if (l.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_archetype;
            BOOST_THROW_EXCEPTION(building_error(empty_archetype));
        }

        if (l.backend().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_backend << l.archetype();
            BOOST_THROW_EXCEPTION(
                building_error(empty_backend + l.archetype()));
        }

        if (l.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_facet << l.archetype();
            BOOST_THROW_EXCEPTION(building_error(empty_facet + l.archetype()));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Physical names are valid.";
}

void meta_name_index_builder::
populate_names(const std::list<entities::physical_meta_name>& mns) {
    for(const auto& mn : mns)
        index_.all().push_back(mn);
}

void meta_name_index_builder::populate_facet_names_by_backend_name() {
    auto& fnbkn(index_.facet_names_by_backend_name());
    physical_meta_id_builder b;
    for (const auto& n : index_.all()) {
        const auto be(b.build_backend(n));
        const auto fct(b.build_facet(n));
        fnbkn[be].insert(fct);
    }
}

void meta_name_index_builder::populate_archetypes_by_facet_by_backend() {
    auto& abbbf(index_.archetype_names_by_backend_by_facet());
    physical_meta_id_builder b;
    for (const auto& n : index_.all()) {
        const auto be(b.build_backend(n));
        const auto fct(b.build_facet(n));
        abbbf[be][fct].push_back(n.id());
    }
}

void meta_name_index_builder::
add(const std::list<entities::physical_meta_name>& mns) {
    BOOST_LOG_SEV(lg, debug) << "Adding list of physical meta-names.";

    validate(mns);
    populate_names(mns);

    BOOST_LOG_SEV(lg, debug) << "Added list of physical names. ";
}

void meta_name_index_builder::
add(const std::unordered_map<entities::logical_meta_id,
    entities::archetype_name_set>& by_logical_meta_name) {
    auto& lmn(index_.archetype_names_by_logical_meta_name());
    for (const auto& pair : by_logical_meta_name) {
        BOOST_LOG_SEV(lg, debug) << "Processing: " << pair.first;
        /*
         * We start by inserting the physical meta-names into the
         * overall container with all physical meta-names across all
         * backends.
         */
        const auto& src(pair.second);
        add(src.meta_names());

        /*
         * Now lets populate the logical meta-name specific container.
         */
        const auto& mn(pair.first);
        auto& dst(lmn[mn]);
        dst.logical_meta_id(src.logical_meta_id());
        dst.archetype_for_label(src.archetype_for_label());

        /*
         * We need to merge the physical meta-names at the logical
         * meta-type level because each backend is reusing the same
         * set of logical meta-types.
         */
        for (const auto& n : src.meta_names())
            dst.meta_names().push_back(n);

        /*
         * However, when it comes down to the canonical archetype
         * mapping, we expect each archetype to be unique - after all,
         * no two text transforms are expected to point to the same
         * archetype (by definition). So, if we spot any duplicates
         * its an error.
         */
        auto& cal(dst.canonical_locations());
        for (const auto& pair : src.canonical_locations()) {
            const bool inserted(cal.insert(pair).second);
            if (!inserted) {
                const auto id(pair.first.value());
                BOOST_LOG_SEV(lg, error) << duplicate_archetype << id;
                BOOST_THROW_EXCEPTION(
                    building_error(duplicate_archetype + id));
            }
        }
    }
}

const entities::physical_meta_name_indices& meta_name_index_builder::build() {
    populate_facet_names_by_backend_name();
    populate_archetypes_by_facet_by_backend();

    BOOST_LOG_SEV(lg, debug) << "Index built: " << index_;
    return index_;
}

}
