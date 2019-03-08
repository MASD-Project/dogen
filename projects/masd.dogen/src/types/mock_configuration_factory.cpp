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
#include <boost/filesystem/operations.hpp>
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen/io/configuration_io.hpp"
#include "masd.dogen/types/mock_configuration_factory.hpp"

namespace  {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("mock_configuration_factory"));

const std::string byproduct_directory("masd.dogen.byproducts/");
const std::string tracing_directory("tracing");
const std::string run_identifier_prefix("tests");

}

namespace masd::dogen {

configuration
mock_configuration_factory::
make(const boost::filesystem::path& target, bool enable_tracing) {
    BOOST_LOG_SEV(lg, debug) << "Creating mock configuration.";
    BOOST_LOG_SEV(lg, debug) << "Target: " << target.generic_string()
                             << " enable_tracing: " << enable_tracing;

    using namespace masd::dogen;
    configuration r;

    std::ostringstream s;
    s << run_identifier_prefix;

    const auto fn(target.filename().string());
    if (!fn.empty())
        s << "." << fn;

    const auto run_id(s.str());
    using boost::filesystem::absolute;
    r.byproduct_directory(absolute(byproduct_directory + run_id));

    diffing_configuration dcfg;
    dcfg.destination(diffing_destination::file);
    dcfg.output_directory(r.byproduct_directory());
    r.diffing(dcfg);

    if (enable_tracing) {
        tracing_configuration tcfg;
        tcfg.level(tracing_level::detail);
        tcfg.format(tracing_format::org_mode);
        tcfg.guids_enabled(true);
        tcfg.logging_impact("severe");
        tcfg.output_directory(r.byproduct_directory() / tracing_directory);
        r.tracing(tcfg);
    }

    reporting_configuration rcfg;
    rcfg.style(reporting_style::org_mode);
    rcfg.output_directory(r.byproduct_directory());
    r.reporting(rcfg);

    BOOST_LOG_SEV(lg, debug) << "Finished creating mock configuration. Result: "
                             << r;
    return r;
}

}
