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
#include "dogen/annotations/types/archetype_location_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("annotations.archetype_location_repository_factory"));

const std::string empty_model_name("Model name cannot be empty. Formatter: ");
const std::string empty_facet_name("Facet name cannot be empty. Formatter: ");
const std::string empty_formatter_name("Formatter name cannot be empty");

}

namespace dogen {
namespace annotations {

void archetype_location_repository_factory::
validate(const std::list<archetype_location>& ohs) const {
    BOOST_LOG_SEV(lg, debug) << "Validating input ownership hierachies.";

    for (const auto& oh : ohs) {
        if (oh.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        if (oh.kernel().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_model_name << oh.archetype();
            BOOST_THROW_EXCEPTION(
                building_error(empty_model_name + oh.archetype()));
        }

        if (oh.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_facet_name << oh.archetype();
            BOOST_THROW_EXCEPTION(
                building_error(empty_facet_name + oh.archetype()));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Input ownership hierachies are valid.";
}

void archetype_location_repository_factory::
populate_ownership_hierarchies(const std::list<archetype_location>& ohs,
    archetype_location_repository& rp) const {
    rp.ownership_hierarchies().reserve(ohs.size());
    for (const auto& oh : ohs)
        rp.ownership_hierarchies().push_back(oh);
}

void archetype_location_repository_factory::
populate_facet_names_by_model_name(archetype_location_repository& rp) const {

    for (const auto& oh : rp.ownership_hierarchies())
        rp.facet_names_by_model_name()[oh.kernel()].insert(oh.facet());
}

void archetype_location_repository_factory::
populate_formatter_names_by_model_name(
    archetype_location_repository& rp) const {

    for (const auto& oh : rp.ownership_hierarchies()) {
        const auto fmtn(oh.archetype());
        rp.formatter_names_by_model_name()[oh.kernel()].insert(fmtn);
    }
}

archetype_location_repository archetype_location_repository_factory::
make(const std::list<archetype_location>& ohs) const {
    BOOST_LOG_SEV(lg, debug) << "Creating ownership hierachy repository.";
    validate(ohs);

    archetype_location_repository r;
    populate_ownership_hierarchies(ohs, r);
    populate_facet_names_by_model_name(r);
    populate_formatter_names_by_model_name(r);
    BOOST_LOG_SEV(lg, debug) << "Created ownership hierachy repository. "
                             << "Result: " << r;
    return r;
}

} }
