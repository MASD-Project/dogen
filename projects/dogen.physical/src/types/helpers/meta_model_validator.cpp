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
#include "dogen.physical/io/entities/meta_name_io.hpp"
#include "dogen.physical/types/helpers/qualified_meta_name_builder.hpp"
#include "dogen.physical/types/helpers/validation_error.hpp"
#include "dogen.physical/types/helpers/meta_name_validator.hpp"
#include "dogen.physical/types/helpers/meta_model_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("physical.helpers.meta_model_validator"));

const std::string more_than_one_canonical_archetype(
    "Found more than one canonical transform for a facet: ");
const std::string facets_missing_canonical_archetype(
    "One or more facets have been declared without a canonical archetype");

}

namespace dogen::physical::helpers {

void meta_model_validator::validate(physical::entities::meta_model& mm) {
    /*
     * Validate the registered canonical transforms.
     */
    std::set<std::string> facets_found;
    std::set<std::string> all_facets;

    const auto rs_fd(entities::relation_status::facet_default);
    for (auto& be : mm.backends()) {
        for (auto& fct_pair : be.facets()) {
            auto& fct(fct_pair.second);
            for (auto& arch_pair : fct.archetypes()) {
                const auto& lmn(arch_pair.first);
                auto& arch(arch_pair.second);

                BOOST_LOG_SEV(lg, debug) << "Processing: " << lmn;

                std::set<std::string> facets_found;
                std::set<std::string> all_facets;
                using qnb = physical::helpers::qualified_meta_name_builder;

                const auto pmn(arch.meta_name());
                const auto fct(qnb::build_facet(pmn));
                all_facets.insert(fct);
                if (arch.relation_status() == rs_fd) {
                    continue;

                    /*
                     * We can only have one canonical transform per
                     * type per facet.
                     */
                    const auto i(facets_found.find(fct));
                    if (i != facets_found.end()) {
                        const auto arch(pmn.qualified());
                        BOOST_LOG_SEV(lg, error) << more_than_one_canonical_archetype
                                                 << fct << " archetype: "
                                                 << pmn.qualified()
                                                 << " meta name: " << lmn;
                        BOOST_THROW_EXCEPTION(validation_error(
                                more_than_one_canonical_archetype + fct));
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
    std::set<std::string> result;
    std::set_difference(all_facets.begin(), all_facets.end(),
        facets_found.begin(), facets_found.end(),
        std::inserter(result, result.end()));
    if (!result.empty()) {
        BOOST_LOG_SEV(lg, warn) << facets_missing_canonical_archetype
                                << " : " << result;
    }
}

}
