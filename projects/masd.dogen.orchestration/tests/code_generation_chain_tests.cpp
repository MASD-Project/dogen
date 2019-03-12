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

/*
 * Comment these out as required if testing only one frontend. These
 * should all be enabled in git, do not check them in commented out by
 * mistake.
 */
#define ENABLE_DIA_TESTS
#define ENABLE_JSON_TESTS

namespace  {

const std::string test_module("masd.dogen.orchestration.tests");
const std::string test_suite("code_generation_chain_tests");

const std::string run_activity("code_generation");
const std::string transform_stats_org_fn("transform_stats.org");
const std::string transform_stats_text_fn("transform_stats.txt");
const std::string archetype_location_fn(
    "000-archetype_location_repository.json");
const std::string injection_transform_prefix(
    "001-injection.dia.decoding_transform-");
const std::string injection_transform_postfix("-input.json");
const std::regex guid_regex(
    "[a-f0-9]{8}-[a-f0-9]{4}-4[a-f0-9]{3}-[89aAbB][a-f0-9]{3}-[a-f0-9]{12}");
const std::regex tracing_regex(".*/tracing/.*");


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

/*
 * @brief Executres the code generation transforms against the
 * supplied target.
 *
 * Note: the output directory is recreated on initialisation so we
 * don't need to worry about its state.
 */
void execute_code_generation(const masd::dogen::configuration& cfg,
    const boost::filesystem::path& output_dir,
    const boost::filesystem::path& target) {


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

/**
 * @brief Generates the configuration and runs code generation.
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

#ifdef ENABLE_DIA_TESTS

BOOST_AUTO_TEST_CASE(masd_dogen_annotations_dia_produces_expected_code) {
    SETUP_TEST_LOG("masd_dogen_annotations_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_annotations_dia());
    const auto od(dogen_generation::output_directory());
    test_code_generation(t, od);
    BOOST_CHECK(are_generated_files_healthy(od, t));
}

BOOST_AUTO_TEST_CASE(enabling_detailed_tracing_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_detailed_tracing_results_in_expected_trace_files");
    /*
     * First, we setup the factory to enable tracing and _nothing_
     * else. Note that we don't worry about logging because by default
     * logs go into a testing specific logs directory.
     */
    using masd::dogen::mock_configuration_factory;
    const mock_configuration_factory f(true/*enable_tracing*/,
        false/*enable_reporting*/, false/*enable_diffing*/);

    /*
     * Setup the target and get the config. Note that we target a
     * small model as we don't particularly care about the code
     * generation itself.
     */
    const std::string identifier(".detailed_tracing");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_dia());
    auto cfg(f.make(t, run_activity + identifier));

    /*
     * Recreate the byproducts directory to ensure we start with a
     * clean slate. Note that the byproduct directory has a run id and
     * we add an additional postfix here so we should not affect
     * anyone else.
     */
    if (boost::filesystem::exists(cfg.byproduct_directory()))
        boost::filesystem::remove_all(cfg.byproduct_directory());

    /*
     * Now we costumise the configuration to make sure it meets the
     * need of the first assertions: logging at detailed level with
     * guids generates the exptected files.
     */
    using masd::dogen::tracing_level;
    cfg.tracing()->level(tracing_level::detail);

    using masd::dogen::tracing_format;
    cfg.tracing()->format(tracing_format::org_mode);

    cfg.tracing()->guids_enabled(true);

    /*
     * Run the transforms.
     */
    const auto od(dogen_generation::output_directory() / "detailed_tracing");
    execute_code_generation(cfg, od, t);

    /*
     * Ensure enabling tracing does not break the code generator.
     */
    BOOST_CHECK(are_generated_files_healthy(od, t, 50/*minimum_number*/));

    /*
     * Ensure we have created a byproducts directory.
     */
    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    /*
     * Ensure we have created the minimum number of expected files.
     */
    using masd::dogen::utility::filesystem::find_files;
    const boost::uintmax_t minimum_number(100);
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() > minimum_number);

    /*
     * Ensure all files have the minimum content size and find a
     * couple of expected files.
     */
    bool found_transform_stats(false);
    bool found_archetype_location(false);
    bool found_injection_dia_transform(false);

    for (const auto& f : files) {
        /*
         * Ensure files have a minimum size.
         */
        const boost::uintmax_t minimum_size(50);
        const auto s(boost::filesystem::file_size(f));
        BOOST_CHECK(s > minimum_size);

        /*
         * We only expect files inside the tracing directory.
         */
        BOOST_REQUIRE(std::regex_match(f.generic_string(), tracing_regex));

        /*
         * Look for a small number of "anchor" files to make sure
         * we're not looking at some other spurious content.
         */
        const auto fn(f.filename().string());
        if (fn == transform_stats_org_fn)
            found_transform_stats = true;
        else if (fn == archetype_location_fn)
            found_archetype_location = true;
        else if (boost::starts_with(fn, injection_transform_prefix) &&
            boost::ends_with(fn, injection_transform_postfix)) {
            found_injection_dia_transform = true;

            /*
             * Ensure filenames have a guid (since we requested it in
             * the config) and the guid is valid.
             */
            auto guid(fn);
            boost::erase_first(guid, injection_transform_prefix);
            boost::erase_first(guid, injection_transform_postfix);
            BOOST_REQUIRE(!guid.empty());
            BOOST_REQUIRE(std::regex_match(guid, guid_regex));
        }
    }
    BOOST_CHECK(found_transform_stats);
    BOOST_CHECK(found_archetype_location);
    BOOST_CHECK(found_injection_dia_transform);
}

BOOST_AUTO_TEST_CASE(enabling_summary_tracing_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_summary_tracing_results_in_expected_trace_files");

    using masd::dogen::mock_configuration_factory;
    const mock_configuration_factory fac(true/*enable_tracing*/,
        false/*enable_reporting*/, false/*enable_diffing*/);

    const std::string identifier(".summary_tracing");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_dia());
    auto cfg(fac.make(t, run_activity + identifier));

    if (boost::filesystem::exists(cfg.byproduct_directory()))
        boost::filesystem::remove_all(cfg.byproduct_directory());

    using masd::dogen::tracing_level;
    cfg.tracing()->level(tracing_level::summary);

    using masd::dogen::tracing_format;
    cfg.tracing()->format(tracing_format::plain);

    const auto od(dogen_generation::output_directory() / "summary_tracing");
    execute_code_generation(cfg, od, t);

    BOOST_CHECK(are_generated_files_healthy(od, t, 50/*minimum_number*/));

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using masd::dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 1);

    const auto f(*files.begin());
    const auto fn(f.filename().string());
    BOOST_REQUIRE(fn == transform_stats_text_fn);
}

#endif // ENABLE_DIA_TESTS

#ifdef ENABLE_JSON_TESTS

BOOST_AUTO_TEST_CASE(masd_dogen_coding_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_coding_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const auto t(dogen_generation::input_masd_dogen_coding_json());
    const auto od(dogen_generation::output_directory());
    test_code_generation(t, od);
    BOOST_CHECK(are_generated_files_healthy(od, t));
}

#endif // ENABLE_JSON_TESTS

BOOST_AUTO_TEST_SUITE_END()
