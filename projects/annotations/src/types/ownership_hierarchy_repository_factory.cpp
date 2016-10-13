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
#include "dogen/annotations/io/ownership_hierarchy_repository_io.hpp"
#include "dogen/annotations/types/ownership_hierarchy_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("annotations.ownership_hierarchy_repository_factory"));

const std::string empty_model_name("Model name cannot be empty. Formatter: ");
const std::string empty_facet_name("Facet name cannot be empty. Formatter: ");
const std::string empty_formatter_name("Formatter name cannot be empty");

}

namespace dogen {
namespace annotations {

void ownership_hierarchy_repository_factory::
validate(const std::list<ownership_hierarchy>& ohs) const {
    BOOST_LOG_SEV(lg, debug) << "Validating input ownership hierachies.";

    for (const auto& oh : ohs) {
        if (oh.formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        if (oh.model_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_model_name << oh.formatter_name();
            BOOST_THROW_EXCEPTION(
                building_error(empty_model_name + oh.formatter_name()));
        }

        if (oh.facet_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_facet_name << oh.formatter_name();
            BOOST_THROW_EXCEPTION(
                building_error(empty_facet_name + oh.formatter_name()));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Input ownership hierachies are valid.";
}

void ownership_hierarchy_repository_factory::
populate_ownership_hierarchies(const std::list<ownership_hierarchy>& ohs,
    ownership_hierarchy_repository& rp) const {
    rp.ownership_hierarchies().reserve(ohs.size());
    for (const auto& oh : ohs)
        rp.ownership_hierarchies().push_back(oh);
}

void ownership_hierarchy_repository_factory::populate_facet_names_by_model_name(
    ownership_hierarchy_repository& rp) const {

    for (const auto& oh : rp.ownership_hierarchies()) {
        rp.facet_names_by_model_name()[oh.model_name()].insert(oh.facet_name());
    }
}

ownership_hierarchy_repository ownership_hierarchy_repository_factory::
make(const std::list<ownership_hierarchy>& ohs) const {
    BOOST_LOG_SEV(lg, debug) << "Creating ownership hierachy repository.";
    validate(ohs);

    ownership_hierarchy_repository r;
    populate_ownership_hierarchies(ohs, r);
    populate_facet_names_by_model_name(r);
    BOOST_LOG_SEV(lg, debug) << "Created ownership hierachy repository. "
                             << "Result: " << r;
    return r;
}

} }
