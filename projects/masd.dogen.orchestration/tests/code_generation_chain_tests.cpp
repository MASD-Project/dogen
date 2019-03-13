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
#include <regex>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "masd.dogen/types/mock_configuration_factory.hpp"
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.utility/types/test_data/dogen_generation.hpp"
#include "masd.dogen.extraction/io/meta_model/operation_io.hpp"
#include "masd.dogen.orchestration/types/transforms/scoped_context_manager.hpp"
#include "masd.dogen.orchestration/types/transforms/code_generation_chain.hpp"

namespace  {

const std::string test_module("masd.dogen.orchestration.tests");
const std::string test_suite("code_generation_chain_tests");

const std::string run_activity("code_generation");


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
 * @brief Performs a number of basic sanity checks on generated files.
 */
bool are_generated_files_healthy(const boost::filesystem::path& output_dir,
    const boost::filesystem::path& target,
    const boost::uintmax_t minimum_number = 100) {

    /*
     * Ensure we have created a model directory.
     */
    auto n(target.filename().stem());
    const auto dir(output_dir / n);
    if (!boost::filesystem::exists(dir))
        return false;

    /*
     * Ensure we have created the minimum number of expected files.
     */
    using masd::dogen::utility::filesystem::find_files;
    const auto files(find_files(dir));
    if (files.size() < minimum_number)
        return false;

    /*
     * Ensure all files have the minimum content size.
     */
    const boost::uintmax_t minimum_file_size(1000);
    for (const auto& f : files) {
        const auto sz(boost::filesystem::file_size(f));
        if (sz < minimum_file_size)
            return false;
    }
    return true;
}

/**
 * @brief Generates the configuration and runs code generation.
 *
 * @note the output directory is recreated on initialisation so we
 * don't need to worry about its state.
 */
void test_code_generation(const boost::filesystem::path& target,
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
     * Execute the code generation transform.
     */
    using namespace masd::dogen::extraction::transforms;
    code_generation_chain::apply(ctx, target);
}

}

BOOST_AUTO_TEST_SUITE(code_generation_chain_tests)

BOOST_AUTO_TEST_CASE(masd_dogen_annotations_dia_produces_expected_code) {
    SETUP_TEST_LOG("masd_dogen_annotations_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_annotations_dia());
    const auto od(dogen_generation::output_directory());
    test_code_generation(t, od);
    BOOST_CHECK(are_generated_files_healthy(od, t));
}

BOOST_AUTO_TEST_CASE(masd_dogen_coding_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_coding_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_coding_json());
    const auto od(dogen_generation::output_directory());
    test_code_generation(t, od);
    BOOST_CHECK(are_generated_files_healthy(od, t));
}

BOOST_AUTO_TEST_SUITE_END()
