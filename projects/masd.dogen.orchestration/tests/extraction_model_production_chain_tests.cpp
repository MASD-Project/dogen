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
#include <boost/filesystem/operations.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include "masd.dogen/types/mock_configuration_factory.hpp"
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/test_data/dogen_generation.hpp"
#include "masd.dogen.utility/types/test_data/cpp_ref_impl_generation.hpp"
#include "masd.dogen.utility/types/test_data/csharp_ref_impl_generation.hpp"
#include "masd.dogen.extraction/io/meta_model/operation_io.hpp"
#include "masd.dogen.extraction/io/meta_model/operation_reason_io.hpp"
#include "masd.dogen.orchestration/types/transforms/scoped_context_manager.hpp"
#include "masd.dogen.orchestration/types/transforms/extraction_model_production_chain.hpp"

namespace  {

const std::string test_module("masd.dogen.orchestration.tests");
const std::string test_suite("extraction_model_production_chain_tests");

const std::string run_activity("extraction_production");

/*
 * Set these flag to true if you want to dump information for all
 * tests. It should normally be set to false, unless we are diagnosing
 * some kind of problem. Don't check it in as true as it slows down
 * the tests for no good reason.
 */
const bool enable_tracing_globally(false);
const bool enable_reporting_globally(false);
const bool enable_diffing_globally(false);

/**
 * @brief Prints a limited number of lines from content. Used to
 * ensure we don't spam the build logs.
 */
void print_lines(const std::string& content, const unsigned int total,
    std::ostream& os) {

    unsigned int i(0);
    std::string line;
    std::istringstream is(content);
    while (std::getline(is, line) && (i < total)) {
        os << line << std::endl;
        ++i;
    }
}

/**
 * @brief Checks to see if the model contains any artefacts which are
 * different from the files in the filesystem.
 *
 * @note We're using std::cout here by design as we always want the
 * output to show up in CDash.
 */
bool check_for_differences(const boost::filesystem::path& output_dir,
    const masd::dogen::extraction::meta_model::model& m) {

    unsigned int diffs_found(0);
    for (const auto& a : m.artefacts()) {
        using namespace masd::dogen::extraction::meta_model;
        /*
         * FIXME: we seem to be generating empty paths. Needs to be
         * investigated. Hack for now
         */
        if (a.path().empty())
            continue;

        /*
         * We can safely ignore all files the user provided regexes
         * for.
         */
        if (a.operation().type() == operation_type::ignore &&
            a.operation().reason() == operation_reason::ignore_regex)
            continue;

        if (a.operation().type() != operation_type::write &&
            a.operation().type() != operation_type::remove)
            continue;

        if (diffs_found == 0) {
            std::cout << "Differences found. Outputting first five."
                      << std::endl;
        }

        ++diffs_found;
        if (diffs_found > 5)
            break;

        const auto rel(a.path().lexically_relative(output_dir));
        if (a.operation().type() == operation_type::remove)
            std::cout << "Unexpected file (remove): " << rel << std::endl;
        else if (a.operation().type() == operation_type::write) {
            if (a.operation().reason() == operation_reason::newly_generated)
                std::cout << "New file: " << rel << std::endl;
            else
                print_lines(a.unified_diff(), 20, std::cout);
        } else if (a.operation().type() == operation_type::ignore) {
            if (a.operation().reason() == operation_reason::ignore_unexpected)
                std::cout << "Unexpected file (ignore): " << rel << std::endl;
            else {
                std::cout << "Unexpected file, unexpected reason: "
                          << a.operation().reason() << ". File: "
                          << rel << std::endl;
            }
        } else {
            std::cout << "Unexpected operation: " << a.operation()
                      << " File: " << rel << std::endl;
        }
    }
    return diffs_found == 0;
}

bool test_extraction_model_production(const boost::filesystem::path& target,
    const boost::filesystem::path& output_dir,
    const bool enable_tracing_locally = false,
    const bool enable_reporting_locally = false,
    const bool enable_diffing_locally = false) {

    /*
     * Create the configuration.
     */
    const bool et(enable_tracing_globally || enable_tracing_locally);
    const bool er(enable_reporting_globally || enable_reporting_locally);
    const bool ed(enable_diffing_globally || enable_diffing_locally);
    using masd::dogen::mock_configuration_factory;
    mock_configuration_factory f(et, er, ed);
    const auto cfg(f.make(target, run_activity));

    /*
     * Create the context.
     */
    using namespace masd::dogen::orchestration::transforms;
    scoped_context_manager sco(cfg, output_dir);
    const auto ctx(sco.context());

    /*
     * Produce the extraction model.
     */
    const auto m(extraction_model_production_chain::apply(ctx, target));

    /*
     * Locate any differences.
     */
    return check_for_differences(output_dir, m);
}

}

BOOST_AUTO_TEST_SUITE(extraction_model_production_chain_tests)

