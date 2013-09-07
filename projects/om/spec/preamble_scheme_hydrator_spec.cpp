/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/om/types/all.hpp"
#include "dogen/om/io/all_io.hpp"
#include "dogen/om/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("om");
const std::string test_suite("preamble_scheme_hydrator_spec");

const std::string preamble_schemes_dir("preamble_schemes");

}

using namespace dogen::om;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(preamble_scheme_hydrator)

BOOST_AUTO_TEST_CASE(preamble_scheme_hydrator_loads_expected_templates_from_data_directory) {
    SETUP_TEST_LOG_SOURCE("preamble_scheme_hydrator_loads_expected_templates_from_data_directory");

    using namespace dogen::utility::filesystem;
    const std::list<boost::filesystem::path> d = {
        // executable_directory()
        data_files_directory() / preamble_schemes_dir
    };

    dogen::om::preamble_scheme_hydrator f(d);
    const auto r(f.hydrate());

    BOOST_LOG_SEV(lg, debug) << "schemes: " << r;
    BOOST_CHECK(!r.empty());

    for (const auto& schemes : r) {
        BOOST_CHECK(!schemes.first.empty());
        BOOST_CHECK(!schemes.second.preambles().empty());
        for (const auto& preambles : schemes.second.preambles()) {
            BOOST_CHECK(!preambles.first.empty());
            BOOST_CHECK(!preambles.second.fields().empty());

            // value  may be empty so nothing can be said about it.
            for (const auto& fields : preambles.second.fields())
                BOOST_CHECK(!fields.name().empty());
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
