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
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/building_error.hpp"
#include "dogen/annotations/io/archetype_location_repository_io.hpp"
#include "dogen/annotations/types/archetype_location_repository_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("annotations.archetype_location_repository_builder"));

const std::string empty_kernel("Kernel name cannot be empty. Archetype: ");
const std::string empty_facet("Facet name cannot be empty. Archetype: ");
const std::string empty_archetype("Archetype name cannot be empty.");

}

namespace dogen {
namespace annotations {

void archetype_location_repository_builder::
validate(const std::list<archetype_location>& als) const {
    BOOST_LOG_SEV(lg, debug) << "Validating archetype locations.";

    for (const auto& al : als) {
        if (al.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_archetype;
            BOOST_THROW_EXCEPTION(building_error(empty_archetype));
        }

        if (al.kernel().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_kernel << al.archetype();
            BOOST_THROW_EXCEPTION(
                building_error(empty_kernel + al.archetype()));
        }

        if (al.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_facet << al.archetype();
            BOOST_THROW_EXCEPTION(building_error(empty_facet + al.archetype()));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Archetype locations are valid.";
}

void archetype_location_repository_builder::
populate_locations(const std::list<archetype_location>& als) {
    for(const auto& al : als)
        repository_.archetype_locations().push_back(al);
}

void archetype_location_repository_builder::
populate_facet_names_by_kernel_name() {
    auto& fnbkn(repository_.facet_names_by_kernel_name());
    for (const auto& al : repository_.archetype_locations())
        fnbkn[al.kernel()].insert(al.facet());
}

void archetype_location_repository_builder::
populate_formatter_names_by_kernel_name() {
    auto& fnbkn(repository_.formatter_names_by_kernel_name());
    for (const auto& al : repository_.archetype_locations())
        fnbkn[al.kernel()].insert(al.archetype());
}

void archetype_location_repository_builder::
add(const std::list<archetype_location>& als) {
    BOOST_LOG_SEV(lg, debug) << "Adding list of archetype location.";

    validate(als);
    populate_locations(als);

    BOOST_LOG_SEV(lg, debug) << "Added archetype location list. ";
}

void archetype_location_repository_builder::add(const std::unordered_map<
    std::string, std::list<annotations::archetype_location>>&
    archetype_locations_by_meta_name) {
    auto& albmn(repository_.archetype_locations_by_meta_name());
    for (const auto& pair : archetype_locations_by_meta_name) {
        const auto& mn(pair.first);
        const auto& als(pair.second);
        albmn[mn] = als;
        add(als);
    }
}

const archetype_location_repository&
archetype_location_repository_builder::build() {
    populate_facet_names_by_kernel_name();
    populate_formatter_names_by_kernel_name();

    BOOST_LOG_SEV(lg, debug) << "Repository built: " << repository_;
    return repository_;
}

} }