BOOST_AUTO_TEST_CASE(masd_dogen_annotations_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_annotations_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_annotations_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_cli_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_cli_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_cli_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_coding_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_coding_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_coding_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_dia_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_dia_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_dia_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_extraction_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_extraction_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_extraction_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_cpp_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_cpp_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_generation_cpp_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_csharp_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_csharp_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_generation_csharp_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_generation_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_injection_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_dia_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_injection_dia_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_injection_dia_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_json_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_injection_json_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_injection_json_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_orchestration_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_orchestration_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_orchestration_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_templating_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_templating_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_templating_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_tracing_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_tracing_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_tracing_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_utility_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_utility_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_utility_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

#ifdef ENABLE_CPP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_boost_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_boost_model_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_boost_model_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_compressed_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_compressed_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_compressed_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_cpp_98_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_cpp_98_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_cpp_98_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_cpp_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_cpp_model_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_cpp_model_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_directory_settings_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_directory_settings_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_directory_settings_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_disable_cmakelists_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_disable_cmakelists_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_disable_cmakelists_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_disable_facet_folders_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_disable_facet_folders_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_disable_facet_folders_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_enable_facet_hash_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_enable_facet_hash_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_enable_facet_hash_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_enable_facet_io_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_enable_facet_io_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_enable_facet_io_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_enable_facet_serialization_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_enable_facet_serialization_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_enable_facet_serialization_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_enable_facet_types_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_enable_facet_types_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_enable_facet_types_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_flat_directory_mode_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_flat_directory_mode_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_flat_directory_mode_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_lam_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_lam_model_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_lam_model_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_northwind_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_northwind_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_northwind_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_split_project_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_split_project_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_split_project_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_std_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_std_model_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_std_model_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_two_layers_with_objects_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_two_layers_with_objects_dia_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_two_layers_with_objects_dia());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

#endif // ENABLE_CPP_REF_IMPL_TESTS

#ifdef ENABLE_CSHARP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(masd_csharprefimpl_csharpmodel_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_csharprefimpl_csharpmodel_dia_produces_expected_model");
    using masd::dogen::utility::test_data::csharp_ref_impl_generation;
    const auto t(csharp_ref_impl_generation::input_masd_csharprefimpl_csharpmodel_dia());
    const auto od(csharp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_csharprefimpl_directorysettings_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_csharprefimpl_directorysettings_dia_produces_expected_model");
    using masd::dogen::utility::test_data::csharp_ref_impl_generation;
    const auto t(csharp_ref_impl_generation::input_masd_csharprefimpl_directorysettings_dia());
    const auto od(csharp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_csharprefimpl_lammodel_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_csharprefimpl_lammodel_dia_produces_expected_model");
    using masd::dogen::utility::test_data::csharp_ref_impl_generation;
    const auto t(csharp_ref_impl_generation::input_masd_csharprefimpl_lammodel_dia());
    const auto od(csharp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

#endif // ENABLE_CSHARP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(masd_dogen_annotations_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_annotations_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_annotations_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_cli_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_cli_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_cli_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_coding_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_coding_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_coding_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_dia_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_dia_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_dia_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_extraction_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_extraction_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_extraction_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_cpp_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_cpp_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_generation_cpp_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_csharp_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_csharp_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_generation_csharp_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_generation_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_injection_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_dia_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_injection_dia_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_injection_dia_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_json_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_injection_json_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_injection_json_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_orchestration_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_orchestration_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_orchestration_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_templating_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_templating_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_templating_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_tracing_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_tracing_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_tracing_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_dogen_utility_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_utility_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_utility_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

#ifdef ENABLE_CPP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_boost_model_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_boost_model_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_boost_model_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_compressed_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_compressed_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_compressed_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_cpp_98_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_cpp_98_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_cpp_98_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_cpp_model_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_cpp_model_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_cpp_model_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_directory_settings_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_directory_settings_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_directory_settings_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_disable_cmakelists_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_disable_cmakelists_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_disable_cmakelists_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_disable_facet_folders_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_disable_facet_folders_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_disable_facet_folders_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_enable_facet_hash_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_enable_facet_hash_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_enable_facet_hash_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_enable_facet_io_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_enable_facet_io_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_enable_facet_io_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_enable_facet_serialization_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_enable_facet_serialization_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_enable_facet_serialization_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_enable_facet_types_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_enable_facet_types_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_enable_facet_types_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_flat_directory_mode_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_flat_directory_mode_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_flat_directory_mode_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_lam_model_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_lam_model_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_lam_model_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_northwind_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_northwind_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_northwind_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_split_project_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_split_project_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_split_project_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_std_model_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_std_model_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_std_model_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_cpp_ref_impl_two_layers_with_objects_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_cpp_ref_impl_two_layers_with_objects_json_produces_expected_model");
    using masd::dogen::utility::test_data::cpp_ref_impl_generation;
    const auto t(cpp_ref_impl_generation::input_masd_cpp_ref_impl_two_layers_with_objects_json());
    const auto od(cpp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

#endif // ENABLE_CPP_REF_IMPL_TESTS

#ifdef ENABLE_CSHARP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(masd_csharprefimpl_csharpmodel_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_csharprefimpl_csharpmodel_json_produces_expected_model");
    using masd::dogen::utility::test_data::csharp_ref_impl_generation;
    const auto t(csharp_ref_impl_generation::input_masd_csharprefimpl_csharpmodel_json());
    const auto od(csharp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_csharprefimpl_directorysettings_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_csharprefimpl_directorysettings_json_produces_expected_model");
    using masd::dogen::utility::test_data::csharp_ref_impl_generation;
    const auto t(csharp_ref_impl_generation::input_masd_csharprefimpl_directorysettings_json());
    const auto od(csharp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

BOOST_AUTO_TEST_CASE(masd_csharprefimpl_lammodel_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_csharprefimpl_lammodel_json_produces_expected_model");
    using masd::dogen::utility::test_data::csharp_ref_impl_generation;
    const auto t(csharp_ref_impl_generation::input_masd_csharprefimpl_lammodel_json());
    const auto od(csharp_ref_impl_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od));
}

#endif // ENABLE_CSHARP_REF_IMPL_TESTS

BOOST_AUTO_TEST_SUITE_END()
