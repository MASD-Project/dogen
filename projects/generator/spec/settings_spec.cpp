/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/generator/config/settings.hpp"
#include "dogen/generator/config/validator.hpp"
#include "dogen/generator/config/configuration_error.hpp"
#include "dogen/generator/test/mock_settings_factory.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string empty;
const boost::filesystem::path empty_path;
const std::string test_module("generator");
const std::string test_suite("settings_spec");

const boost::filesystem::path target("some_target");
const boost::filesystem::path src_dir("src directory");
const boost::filesystem::path include_dir("include directory");
const std::string epp("package::path");

const std::string missing_target("Mandatory parameter target is missing");
const std::string missing_source_include("You must supply source and include");
const std::string missing_project_dir("You must supply the project directory");
const std::string unexpected_source_include("Source and include directories");
const std::string unexpected_project_dir("Project directories cannot be");

dogen::generator::config::settings default_mock_settings() {
    return dogen::generator::test::mock_settings_factory::
        build_settings(target, src_dir, include_dir, epp);
}

dogen::generator::config::settings target_only_settings() {
    return dogen::generator::test::mock_settings_factory::
        build_settings(target, empty_path, empty_path, empty);
}

dogen::generator::config::settings split_project_settings(const bool split) {
    auto s(target_only_settings());
    auto cpp(s.cpp());
    cpp.split_project(split);
    s.cpp(cpp);
    return s;
}

}

using dogen::utility::test::contains_checker;
using dogen::generator::config::configuration_error;
using dogen::generator::config::validator;

BOOST_AUTO_TEST_SUITE(settings)

BOOST_AUTO_TEST_CASE(default_mock_settings_are_valid) {
    SETUP_TEST_LOG_SOURCE("default_mock_settings_are_valid");
    using dogen::generator::config::validator;
    validator::validate(default_mock_settings());
}

BOOST_AUTO_TEST_CASE(not_defining_a_target_throws) {
    SETUP_TEST_LOG_SOURCE("not_defining_a_target_throws");

    dogen::generator::config::settings s;
    BOOST_CHECK(s.modeling().target().empty());

    contains_checker<configuration_error> c(missing_target);
    BOOST_CHECK_EXCEPTION(validator::validate(s), configuration_error, c);
}

BOOST_AUTO_TEST_CASE(non_split_projects_without_project_directory_throw) {
    SETUP_TEST_LOG_SOURCE("non_split_projects_without_project_directory_throw");

    const auto s(split_project_settings(false));
    contains_checker<configuration_error> c(missing_project_dir);
    BOOST_CHECK_EXCEPTION(validator::validate(s), configuration_error, c);
}

BOOST_AUTO_TEST_CASE(non_split_projects_with_include_or_source_throw) {
    SETUP_TEST_LOG_SOURCE("non_split_projects_with_include_or_source_throw");

    const auto s(split_project_settings(false));
    contains_checker<configuration_error> c(missing_project_dir);
    BOOST_CHECK_EXCEPTION(validator::validate(s), configuration_error, c);
}

BOOST_AUTO_TEST_CASE(split_project_requires_source_and_include_directories) {
    SETUP_TEST_LOG_SOURCE("split_project_requires_source_and_include_directories");

    const auto s(split_project_settings(true));
    contains_checker<configuration_error> c(missing_source_include);
    BOOST_CHECK_EXCEPTION(validator::validate(s), configuration_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
