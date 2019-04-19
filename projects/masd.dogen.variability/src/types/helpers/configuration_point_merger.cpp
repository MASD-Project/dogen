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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.variability/types/helpers/configuration_point_merger.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(
        "variability.helpers..configuration_point_merger"));

}

namespace masd::dogen::variability::helpers {

meta_model::configuration
configuration_point_merger::merge(const meta_model::configuration& lhs,
    const meta_model::configuration& rhs) const {
    BOOST_LOG_SEV(lg, debug) << "Merging configurations. Lhs"
                             << lhs.name().qualified()
                             << " Rhs: " << rhs.name().qualified();

    meta_model::configuration r(lhs);
    for (const auto& cp : rhs.configuration_points())
        r.configuration_points().insert(cp);

    BOOST_LOG_SEV(lg, debug) << "Merged configurations.";
    return r;
}

}
