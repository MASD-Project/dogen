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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/set_io.hpp"
#include "dogen.utility/types/io/forward_list_io.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_validator.hpp"
#include "dogen.physical/types/helpers/validation_error.hpp"
#include "dogen.physical/types/helpers/meta_model_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("physical.helpers.meta_model_validator"));

const std::string more_than_one_canonical_archetype(
    "Found more than one canonical transform for a facet: ");
const std::string facets_missing_canonical_archetype(
    "One or more facets have been declared without a canonical archetype");

}

namespace dogen::identification::entities {

inline bool
operator<(const physical_meta_id& lhs, const physical_meta_id& rhs) {
    return lhs.value() < rhs.value();
}

}

namespace dogen::physical::helpers {

using dogen::identification::entities::physical_meta_id;

void meta_model_validator::validate(physical::entities::meta_model& mm) {
    /*
     * Validate the registered canonical transforms.
     */
    std::set<physical_meta_id> facets_found;
    std::set<physical_meta_id> all_facets;

    const auto rs_fd(entities::relation_status::facet_default);
    for (const auto& be : mm.backends()) {
        for (const auto& fct_pair : be.facets()) {
            const auto& fct(fct_pair.second);
            for (const auto& arch_pair : fct.archetypes()) {
                const auto& pmid(arch_pair.first);
                const auto& arch(arch_pair.second);

                BOOST_LOG_SEV(lg, debug) << "Processing: " << pmid;

                identification::helpers::physical_meta_id_builder b;
                const auto pmn(arch.meta_name());
                const auto fct(b.build_facet(pmn));
                all_facets.insert(fct);
                if (arch.relations().status() == rs_fd) {
                    continue;

                    // FIXME: this logic is incorrect. Check this when
                    // we have a stable code base again.
                    /*
                     * We can only have one canonical transform per
                     * type per facet.
                     */
                    const auto i(facets_found.find(fct));
                    if (i != facets_found.end()) {
                        const auto arch(pmn.id());
                        BOOST_LOG_SEV(lg, error)
                            << more_than_one_canonical_archetype
                            << fct << " archetype: "
                            << pmn.id()
                            << " meta id: " << pmid;
                        BOOST_THROW_EXCEPTION(validation_error(
                                more_than_one_canonical_archetype +
                                fct.value()));
                    }
                    facets_found.insert(fct);
                }
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "All Facets: " << all_facets;
    BOOST_LOG_SEV(lg, debug) << "Facets found: " << facets_found;

    /*
     * We should have one canonical transform per type per
     * facet. However, there are certain facet such as build and
     * visual studio where we don't actually require canonical
     * archetypes so we just warn.
     */
    std::set<physical_meta_id> result;
    std::set_difference(all_facets.begin(), all_facets.end(),
        facets_found.begin(), facets_found.end(),
        std::inserter(result, result.end()));
    if (!result.empty()) {
        BOOST_LOG_SEV(lg, warn) << facets_missing_canonical_archetype
                                << " : " << result;
    }
}

}
