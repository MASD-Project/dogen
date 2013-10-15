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
#include <istream>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/om/types/hydration_workflow.hpp"

namespace {

const std::string empty;
const std::string test_module("om");
const std::string test_suite("hydration_workflow_spec");

const std::string modeline_groups_dir("modeline_groups");

class mock_hydrator {
public:
    typedef std::string value_type;

    mock_hydrator() : counter_(0) { }

    value_type hydrate(std::istream&) const {
        ++counter_;
        std::ostringstream s;
        s << "file_" << counter_;
        return s.str();
    }

private:
    mutable unsigned int counter_;
};

}

using namespace dogen::om;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(hydration_workflow)

BOOST_AUTO_TEST_CASE(hydrating_modeline_groups_in_data_directory_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("hydrating_modeline_groups_in_data_directory_produces_expected_result");

    using namespace dogen::utility::filesystem;
    const std::list<boost::filesystem::path> d = {
        data_files_directory() / modeline_groups_dir
    };

    dogen::om::hydration_workflow<mock_hydrator> hw;
    const auto r(hw.hydrate(d));

    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    BOOST_CHECK(!r.empty());

    for (const auto& pair : r) {
        BOOST_CHECK(!pair.first.empty());
        BOOST_CHECK(!pair.second.empty());
    }
}

BOOST_AUTO_TEST_SUITE_END()
