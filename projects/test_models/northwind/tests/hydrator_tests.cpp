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
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test_data/northwind.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/tds_test_good.hpp"
#include "dogen/test_models/northwind/io/repository_io.hpp"
#include "dogen/test_models/northwind/types/hydrator.hpp"

namespace  {

const std::string test_suite("hydrator_tests");
const std::string test_module("northwind");

const std::string region_data("INSERT [dbo].[Region] ([RegionID], [RegionDescription]) VALUES (1, N'Eastern                               ");

}

using dogen::test_models::northwind::hydrator;

BOOST_AUTO_TEST_SUITE(hydrator_tests)

BOOST_AUTO_TEST_CASE(hydrating_region_results_in_expected_data) {
    SETUP_TEST_LOG_SOURCE("hydrating_region_results_in_expected_data");

    std::istringstream iss(region_data);
    hydrator h;
    const auto rp(h.hydrate(iss));
    BOOST_LOG_SEV(lg, debug) << "Result: " << rp;
}

BOOST_AUTO_TEST_SUITE_END()
