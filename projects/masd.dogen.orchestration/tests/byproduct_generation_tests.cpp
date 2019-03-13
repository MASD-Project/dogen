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
const std::string archetype_location_fn(
    "000-archetype_location_repository.json");
const std::string injection_transform_prefix(
    "001-injection.dia.decoding_transform-");
const std::string first_short_name("000.json");
const std::string second_short_name("001.json");
const std::string injection_transform_postfix("-input.json");
const std::regex tracing_regex(".*/tracing/.*");
const std::regex guid_regex(
    "[a-f0-9]{8}-[a-f0-9]{4}-4[a-f0-9]{3}-[89aAbB][a-f0-9]{3}-[a-f0-9]{12}");

using boost::filesystem::path;
using masd::dogen::configuration;
using masd::dogen::tracing_level;
using masd::dogen::tracing_format;
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
 * @note We also ensure the byproduct directory is empty.
 */
configuration setup_tracing_configuration(const path& target,
    const std::string& additional_identifier, const tracing_level tl,
    const tracing_format tf, const bool enable_guids = false,
    const bool use_short_names = false) {
    /*
     * First, we setup the factory to enable tracing and _nothing_
     * else. Note that we don't worry about logging because by default
     * logs go into a testing specific logs directory.
     */
    const mock_configuration_factory f(true/*enable_tracing*/,
        false/*enable_reporting*/, false/*enable_diffing*/);

    /*
     * Setup the target and get the config. Note that we target a
     * small model as we don't particularly care about the code
     * generation itself.
     */
    auto r(f.make(target, run_activity + "." + additional_identifier));

    /*
     * Now we costumise the configuration to make sure it meets the
     * needs of the test.
     */
    r.tracing()->level(tl);
    r.tracing()->format(tf);
    r.tracing()->guids_enabled(enable_guids);
    r.tracing()->use_short_names(use_short_names);

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

bool are_tracing_files_healthy(const configuration& cfg) {
    /*
     * Ensure we have created a byproducts directory.
     */
    using namespace boost::filesystem;
    if (!exists(cfg.byproduct_directory()))
        return false;
    BOOST_TEST_MESSAGE("Directory exists.");

    /*
     * Ensure we have created the minimum number of expected files.
     */
    using masd::dogen::utility::filesystem::find_files;
    const boost::uintmax_t minimum_number(100);
    const auto files(find_files(cfg.byproduct_directory()));
    if (files.size() < minimum_number)
        return false;
    BOOST_TEST_MESSAGE("Files." << files.size());

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
        const auto sz(file_size(f));
        BOOST_TEST_MESSAGE("Size." << sz);
        if (sz < minimum_size)
            return false;

        /*
         * We only expect files inside the tracing directory.
         */
        const auto gs(f.generic_string());
        BOOST_TEST_MESSAGE("gs." << gs);
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
                found_injection_dia_transform = true;
        } else {
            if (fn == transform_stats_org_fn)
                found_transform_stats = true;
            else if (fn == archetype_location_fn)
                found_archetype_location = true;
            else if (boost::starts_with(fn, injection_transform_prefix) &&
                boost::ends_with(fn, injection_transform_postfix)) {
                found_injection_dia_transform = true;
                BOOST_TEST_MESSAGE("Found injection.");

                /*
                 * Ensure filenames have a guid (since we requested it in
                 * the config) and the guid is valid.
                 */
                auto guid(fn);
                boost::erase_first(guid, injection_transform_prefix);
                boost::erase_first(guid, injection_transform_postfix);
                BOOST_TEST_MESSAGE("guid:" << guid);
                if (guid.size() != 36)
                    return false;

                BOOST_TEST_MESSAGE("before regex match");
                if (!std::regex_match(guid, guid_regex))
                    return false;

                BOOST_TEST_MESSAGE("after regex match");
            }
        }
    }
    return
        found_transform_stats &&
        found_archetype_location &&
        found_injection_dia_transform;
}

}

BOOST_AUTO_TEST_SUITE(byproduct_generation_tests)

BOOST_AUTO_TEST_CASE(enabling_detailed_tracing_with_org_mode_results_in_expected_trace_files) {
    SETUP_TEST_LOG("enabling_detailed_tracing_with_org_moderesults_in_expected_trace_files");

    const auto t(dogen_generation::input_masd_dogen_dia());
    const std::string id("detailed_tracing_org_mode");
    const auto tl(tracing_level::detail);
    const auto tf(tracing_format::org_mode);
    const bool eg(true/*enable_guids*/);
    const auto cfg(setup_tracing_configuration(t, id, tl, tf, eg));
    remove_byproducts_directory(cfg);

    const auto od(dogen_generation::output_directory() / id);
    apply_transforms(cfg, od, t);

    BOOST_CHECK(are_tracing_files_healthy(cfg));
}

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
    SETUP_TEST_LOG("enabling_detailed_tracing_with_short_names_results_in_expected_trace_files");

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

    BOOST_CHECK(are_tracing_files_healthy(cfg));
}

BOOST_AUTO_TEST_SUITE_END()
