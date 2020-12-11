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
#include "dogen/types/mock_configuration_factory.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test_data/dogen_product.hpp"
#include "dogen.utility/types/test_data/cpp_ref_impl_product.hpp"
#include "dogen.utility/types/test_data/csharp_ref_impl_product.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/operation_io.hpp"
#include "dogen.physical/io/entities/operation_reason_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.orchestration/types/transforms/context_bootstrapping_chain.hpp"
#include "dogen.orchestration/types/transforms/physical_model_production_chain.hpp"

namespace  {

const std::string test_module("dogen.orchestration.tests");
const std::string test_suite("physical_model_production_chain_tests");

const std::string run_activity("physical_production");
const std::string unexpected_ignore_fn("unexpected_ignore.hpp");
const std::string expected_ignore_fn("expected_ignore.hpp");
const std::string changed_handcrafted_hpp_fn("changed_handcrafted.hpp");
const std::string changed_handcrafted_cpp_fn("changed_handcrafted.cpp");

/*
 * Set these flag to true if you want to dump information for all
 * tests. All except for diffing should normally be set to false,
 * unless we are diagnosing some kind of problem. Don't check it in as
 * true as it slows down the tests for no good reason.
 */
const bool enable_tracing_globally(false);
const bool enable_reporting_globally(true);
const bool enable_diffing_globally(true);

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

std::list<boost::shared_ptr<dogen::physical::entities::artefact>>
gather_artefacts(const dogen::physical::entities::model& m) {
    std::list<boost::shared_ptr<dogen::physical::entities::artefact>> r;
    for (const auto& pr_pair : m.regions_by_logical_id()) {
        const auto& as(pr_pair.second);
        for (const auto& a_pair : as.artefacts_by_archetype())
            r.push_back(a_pair.second);
    }

    for (const auto& a : m.orphan_artefacts())
        r.push_back(a);

    return r;
}

dogen::physical::entities::model
apply_physical_model_production(const boost::filesystem::path& target,
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
    using dogen::mock_configuration_factory;
    mock_configuration_factory f(et, er, ed);
    const auto cfg(f.make(target, run_activity));

    /*
     * Bootstrap the top-level context.
     */
    using namespace dogen::orchestration::transforms;
    using cbc = context_bootstrapping_chain;
    const auto& od(output_dir);
    const auto& a(run_activity);
    const auto ctx(cbc::bootstrap_full_context(cfg, a, od));

    /*
     * Bind the tracer to the current scope.
     */
    const auto& t(*ctx.codec_context().tracer());
    dogen::tracing::scoped_tracer st(t);

    /*
     * Produce the physical model.
     */
    const auto r(physical_model_production_chain::apply(ctx, target));
    return r;
}

/**
 * @brief Checks to see if the model contains any artefacts which are
 * different from the files in the filesystem.
 *
 * @note We're using std::cout here by design as we always want the
 * output to show up in CDash.
 */
bool check_for_differences(const boost::filesystem::path& output_dir,
    const dogen::physical::entities::model& m) {

    unsigned int diffs_found(0);
    const auto& artefacts(gather_artefacts(m));
    for (const auto& ptr : artefacts) {
        const auto& a(*ptr);
        using namespace dogen::physical::entities;
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

        const bool is_first_diff(diffs_found == 0);
        if (is_first_diff) {
            std::cout << "Differences found. Outputting head of first 5 diffs."
                      << std::endl;
        }

        ++diffs_found;
        if (diffs_found > 5)
            break;

        const auto& p(a.file_path());
        const auto rel(p.lexically_relative(output_dir));
        const auto gs(rel.generic_string());
        if (a.operation().type() == operation_type::remove)
            std::cout << "Unexpected file (remove): " << gs << std::endl;
        else if (a.operation().type() == operation_type::write) {
            const auto rsn(a.operation().reason());
            if (rsn == operation_reason::newly_generated)
                std::cout << "New file: " << gs << std::endl;
            else if (rsn == operation_reason::force_write &&
                a.unified_diff().empty()) {
                std::cout << "Unexpected force write (no diffs): "
                          << gs << std::endl;
            } else
                print_lines(a.unified_diff(), 20, std::cout);
        } else if (a.operation().type() == operation_type::ignore) {
            if (a.operation().reason() == operation_reason::ignore_unexpected)
                std::cout << "Unexpected file (ignore): " << gs << std::endl;
            else {
                std::cout << "Unexpected file, unexpected reason: "
                          << a.operation().reason() << ". File: "
                          << gs << std::endl;
            }
        } else {
            std::cout << "Unexpected operation: " << a.operation()
                      << " File: " << gs << std::endl;
        }
    }
    return diffs_found == 0;
}

/**
 * @brief Performs a set of checks for the delete extra scenario.
 */
bool check_for_delete_extra(const boost::filesystem::path& output_dir,
    const dogen::physical::entities::model& m) {
    unsigned int diffs_found(0);
    const auto& artefacts(gather_artefacts(m));
    for (const auto& ptr : artefacts) {
        const auto& a(*ptr);

        if (diffs_found > 5)
            break;

        const auto& p(a.file_path());
        const auto fn(p.filename().generic_string());
        const auto ot(a.operation().type());
        const auto rsn(a.operation().reason());
        const auto rel(p.lexically_relative(output_dir));
        const auto gs(rel.generic_string());

        using namespace dogen::physical::entities;
        if (fn == unexpected_ignore_fn) {
            /*
             * File should be removed because it is unexpected and
             * delete extra files is on.
             */
            if (ot != operation_type::remove ||
                rsn != operation_reason::unexpected) {
                ++diffs_found;
                std::cout << "Expected remove of file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        } else if (fn == expected_ignore_fn) {
            /*
             * File should be ignored because it is on the list of
             * ignore files matching regex.
             */
            if (ot != operation_type::ignore ||
                rsn != operation_reason::ignore_regex) {
                ++diffs_found;
                std::cout << "Expected ignore of file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        } else {
            /*
             * All other files should be generated and unchanged.
             */
            if (ot != operation_type::ignore ||
                rsn != operation_reason::unchanged_generated) {
                ++diffs_found;
                std::cout << "Expected ignore of generated file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        }
    }
    return diffs_found == 0;
}

/**
 * @brief Performs a set of checks for the delete extra scenario.
 */
bool check_for_ignore_extra(const boost::filesystem::path& output_dir,
    const dogen::physical::entities::model& m) {
    unsigned int diffs_found(0);
    const auto& artefacts(gather_artefacts(m));
    for (const auto& ptr : artefacts) {
        const auto& a(*ptr);

        if (diffs_found > 5)
            break;

        const auto& p(a.file_path());
        const auto fn(p.filename().generic_string());
        const auto ot(a.operation().type());
        const auto rsn(a.operation().reason());
        const auto rel(p.lexically_relative(output_dir));
        const auto gs(rel.generic_string());

        using namespace dogen::physical::entities;
        if (fn == unexpected_ignore_fn) {
            /*
             * File should not be removed because whilst it is
             * unexpected, delete extra files is off.
             */
            if (ot != operation_type::ignore ||
                rsn != operation_reason::ignore_unexpected) {
                ++diffs_found;
                std::cout << "Expected remove of file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        } else if (fn == expected_ignore_fn) {
            /*
             * File should be ignored because it is on the list of
             * ignore files matching regex.
             */
            if (ot != operation_type::ignore ||
                rsn != operation_reason::ignore_regex) {
                ++diffs_found;
                std::cout << "Expected ignore of file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        } else {
            /*
             * All other files should be generated and unchanged.
             */
            if (ot != operation_type::ignore ||
                rsn != operation_reason::unchanged_generated) {
                ++diffs_found;
                std::cout << "Expected ignore of generated file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        }
    }
    return diffs_found == 0;
}

/**
 * @brief Performs a set of checks for the delete extra scenario.
 */
bool check_for_force_write(const boost::filesystem::path& output_dir,
    const dogen::physical::entities::model& m) {
    unsigned int diffs_found(0);
    const auto& artefacts(gather_artefacts(m));
    for (const auto& ptr : artefacts) {
        const auto& a(*ptr);

        if (diffs_found > 5)
            break;

        const auto& p(a.file_path());
        const auto fn(p.filename().generic_string());
        const auto ot(a.operation().type());
        const auto rsn(a.operation().reason());
        const auto rel(p.lexically_relative(output_dir));
        const auto gs(rel.generic_string());

        using namespace dogen::physical::entities;
        if (fn == changed_handcrafted_hpp_fn ||
            fn == changed_handcrafted_cpp_fn) {
            /*
             * Files with overwrite should be ignored, even when
             * force write is on.
             */
            if (ot != operation_type::ignore ||
                rsn != operation_reason::already_exists) {
                ++diffs_found;
                std::cout << "Expected ignore of file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        } else {
            /*
             * All other files should be generated and written because
             * force write is on.
             */
            if (ot != operation_type::write ||
                rsn != operation_reason::force_write) {
                ++diffs_found;
                std::cout << "Expected write of generated file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        }
    }
    return diffs_found == 0;
}

/**
 * @brief Performs a set of checks for the model out of sync scenario.
 */
bool check_out_of_sync(const boost::filesystem::path& output_dir,
    const dogen::physical::entities::model& m) {
    unsigned int diffs_found(0);
    const auto& artefacts(gather_artefacts(m));
    for (const auto& ptr : artefacts) {
        const auto& a(*ptr);

        if (diffs_found > 5)
            break;

        const auto ot(a.operation().type());
        const auto rsn(a.operation().reason());
        const auto& p(a.file_path());
        const auto rel(p.lexically_relative(output_dir /
                "cpp_ref_impl.out_of_sync"));
        const auto gs(rel.generic_string());
        using namespace dogen::physical::entities;
        if (gs == "include/cpp_ref_impl.out_of_sync/types/all.hpp" ||
            gs == "include/cpp_ref_impl.out_of_sync/types/changed_generated.hpp" ||
            gs == "src/hash/changed_generated_hash.cpp" ||
            gs == "src/io/changed_generated_io.cpp" ||
            gs == "src/serialization/changed_generated_ser.cpp" ||
            gs == "src/test_data/changed_generated_td.cpp" ||
            gs == "src/types/changed_generated.cpp") {
            /*
             * Generated files which have changed should be written.
             */
            if (ot != operation_type::write ||
                rsn != operation_reason::changed_generated) {
                ++diffs_found;
                std::cout << "Expected write for file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        } else if (
            gs == "include/cpp_ref_impl.out_of_sync/types/changed_handcrafted.hpp" ||
            gs == "include/cpp_ref_impl.out_of_sync/types/unchanged_handcrafted.hpp" ||
            gs == "src/types/changed_handcrafted.cpp" ||
            gs == "src/types/unchanged_handcrafted.cpp") {
            /*
             * Files with the overwrite flag that already exist should
             * be ignored.
             */
            if (ot != operation_type::ignore ||
                rsn != operation_reason::already_exists) {
                ++diffs_found;
                std::cout << "Expected ignore for file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        } else if (
            gs == "include/cpp_ref_impl.out_of_sync/types/handcrafted_new.hpp" ||
            gs == "src/types/handcrafted_new.cpp") {
            /*
             * Files with the overwrite flag that don't yet exist
             * should be created.
             */
            if (ot != operation_type::write ||
                rsn != operation_reason::newly_generated) {
                ++diffs_found;
                std::cout << "Expected write for file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        } else {
            /*
             * Generated files that have not changed should be ignored
             * because force write flag is off.
             */
            if (ot != operation_type::ignore ||
                rsn != operation_reason::unchanged_generated) {
                ++diffs_found;
                std::cout << "Expected ignore of file: " << gs
                          << " Operation: " << a.operation() << std::endl;
            }
        }
    }
    return diffs_found == 0;
}

}

BOOST_AUTO_TEST_SUITE(physical_model_production_chain_tests)

BOOST_AUTO_TEST_CASE(dogen_variability_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_variability_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_variability_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_cli_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_cli_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_cli_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_logical_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_logical_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_logical_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_dia_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_dia_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_dia_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_physical_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_physical_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_physical_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_text_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_text_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_text_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_codec_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_product_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_codec_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_codec_dia_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_codec_dia_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_codec_dia_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_orchestration_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_orchestration_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_orchestration_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_templating_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_templating_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_templating_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_tracing_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_tracing_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_tracing_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(dogen_utility_dia_produces_expected_model) {
    SETUP_TEST_LOG("dogen_utility_dia_produces_expected_model");
    using dogen::utility::test_data::dogen_product;
    const auto t(dogen_product::input_dogen_utility_dia());
    const auto od(dogen_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

#ifdef ENABLE_CPP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(cpp_ref_impl_boost_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_boost_model_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_boost_model_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_compressed_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_compressed_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_compressed_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_cpp_98_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_cpp_98_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_cpp_98_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_cpp_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_cpp_model_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_cpp_model_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_directory_settings_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_directory_settings_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_directory_settings_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_disable_cmakelists_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_disable_cmakelists_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_disable_cmakelists_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_disable_facet_folders_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_disable_facet_folders_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_disable_facet_folders_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_hash_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_hash_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_hash_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_io_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_io_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_io_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_serialization_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_serialization_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_serialization_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_types_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_types_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_types_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_flat_directory_mode_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_flat_directory_mode_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_flat_directory_mode_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_lam_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_lam_model_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_lam_model_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_northwind_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_northwind_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_northwind_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_split_project_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_split_project_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_split_project_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_std_model_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_std_model_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_std_model_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_two_layers_with_objects_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_two_layers_with_objects_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_two_layers_with_objects_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_delete_extra_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_delete_extra_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_delete_extra_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto et(false/*enable_tracing_locally*/);
    const auto er(true/*enable_reporting_locally*/);
    const auto m(apply_physical_model_production(t, od, et, er));
    BOOST_CHECK(check_for_delete_extra(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_force_write_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_two_layers_with_objects_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_force_write_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto et(false/*enable_tracing_locally*/);
    const auto er(true/*enable_reporting_locally*/);
    const auto m(apply_physical_model_production(t, od, et, er));
    BOOST_CHECK(check_for_force_write(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_ignore_extra_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_ignore_extra_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_ignore_extra_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto et(false/*enable_tracing_locally*/);
    const auto er(true/*enable_reporting_locally*/);
    const auto m(apply_physical_model_production(t, od, et, er));
    BOOST_CHECK(check_for_ignore_extra(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_out_of_sync_dia_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_out_of_sync_dia_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_out_of_sync_dia());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto et(false/*enable_tracing_locally*/);
    const auto er(true/*enable_reporting_locally*/);
    const auto m(apply_physical_model_production(t, od, et, er));
    BOOST_CHECK(check_out_of_sync(od, m));
}

#endif // ENABLE_CPP_REF_IMPL_TESTS

#ifdef ENABLE_CSHARP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(csharprefimpl_csharpmodel_dia_produces_expected_model) {
    SETUP_TEST_LOG("csharprefimpl_csharpmodel_dia_produces_expected_model");
    using dogen::utility::test_data::csharp_ref_impl_product;
    const auto t(csharp_ref_impl_product::input_csharprefimpl_csharpmodel_dia());
    const auto od(csharp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(csharprefimpl_directory_settings_dia_produces_expected_model) {
    SETUP_TEST_LOG("csharprefimpl_directory_settings_dia_produces_expected_model");
    using dogen::utility::test_data::csharp_ref_impl_product;
    const auto t(csharp_ref_impl_product::input_csharprefimpl_directory_settings_dia());
    const auto od(csharp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(csharprefimpl_lammodel_dia_produces_expected_model) {
    SETUP_TEST_LOG("csharprefimpl_lammodel_dia_produces_expected_model");
    using dogen::utility::test_data::csharp_ref_impl_product;
    const auto t(csharp_ref_impl_product::input_csharprefimpl_lammodel_dia());
    const auto od(csharp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

#endif // ENABLE_CSHARP_REF_IMPL_TESTS

#ifdef ENABLE_CPP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(cpp_ref_impl_boost_model_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_boost_model_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_boost_model_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_compressed_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_compressed_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_compressed_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_cpp_98_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_cpp_98_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_cpp_98_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_cpp_model_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_cpp_model_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_cpp_model_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_directory_settings_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_directory_settings_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_directory_settings_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_disable_cmakelists_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_disable_cmakelists_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_disable_cmakelists_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_disable_facet_folders_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_disable_facet_folders_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_disable_facet_folders_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_hash_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_hash_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_hash_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_io_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_io_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_io_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_serialization_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_serialization_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_serialization_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_enable_facet_types_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_enable_facet_types_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_types_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_flat_directory_mode_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_flat_directory_mode_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_flat_directory_mode_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_lam_model_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_lam_model_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_lam_model_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_northwind_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_northwind_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_northwind_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_split_project_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_split_project_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_split_project_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_std_model_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_std_model_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_std_model_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_two_layers_with_objects_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_two_layers_with_objects_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_two_layers_with_objects_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_delete_extra_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_delete_extra_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_delete_extra_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto et(false/*enable_tracing_locally*/);
    const auto er(true/*enable_reporting_locally*/);
    const auto m(apply_physical_model_production(t, od, et, er));
    BOOST_CHECK(check_for_delete_extra(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_force_write_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_two_layers_with_objects_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_force_write_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto et(false/*enable_tracing_locally*/);
    const auto er(true/*enable_reporting_locally*/);
    const auto m(apply_physical_model_production(t, od, et, er));
    BOOST_CHECK(check_for_force_write(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_ignore_extra_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_ignore_extra_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_ignore_extra_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto et(false/*enable_tracing_locally*/);
    const auto er(true/*enable_reporting_locally*/);
    const auto m(apply_physical_model_production(t, od, et, er));
    BOOST_CHECK(check_for_ignore_extra(od, m));
}

BOOST_AUTO_TEST_CASE(cpp_ref_impl_out_of_sync_json_produces_expected_model) {
    SETUP_TEST_LOG("cpp_ref_impl_out_of_sync_json_produces_expected_model");
    using dogen::utility::test_data::cpp_ref_impl_product;
    const auto t(cpp_ref_impl_product::input_cpp_ref_impl_out_of_sync_json());
    const auto od(cpp_ref_impl_product::project_directory());
    const auto et(false/*enable_tracing_locally*/);
    const auto er(true/*enable_reporting_locally*/);
    const auto m(apply_physical_model_production(t, od, et, er));
    BOOST_CHECK(check_out_of_sync(od, m));
}

#endif // ENABLE_CPP_REF_IMPL_TESTS

#ifdef ENABLE_CSHARP_REF_IMPL_TESTS

BOOST_AUTO_TEST_CASE(csharprefimpl_csharpmodel_json_produces_expected_model) {
    SETUP_TEST_LOG("csharprefimpl_csharpmodel_json_produces_expected_model");
    using dogen::utility::test_data::csharp_ref_impl_product;
    const auto t(csharp_ref_impl_product::input_csharprefimpl_csharpmodel_json());
    const auto od(csharp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(csharprefimpl_directorysettings_json_produces_expected_model) {
    SETUP_TEST_LOG("csharprefimpl_directorysettings_json_produces_expected_model");
    using dogen::utility::test_data::csharp_ref_impl_product;
    const auto t(csharp_ref_impl_product::input_csharprefimpl_directory_settings_json());
    const auto od(csharp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

BOOST_AUTO_TEST_CASE(csharprefimpl_lammodel_json_produces_expected_model) {
    SETUP_TEST_LOG("csharprefimpl_lammodel_json_produces_expected_model");
    using dogen::utility::test_data::csharp_ref_impl_product;
    const auto t(csharp_ref_impl_product::input_csharprefimpl_lammodel_json());
    const auto od(csharp_ref_impl_product::project_directory());
    const auto m(apply_physical_model_production(t, od));
    BOOST_CHECK(check_for_differences(od, m));
}

#endif // ENABLE_CSHARP_REF_IMPL_TESTS

BOOST_AUTO_TEST_SUITE_END()
