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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/config/types/validation_error.hpp"
#include "dogen/config/types/knitting_options.hpp"
#include "dogen/config/test/mock_options_factory.hpp"
#include "dogen/config/types/knitting_options_validator.hpp"

namespace {

const std::string empty;
const boost::filesystem::path empty_dir;
const std::string test_module("config");
const std::string test_suite("knitting_options_validator_spec");

const boost::filesystem::path target("some_target");
const boost::filesystem::path src_dir("src directory");
const boost::filesystem::path include_dir("include directory");
const boost::filesystem::path project_dir("proj directory");
const std::string epp("package::path");

const std::string missing_target("Mandatory parameter target is missing");
const std::string missing_source_include("You must supply source and include");
const std::string missing_project_dir("You must supply the project directory");
const std::string unexpected_source_include("Source and include directory");
const std::string unexpected_project_dir("Project directory path cannot be");

dogen::config::knitting_options target_source_and_include() {
    return dogen::config::test::mock_options_factory::
        make_knitting_options(target, src_dir, include_dir, epp);
}

dogen::config::knitting_options target_only() {
    return dogen::config::test::mock_options_factory::
        make_knitting_options(target, empty_dir, empty_dir, empty);
}

dogen::config::knitting_options split_project(const bool split) {
    auto o(target_only());
    o.cpp().split_project(split);
    return o;
}

dogen::config::knitting_options
split_project(const bool split, const boost::filesystem::path& include,
    const boost::filesystem::path& src) {
    auto o(target_only());
    o.cpp().split_project(split);
    o.cpp().include_directory_path(include);
    o.cpp().source_directory_path(src);

    if (!split)
        o.cpp().project_directory_path(project_dir);

    return o;
}

dogen::config::knitting_options
split_project(const bool split, const boost::filesystem::path& proj) {
    auto o(target_only());

    o.cpp().split_project(split);
    o.cpp().project_directory_path(proj);

    if (split) {
        o.cpp().include_directory_path(include_dir);
        o.cpp().source_directory_path(src_dir);
    }

    return o;
}

}

using dogen::utility::test::contains_checker;
using dogen::config::validation_error;

BOOST_AUTO_TEST_SUITE(knitting_options_validator)

BOOST_AUTO_TEST_CASE(options_without_a_target_throw) {
    SETUP_TEST_LOG_SOURCE("options_without_a_target_throw");

    dogen::config::knitting_options o;
    BOOST_CHECK(o.input().target().empty());
    contains_checker<validation_error> c(missing_target);
    BOOST_CHECK_EXCEPTION(
        dogen::config::knitting_options_validator::validate(o),
        validation_error, c);
}

BOOST_AUTO_TEST_CASE(options_with_a_target_are_valid) {
    SETUP_TEST_LOG_SOURCE("options_with_a_target_are_valid");

    // we cannot test with target only here, as this is not a valid
    // scenario; for split projects we must supply the include and
    // source directories and for non-split we need project
    // directories. so we just chose one of the two.
    dogen::config::knitting_options_validator::validate(
        target_source_and_include());
}

BOOST_AUTO_TEST_CASE(options_for_non_split_projects_without_a_project_directory_throw) {
    SETUP_TEST_LOG_SOURCE("options_for_non_split_projects_without_a_project_directory_throw");

    auto o(split_project(false));
    contains_checker<validation_error> c(missing_project_dir);
    BOOST_CHECK_EXCEPTION(
        dogen::config::knitting_options_validator::validate(o),
        validation_error, c);
}

BOOST_AUTO_TEST_CASE(options_for_split_projects_with_a_project_directory_are_valid) {
    SETUP_TEST_LOG_SOURCE("options_for_split_projects_with_a_project_directory_are_valid");
    dogen::config::knitting_options_validator::validate(
        split_project(false, project_dir));
}

BOOST_AUTO_TEST_CASE(options_for_non_split_projects_with_include_or_source_directories_throw) {
    SETUP_TEST_LOG_SOURCE("options_for_non_split_projects_with_include_or_source_directories_throw");

    auto o(split_project(false, include_dir, src_dir));
    contains_checker<validation_error> c(unexpected_source_include);
    BOOST_CHECK_EXCEPTION(
        dogen::config::knitting_options_validator::validate(o),
        validation_error, c);

    o = split_project(false, include_dir, empty_dir);
    BOOST_CHECK_EXCEPTION(
        dogen::config::knitting_options_validator::validate(o),
        validation_error, c);

    o = split_project(false, empty_dir, src_dir);
    BOOST_CHECK_EXCEPTION(
        dogen::config::knitting_options_validator::validate(o),
        validation_error, c);
}

BOOST_AUTO_TEST_CASE(options_for_split_projects_without_source_or_include_directories_throw) {
    SETUP_TEST_LOG_SOURCE("options_for_split_projects_without_source_or_include_directories_throw");

    auto o(split_project(true));
    contains_checker<validation_error> c(missing_source_include);
    BOOST_CHECK_EXCEPTION(
        dogen::config::knitting_options_validator::validate(o),
        validation_error, c);

    o = split_project(true, include_dir, empty_dir);
    BOOST_CHECK_EXCEPTION(
        dogen::config::knitting_options_validator::validate(o),
        validation_error, c);

    o = split_project(true, empty_dir, src_dir);
    BOOST_CHECK_EXCEPTION(
        dogen::config::knitting_options_validator::validate(o),
        validation_error, c);

    dogen::config::knitting_options_validator::validate(
        split_project(true, include_dir, src_dir));
}

BOOST_AUTO_TEST_CASE(options_for_split_projects_with_source_and_include_directories_are_valid) {
    SETUP_TEST_LOG_SOURCE("options_for_split_projects_with_source_and_include_directories_are_valid");
    dogen::config::knitting_options_validator::validate(
        split_project(true, include_dir, src_dir));
}

BOOST_AUTO_TEST_CASE(options_for_split_projects_with_project_directory_throw) {
    SETUP_TEST_LOG_SOURCE("options_for_split_projects_with_project_directory_throw");

    const auto o(split_project(true, project_dir));
    contains_checker<validation_error> c(unexpected_project_dir);
    BOOST_CHECK_EXCEPTION(
        dogen::config::knitting_options_validator::validate(o),
        validation_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
