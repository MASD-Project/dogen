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
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.variability/io/entities/configuration_point_io.hpp"
#include "dogen.variability/types/helpers/configuration_point_merger.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "variability.helpers.configuration_point_merger"));

}

namespace dogen::variability::helpers {

std::unordered_map<std::string, entities::configuration_point>
configuration_point_merger::merge(
    const std::string& lhs_name, const std::unordered_map<std::string,
    entities::configuration_point>& lhs, const std::string& rhs_name,
    const std::unordered_map<std::string,
    entities::configuration_point>& rhs) const {
    BOOST_LOG_SEV(lg, debug) << "Merging configurations."
                             << " lhs: " << lhs_name
                             << " rhs: " << rhs_name;
    BOOST_LOG_SEV(lg, trace) << "lhs: " << lhs;
    BOOST_LOG_SEV(lg, trace) << "rhs: " << rhs;

    std::unordered_map<std::string, entities::configuration_point> r(lhs);
    for (const auto& pair : rhs)
        r.insert(pair);

    BOOST_LOG_SEV(lg, debug) << "Merged configurations. ";
    BOOST_LOG_SEV(lg, trace) << "Result: " << r;
    return r;
}

}
