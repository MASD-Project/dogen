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
#include "masd.dogen.orchestration/types/transforms/extraction_model_production_chain.hpp"

namespace  {

const std::string test_module("masd.dogen.orchestration.tests");
const std::string test_suite("byproduct_generation_tests");

const std::string run_activity("byproduct_generation");
const std::string transform_stats_org_fn("transform_stats.org");
const std::string transform_stats_text_fn("transform_stats.txt");
const std::string transform_stats_graphviz_fn("transform_stats.dot");
const std::string archetype_location_prefix(
    "000-archetype_location_repository-");
const std::string type_repository_prefix(
    "001-type_repository-");
const std::string archetype_location_postfix(
    "-initial_input.json");
const std::string type_repository_postfix(
    "-initial_input.json");
const std::string injection_transform_prefix(
    "001-injection.dia.decoding_transform-");
const std::string first_short_name("000-initial_input.json");
const std::string second_short_name("001-initial_input.json");
const std::string third_short_name("004-input.json");
const std::string injection_transform_postfix("-input.json");
const std::regex tracing_regex(".*/tracing/.*");
const std::regex guid_regex(
    "[a-f0-9]{8}-[a-f0-9]{4}-4[a-f0-9]{3}-[89aAbB][a-f0-9]{3}-[a-f0-9]{12}");
const std::string diff_fn("dogen.patch");
const std::string report_org_mode_fn("dogen_report.org");
const std::string report_plain_fn("dogen_report.txt");

using boost::filesystem::path;
using masd::dogen::configuration;
using masd::dogen::tracing_level;
using masd::dogen::tracing_format;
using masd::dogen::reporting_style;
using masd::dogen::mock_configuration_factory;
using masd::dogen::utility::test_data::dogen_generation;

/*
 * @brief Recreate the byproducts directory to ensure we start with a
 * clean slate.
 *
 * Note that the byproduct directory has a run id and we add an
 * additional postfix here so we should not affect anyone else.
 */
void remove_byproducts_directory(const configuration& cfg) {
    using namespace boost::filesystem;
    if (exists(cfg.byproduct_directory()))
        remove_all(cfg.byproduct_directory());
}

/**
 * @brief Sets up the configuration for testing tracing.
 *
 * @note we disable all other byproduct output.
 */
configuration setup_tracing_configuration(const path& target,
    const std::string& additional_identifier, const tracing_level tl,
    const tracing_format tf, const bool enable_guids = false,
    const bool use_short_names = false) {

    const mock_configuration_factory f(true/*enable_tracing*/,
        false/*enable_reporting*/, false/*enable_diffing*/);

    auto r(f.make(target, run_activity + "." + additional_identifier));
    r.tracing()->level(tl);
    r.tracing()->format(tf);
    r.tracing()->guids_enabled(enable_guids);
    r.tracing()->use_short_names(use_short_names);

    return r;
}

/**
 * @brief Sets up the configuration for testing diffing.
 *
 * @note we disable all other byproduct output.
 */
configuration setup_diffing_configuration(const path& target,
    const std::string& additional_identifier) {
    const mock_configuration_factory f(false/*enable_tracing*/,
        false/*enable_reporting*/, true/*enable_diffing*/);

    auto r(f.make(target, run_activity + "." + additional_identifier));
    using masd::dogen::diffing_destination;
    r.diffing()->destination(diffing_destination::file);

    return r;
}

/**
 * @brief Sets up the configuration for testing reporting.
 *
 * @note we disable all other byproduct output.
 */
configuration setup_reporting_configuration(const path& target,
    const std::string& additional_identifier,
    const reporting_style rs) {
    const mock_configuration_factory f(false/*enable_tracing*/,
        true/*enable_reporting*/, false/*enable_diffing*/);

    auto r(f.make(target, run_activity + "." + additional_identifier));
    r.reporting()->style(rs);
    return r;
}

/**
 * @brief Applies the transform chains.
 */
void apply_transforms(const configuration& cfg, const path& output_dir,
    const path& target) {

    using namespace masd::dogen::orchestration::transforms;
    scoped_context_manager sco(cfg, output_dir);
    const auto ctx(sco.context());

    /*
     * Produce the extraction model.
     */
    const auto m(extraction_model_production_chain::apply(ctx, target));
}

bool are_tracing_files_healthy(const configuration& cfg,
    masd::dogen::utility::log::logger lg) {
    /*
     * Ensure we have created a byproducts directory.
     */
    using namespace boost::filesystem;
    if (!exists(cfg.byproduct_directory()))
        return false;

    using namespace masd::dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "Directory exists.";

    /*
     * Ensure we have created the minimum number of expected files.
     */
    using masd::dogen::utility::filesystem::find_files;
    const boost::uintmax_t minimum_number(100);
    const auto files(find_files(cfg.byproduct_directory()));
    if (files.size() < minimum_number)
        return false;

    BOOST_LOG_SEV(lg, debug) << "Files." << files.size();

    /*
     * Ensure all files have the minimum content size and find a
     * couple of expected files.
     */
    bool found_transform_stats(false);
    bool found_archetype_location(false);
    bool found_type_repository(false);
    bool found_injection_dia_transform(false);
    for (const auto& f : files) {
        /*
         * Ensure files have a minimum size.
         */
        const boost::uintmax_t minimum_size(50);
        const auto sz(file_size(f));
        BOOST_LOG_SEV(lg, debug) << "Size." << sz;

        if (sz < minimum_size)
            return false;

        /*
         * We only expect files inside the tracing directory.
         */
        const auto gs(f.generic_string());
        BOOST_LOG_SEV(lg, debug) << "gs: " << gs;

        if (!std::regex_match(gs, tracing_regex))
            return false;

        /*
         * Look for a small number of "anchor" files to make sure
         * we're not looking at some other spurious content.
         */
        const auto fn(f.filename().string());
        if (cfg.tracing()->use_short_names()) {
            if (fn == transform_stats_org_fn)
                found_transform_stats = true;
            else if (fn == first_short_name)
                found_archetype_location = true;
            else if (fn == second_short_name)
                found_type_repository = true;
            else if (fn == third_short_name)
                found_injection_dia_transform = true;
        } else {
            if (fn == transform_stats_org_fn)
                found_transform_stats = true;
            else if (boost::starts_with(fn, archetype_location_prefix) &&
                boost::ends_with(fn, archetype_location_postfix)) {
                found_archetype_location = true;
                BOOST_LOG_SEV(lg, debug) << "Found archetype location: " << gs;
            } else if (boost::starts_with(fn, type_repository_prefix) &&
                boost::ends_with(fn, type_repository_postfix)) {
                found_type_repository = true;
                BOOST_LOG_SEV(lg, debug) << "Found type repository: " << gs;
            } else if (boost::starts_with(fn, injection_transform_prefix) &&
                boost::ends_with(fn, injection_transform_postfix)) {
                found_injection_dia_transform = true;
                BOOST_LOG_SEV(lg, debug) << "Found injection: " << gs;

                /*
                 * Ensure filenames have a guid (since we requested it in
                 * the config) and the guid is valid.
                 */
                auto guid(fn);
                boost::erase_first(guid, injection_transform_prefix);
                boost::erase_first(guid, injection_transform_postfix);
                BOOST_LOG_SEV(lg, debug) << "guid:" << guid;

                if (guid.size() != 36)
                    return false;

                BOOST_LOG_SEV(lg, debug) << "before regex match.";
                if (!std::regex_match(guid, guid_regex))
                    return false;

                BOOST_LOG_SEV(lg, debug) << "after regex match.";
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "found_transform_stats: "
                             << found_transform_stats
                             << " found_archetype_location: "
                             << found_archetype_location
                             << " found_type_repository: "
                             << found_type_repository
                             << " found_injection_dia_transform: "
                             << found_injection_dia_transform;

    return
        found_transform_stats && found_archetype_location &&
        found_type_repository && found_injection_dia_transform;
}

}

BOOST_AUTO_TEST_SUITE(byproduct_generation_tests)

/*
 * This test fails on windows. This is because we are generating paths
 * that are too large for windows. We tried moving it to TEMP but even
 * then the test still fails. The test is set to ignore in two places:
 *
 * - here, via macros. This means you cannot run the test on windows
 *   from the binary. It stops users from complaining the tests are
 *   broken.
 * - from the CMakeLists that adds boost tests. It stops the build
 *   machine from trying to run the test and then failing because the
 *   test is not on the windows binary.
 */
#ifndef _WIN32
BOOST_AUTO_TEST_CASE(enabling_detailed_tracing_with_org_mode_results_in_expected_trace_files) {
    SETUP_TEST_LOG_SOURCE("enabling_detailed_tracing_with_org_mode_results_in_expected_trace_files");

    const auto t(dogen_generation::input_masd_dogen_dia());
    const std::string id("detailed_tracing_org_mode");
    const auto tl(tracing_level::detail);
    const auto tf(tracing_format::org_mode);
    const bool eg(true/*enable_guids*/);
    const auto cfg(setup_tracing_configuration(t, id, tl, tf, eg));
    remove_byproducts_directory(cfg);

    const auto od(dogen_generation::output_directory() / id);
    apply_transforms(cfg, od, t);

    BOOST_CHECK(are_tracing_files_healthy(cfg, lg));
}
#endif

BOOST_AUTO_TEST_CASE(enabling_summary_tracing_with_plain_text_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_summary_tracing_with_plain_text_results_in_expected_trace_files");

    const auto t(dogen_generation::input_masd_dogen_dia());
    const std::string id("summary_tracing_plain");
    const auto tl(tracing_level::summary);
    const auto tf(tracing_format::plain);
    const auto cfg(setup_tracing_configuration(t, id, tl, tf));
    remove_byproducts_directory(cfg);

    const auto od(dogen_generation::output_directory() / id);
    apply_transforms(cfg, od, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using masd::dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 1);

    const auto f(*files.begin());
    const auto fn(f.filename().string());
    BOOST_REQUIRE(fn == transform_stats_text_fn);
}

BOOST_AUTO_TEST_CASE(enabling_summary_tracing_with_graphviz_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_summary_tracing_with_graphviz_results_in_expected_trace_files");

    const auto t(dogen_generation::input_masd_dogen_dia());
    const std::string id("summary_tracing_graphviz");
    const auto tl(tracing_level::summary);
    const auto tf(tracing_format::graphviz);
    const auto cfg(setup_tracing_configuration(t, id, tl, tf));
    remove_byproducts_directory(cfg);

    const auto od(dogen_generation::output_directory() / id);
    apply_transforms(cfg, od, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using masd::dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 1);

    const auto f(*files.begin());
    const auto fn(f.filename().string());
    BOOST_REQUIRE(fn == transform_stats_graphviz_fn);
}

BOOST_AUTO_TEST_CASE(enabling_detailed_tracing_with_short_names_results_in_expected_trace_files) {
    SETUP_TEST_LOG_SOURCE("enabling_detailed_tracing_with_short_names_results_in_expected_trace_files");

    const auto t(dogen_generation::input_masd_dogen_dia());
    const std::string id("detail_tracing_short_names");
    const auto tl(tracing_level::detail);
    const auto tf(tracing_format::org_mode);
    const bool eg(false/*enable_guids*/);
    const bool usn(true/*use_short_names*/);
    const auto cfg(setup_tracing_configuration(t, id, tl, tf, eg, usn));
    remove_byproducts_directory(cfg);

    const auto od(dogen_generation::output_directory() / id);
    apply_transforms(cfg, od, t);

    BOOST_CHECK(are_tracing_files_healthy(cfg, lg));
}

BOOST_AUTO_TEST_CASE(enabling_diffing_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_diffing_results_in_expected_trace_files");

    const auto t(dogen_generation::input_masd_dogen_dia());
    const std::string id("diffing");
    const auto cfg(setup_diffing_configuration(t, id));

    const auto od(dogen_generation::output_directory() / id);
    apply_transforms(cfg, od, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using masd::dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 1);

    const auto f(*files.begin());
    const auto fn(f.filename().string());
    BOOST_REQUIRE(fn == diff_fn);
}

BOOST_AUTO_TEST_CASE(enabling_reporting_org_mode_style_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_reporting_org_mode_style_results_in_expected_trace_files");

    const auto t(dogen_generation::input_masd_dogen_dia());
    const std::string id("reporting_org_mode");
    const auto rs(reporting_style::org_mode);
    const auto cfg(setup_reporting_configuration(t, id, rs));

    const auto od(dogen_generation::output_directory() / id);
    apply_transforms(cfg, od, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using masd::dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 1);

    const auto f(*files.begin());
    const auto fn(f.filename().string());
    BOOST_REQUIRE(fn == report_org_mode_fn);
}

BOOST_AUTO_TEST_CASE(enabling_reporting_plain_style_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_reporting_plain_style_results_in_expected_trace_files");

    const auto t(dogen_generation::input_masd_dogen_dia());
    const std::string id("reporting_plain");
    const auto rs(reporting_style::plain);
    const auto cfg(setup_reporting_configuration(t, id, rs));

    const auto od(dogen_generation::output_directory() / id);
    apply_transforms(cfg, od, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using masd::dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 1);

    const auto f(*files.begin());
    const auto fn(f.filename().string());
    BOOST_REQUIRE(fn == report_plain_fn);
}

BOOST_AUTO_TEST_SUITE_END()
