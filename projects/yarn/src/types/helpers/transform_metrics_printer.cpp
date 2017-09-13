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
#include <sstream>
#include <iomanip>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/helpers/transform_metrics_printer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.transform_metrics_printer"));

const char filler(' ');
const unsigned int fill_size(4);

}

namespace dogen {
namespace yarn {
namespace helpers {

void transform_metrics_printer::print(std::ostream& o, unsigned int fill_level,
    const bool disable_guids_in_stats,
    const boost::shared_ptr<const transform_metrics> tm) {

    BOOST_LOG_SEV(lg, debug) << "Fill level: " << fill_level;
    auto elapsed (tm->end() - tm->start());
    o << std::string(fill_size * fill_level, filler)
      << tm->transform_id() << " (" << elapsed  << " ms)"
      << " [" << tm->model_id() << "]";

    if (!disable_guids_in_stats)
        o << " [" << tm->guid() << "]";

    o << std::endl;

    ++fill_level;
    for(auto child : tm->children())
        print(o, fill_level, disable_guids_in_stats, child);
}

std::string transform_metrics_printer::print(const bool disable_guids_in_stats,
    const boost::shared_ptr<const transform_metrics> tm) {
    BOOST_LOG_SEV(lg, debug) << "Printing graph.";

    unsigned int fill_level(0);
    std::ostringstream s;
    print(s, fill_level, disable_guids_in_stats, tm);
    const auto r(s.str());

    BOOST_LOG_SEV(lg, debug) << "Finished printing graph.";
    return r;
}

} } }
