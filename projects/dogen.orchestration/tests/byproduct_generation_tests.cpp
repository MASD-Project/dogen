#include <regex>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/types/mock_configuration_factory.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/test_data/dogen_product.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/operation_io.hpp"
#include "dogen.orchestration/types/transforms/context_bootstrapping_chain.hpp"
#include "dogen.orchestration/types/transforms/physical_model_production_chain.hpp"
#include "dogen/types/tracing_backend.hpp"

namespace  {

const std::string test_module("dogen.orchestration.tests");
const std::string test_suite("byproduct_generation_tests");

const std::string run_activity("byproduct_generation");
const std::string transform_stats_org_fn("transform_stats.org");
const std::string transform_stats_text_fn("transform_stats.txt");
const std::string transform_stats_graphviz_fn("transform_stats.dot");
const std::string references_graph_org_fn("references_graph.org");
const std::string references_graph_text_fn("references_graph.txt");
const std::string references_graph_graphviz_fn("references_graph.dot");
const std::string physical_name_prefix("00000-configuration-");
const std::string physical_name_postfix("-initial_input.json");
const std::string codec_transform_prefix(
    "00000-codec.transforms.org_artefact_to_model_transform-dogen-");
const std::string first_short_name("00000-initial_input.json");
const std::string second_short_name("00001-input.json");
const std::string codec_transform_postfix("-input.json");
const std::regex tracing_regex(".*/tracing/.*");
const std::regex guid_regex(
    "[a-f0-9]{8}-[a-f0-9]{4}-4[a-f0-9]{3}-[89aAbB][a-f0-9]{3}-[a-f0-9]{12}");
const std::string diff_fn("dogen.patch");
const std::string report_org_mode_fn("dogen_report.org");
const std::string report_plain_fn("dogen_report.txt");

using boost::filesystem::path;
using dogen::configuration;
using dogen::tracing_level;
using dogen::tracing_format;
using dogen::tracing_backend;
using dogen::reporting_style;
using dogen::mock_configuration_factory;
using dogen::utility::test_data::dogen_product;

/*
 * @brief Recreate the byproducts directory to ensure we start with a
 * clean slate.
 *
 * Note that the byproduct directory has a run id and we add an
 * additional postfix here so we should not affect anyone else.
 */
void remove_byproducts_directory(const configuration& cfg) {
    using dogen::utility::filesystem::recreate_directory;
    recreate_directory(cfg.byproduct_directory());
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
    r.tracing()->backend(tracing_backend::file);

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
    using dogen::diffing_destination;
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
    const std::vector<boost::filesystem::path>& reference_directories,
    const path& target) {

    /*
     * Bootstrap the top-level context.
     */
    using namespace dogen::orchestration::transforms;
    using cbc = context_bootstrapping_chain;
    const auto& od(output_dir);
    const auto& a(run_activity);
    const auto& rds(reference_directories);
    const auto ctx(cbc::bootstrap(cfg, a, rds, od));

    /*
     * Bind the tracer to the current scope.
     */
    const auto& t(*ctx.codec_context().tracer());
    dogen::tracing::scoped_tracer st(t);

    /*
     * Produce the physical model.
     */
    const auto m(physical_model_production_chain::apply(ctx, target));
}

bool are_tracing_files_healthy(const configuration& cfg,
    dogen::utility::log::logger lg) {
    /*
     * Ensure we have created a byproducts directory.
     */
    using namespace boost::filesystem;
    using namespace dogen::utility::log;
    if (!exists(cfg.byproduct_directory())) {
        BOOST_LOG_SEV(lg, error) << "Could not find byproduct directory: "
                                 << cfg.byproduct_directory().generic_path();
        return false;
    }

    BOOST_LOG_SEV(lg, debug) << "Directory exists.";

    /*
     * Ensure we have created the minimum number of expected files.
     */
    using dogen::utility::filesystem::find_files;
    const boost::uintmax_t minimum_number(100);
    const auto files(find_files(cfg.byproduct_directory()));
    if (files.size() < minimum_number) {
        BOOST_LOG_SEV(lg, error) << "Found less files than expected. Found: "
                                 << files.size() << ". Minimum is: "
                                 << minimum_number;
        return false;
    }

    BOOST_LOG_SEV(lg, debug) << "Files: " << files.size();

    /*
     * Ensure all files have the minimum content size and find a
     * couple of expected files.
     */
    bool found_transform_stats(false);
    bool found_references_graph(false);
    bool found_physical_name(false);
    bool found_codec_dia_transform(false);
    for (const auto& f : files) {
        const auto gs(f.generic_string());
        BOOST_LOG_SEV(lg, debug) << "gs: " << gs;

        /*
         * Ensure files have a minimum size.
         */
        const boost::uintmax_t minimum_size(50);
        const auto sz(file_size(f));
        BOOST_LOG_SEV(lg, debug) << "Size: " << sz;

        if (sz < minimum_size) {
            BOOST_LOG_SEV(lg, error) << "File size is smaller than minimum."
                                     << " Size: " << sz << " Minimum expected: "
                                     << minimum_size;
            return false;
        }

        /*
         * We only expect files inside the tracing directory.
         */
        if (!std::regex_match(gs, tracing_regex)) {
            BOOST_LOG_SEV(lg, error) << "File is not in the tracing directory.";
            return false;
        }

        /*
         * Look for a small number of "anchor" files to make sure
         * we're not looking at some other spurious content.
         */
        const auto fn(f.filename().string());
        if (cfg.tracing()->use_short_names()) {
            if (fn == transform_stats_org_fn)
                found_transform_stats = true;
            else if (fn == references_graph_org_fn)
                found_references_graph = true;
            else if (fn == first_short_name)
                found_physical_name = true;
            else if (fn == second_short_name)
                found_codec_dia_transform = true;
        } else {
            if (fn == transform_stats_org_fn)
                found_transform_stats = true;
            else if (fn == references_graph_org_fn)
                found_references_graph = true;
            else if (boost::starts_with(fn, physical_name_prefix) &&
                boost::ends_with(fn, physical_name_postfix)) {
                found_physical_name = true;
                BOOST_LOG_SEV(lg, debug) << "Found archetype location: " << gs;
            } else if (boost::starts_with(fn, codec_transform_prefix) &&
                boost::ends_with(fn, codec_transform_postfix)) {
                found_codec_dia_transform = true;
                BOOST_LOG_SEV(lg, debug) << "Found codec: " << gs;

                /*
                 * Ensure filenames have a guid (since we requested it in
                 * the config) and the guid is valid.
                 */
                auto guid(fn);
                boost::erase_first(guid, codec_transform_prefix);
                boost::erase_first(guid, codec_transform_postfix);
                BOOST_LOG_SEV(lg, debug) << "guid: " << guid;

                if (guid.size() != 36) {
                    BOOST_LOG_SEV(lg, error) << "GUID is too small. Expected: "
                                             << 36 << " Size: " << guid.size();
                    return false;
                }

                BOOST_LOG_SEV(lg, debug) << "before regex match.";
                if (!std::regex_match(guid, guid_regex)) {
                    BOOST_LOG_SEV(lg, error) << "GUID does not match regex.";
                    return false;
                }

                BOOST_LOG_SEV(lg, debug) << "after regex match.";
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "found_transform_stats: "
                             << found_transform_stats
                             << " found_references_graph: "
                             << found_references_graph
                             << " found_physical_name: "
                             << found_physical_name
                             << " found_codec_dia_transform: "
                             << found_codec_dia_transform;

    return
        found_transform_stats && found_references_graph &&
        found_physical_name && found_codec_dia_transform;
}

}

/*
 * Test the generation of files within the byproducts directory.
 */
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

    const auto t(dogen_product::input_dogen_org());
    const std::string id("detailed_tracing_org_mode");
    const auto tl(tracing_level::detail);
    const auto tf(tracing_format::org_mode);
    const bool eg(true/*enable_guids*/);
    const auto cfg(setup_tracing_configuration(t, id, tl, tf, eg));
    remove_byproducts_directory(cfg);

    const auto od(dogen_product::output_directory() / id);
    const auto rds(dogen_product::reference_directories());
    apply_transforms(cfg, od, rds, t);

    BOOST_CHECK(are_tracing_files_healthy(cfg, lg));
}
#endif

BOOST_AUTO_TEST_CASE(enabling_summary_tracing_with_plain_text_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_summary_tracing_with_plain_text_results_in_expected_trace_files");

    const auto t(dogen_product::input_dogen_org());
    const std::string id("summary_tracing_plain");
    const auto tl(tracing_level::summary);
    const auto tf(tracing_format::plain);
    const auto cfg(setup_tracing_configuration(t, id, tl, tf));
    remove_byproducts_directory(cfg);

    const auto od(dogen_product::output_directory() / id);
    const auto rds(dogen_product::reference_directories());
    apply_transforms(cfg, od, rds, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 2);

    const auto f_beg(*files.begin());
    const auto fn_beg(f_beg.filename().string());
    BOOST_REQUIRE(fn_beg == transform_stats_text_fn ||
        fn_beg == references_graph_text_fn);

    const auto f_end(*files.rbegin());
    const auto fn_end(f_end.filename().string());
    BOOST_REQUIRE(fn_end == transform_stats_text_fn ||
        fn_end == references_graph_text_fn);
}

BOOST_AUTO_TEST_CASE(enabling_summary_tracing_with_graphviz_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_summary_tracing_with_graphviz_results_in_expected_trace_files");

    const auto t(dogen_product::input_dogen_org());
    const std::string id("summary_tracing_graphviz");
    const auto tl(tracing_level::summary);
    const auto tf(tracing_format::graphviz);
    const auto cfg(setup_tracing_configuration(t, id, tl, tf));
    remove_byproducts_directory(cfg);

    const auto od(dogen_product::output_directory() / id);
    const auto rds(dogen_product::reference_directories());
    apply_transforms(cfg, od, rds, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 2);

    const auto f_beg(*files.begin());
    const auto fn_beg(f_beg.filename().string());
    BOOST_REQUIRE(fn_beg == transform_stats_graphviz_fn ||
        fn_beg == references_graph_graphviz_fn);

    const auto f_end(*files.rbegin());
    const auto fn_end(f_end.filename().string());
    BOOST_REQUIRE(fn_end == transform_stats_graphviz_fn ||
        fn_end == references_graph_graphviz_fn);
}

BOOST_AUTO_TEST_CASE(enabling_detailed_tracing_with_short_names_results_in_expected_trace_files) {
    SETUP_TEST_LOG_SOURCE("enabling_detailed_tracing_with_short_names_results_in_expected_trace_files");

    const auto t(dogen_product::input_dogen_org());
    const std::string id("detail_tracing_short_names");
    const auto tl(tracing_level::detail);
    const auto tf(tracing_format::org_mode);
    const bool eg(false/*enable_guids*/);
    const bool usn(true/*use_short_names*/);
    const auto cfg(setup_tracing_configuration(t, id, tl, tf, eg, usn));
    remove_byproducts_directory(cfg);

    const auto od(dogen_product::output_directory() / id);
    const auto rds(dogen_product::reference_directories());
    apply_transforms(cfg, od, rds, t);

    BOOST_CHECK(are_tracing_files_healthy(cfg, lg));
}

BOOST_AUTO_TEST_CASE(enabling_diffing_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_diffing_results_in_expected_trace_files");

    const auto t(dogen_product::input_dogen_org());
    const std::string id("diffing");
    const auto cfg(setup_diffing_configuration(t, id));

    const auto od(dogen_product::output_directory() / id);
    const auto rds(dogen_product::reference_directories());
    apply_transforms(cfg, od, rds, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 1);

    const auto f(*files.begin());
    const auto fn(f.filename().string());
    BOOST_REQUIRE(fn == diff_fn);
}

BOOST_AUTO_TEST_CASE(enabling_reporting_org_mode_style_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_reporting_org_mode_style_results_in_expected_trace_files");

    const auto t(dogen_product::input_dogen_org());
    const std::string id("reporting_org_mode");
    const auto rs(reporting_style::org_mode);
    const auto cfg(setup_reporting_configuration(t, id, rs));

    const auto od(dogen_product::output_directory() / id);
    const auto rds(dogen_product::reference_directories());
    apply_transforms(cfg, od, rds, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 1);

    const auto f(*files.begin());
    const auto fn(f.filename().string());
    BOOST_REQUIRE(fn == report_org_mode_fn);
}

BOOST_AUTO_TEST_CASE(enabling_reporting_plain_style_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_reporting_plain_style_results_in_expected_trace_files");

    const auto t(dogen_product::input_dogen_org());
    const std::string id("reporting_plain");
    const auto rs(reporting_style::plain);
    const auto cfg(setup_reporting_configuration(t, id, rs));

    const auto od(dogen_product::output_directory() / id);
    const auto rds(dogen_product::reference_directories());
    apply_transforms(cfg, od, rds, t);

    BOOST_REQUIRE(boost::filesystem::exists(cfg.byproduct_directory()));

    using dogen::utility::filesystem::find_files;
    const auto files(find_files(cfg.byproduct_directory()));
    BOOST_REQUIRE(files.size() == 1);

    const auto f(*files.begin());
    const auto fn(f.filename().string());
    BOOST_REQUIRE(fn == report_plain_fn);
}

BOOST_AUTO_TEST_SUITE_END()
