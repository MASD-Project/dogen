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
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/options/types/validation_error.hpp"
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/options/test/mock_options_factory.hpp"
#include "dogen/options/types/knitting_options_validator.hpp"

namespace {

const std::string empty;
const boost::filesystem::path empty_dir;
const std::string test_module("options");
const std::string test_suite("knitting_options_validator_tests");

const boost::filesystem::path target("some_target");
const boost::filesystem::path project_dir("proj directory");
const std::string epp("package::path");

const std::string missing_target("Mandatory parameter target is missing");
const std::string missing_project_dir("You must supply the project directory");

dogen::options::knitting_options target_only() {
    using dogen::options::test::mock_options_factory;
    return mock_options_factory::make_knitting_options(target);
}

dogen::options::knitting_options target_and_project_dir() {
    using dogen::options::test::mock_options_factory;
    return mock_options_factory::make_knitting_options(target, project_dir);
}

}

using dogen::utility::test::contains_checker;
using dogen::options::validation_error;

BOOST_AUTO_TEST_SUITE(knitting_options_validator_tests)

BOOST_AUTO_TEST_CASE(options_without_a_target_throws) {
    SETUP_TEST_LOG_SOURCE("options_without_a_target_throws");

    dogen::options::knitting_options o;
    BOOST_CHECK(o.input().target().empty());
    contains_checker<validation_error> c(missing_target);

    dogen::options::knitting_options_validator v;
    BOOST_CHECK_EXCEPTION(v.validate(o), validation_error, c);
}

BOOST_AUTO_TEST_CASE(options_with_a_target_are_valid) {
    SETUP_TEST_LOG_SOURCE("options_with_a_target_are_valid");
    dogen::options::knitting_options_validator v;
    v.validate(target_and_project_dir());
}

BOOST_AUTO_TEST_CASE(options_without_a_project_directory_throws) {
    SETUP_TEST_LOG_SOURCE("options_without_a_project_directory_throws");

    contains_checker<validation_error> c(missing_project_dir);
    dogen::options::knitting_options_validator v;
    BOOST_CHECK_EXCEPTION(v.validate(target_only()), validation_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
