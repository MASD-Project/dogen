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
#include <locale>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/string/differ.hpp"
#include "dogen.utility/types/environment/variable_reader.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/types/transforms/context_bootstrapping_chain.hpp"
#include "dogen.physical/io/entities/operation_io.hpp"
#include "dogen.physical/io/entities/operation_reason_io.hpp"
#include "dogen.orchestration/types/transforms/context_bootstrapping_chain.hpp"
#include "dogen/types/mock_configuration_factory.hpp"
#include "dogen.orchestration/types/transforms/physical_model_production_chain.hpp"
#include "dogen.codec/types/transforms/artefact_to_artefact_chain.hpp"
#include "dogen.codec/types/transforms/file_to_artefact_transform.hpp"
#include "dogen.orchestration/tests/model_producer.hpp"

namespace  {

using namespace dogen::utility::log;
auto lg(logger_factory("orchestration.model_producer"));

const std::string conversion_activity("model_to_model");
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

}

namespace dogen::orchestration::tests {

void model_producer::print_lines(const std::string& content,
    const unsigned int total, std::ostream& os) {

    unsigned int i(0);
    std::string line;
    std::istringstream is(content);
    while (std::getline(is, line) && (i < total)) {
        os << line << std::endl;
        ++i;
    }
}

std::list<boost::shared_ptr<dogen::physical::entities::artefact>>
model_producer::gather_artefacts(const dogen::physical::entities::model& m) {
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

std::string model_producer::read_variability_override() {
    /*
     * If the environment variable forcing full generation is on, setup the
     * overrides and expected profile for it.
     */
    using vr = dogen::utility::environment::variable_reader;
    const std::string var("WITH_FULL_GENERATION");
    const auto original(vr::read_environment_variable(var));
    BOOST_LOG_SEV(lg, debug) << "Original environment variable."
                             << "Name: " << var
                             << " Value: " << original;

    using boost::algorithm::to_lower_copy;
    const std::string wfg = to_lower_copy(original);
    const bool with_full_generation(wfg == "on");
    if (with_full_generation) {
        BOOST_LOG_SEV(lg, debug) << "Full generation is ON.";

        const std::string full_generation_option =
            "masd.variability.profile, dogen.profiles.base.test_all_facets";
        BOOST_LOG_SEV(lg, debug) << "Full generation option: "
                                 << full_generation_option;

        return full_generation_option;
    } else {
        BOOST_LOG_SEV(lg, debug) << "Full generation is NOT enabled.";
        return std::string{};
    }
}

configuration model_producer::
make_configuration(const boost::filesystem::path& target,
    const bool enable_tracing_locally, const bool enable_reporting_locally,
    const bool enable_diffing_locally) {
    const bool et(enable_tracing_globally || enable_tracing_locally);
    const bool er(enable_reporting_globally || enable_reporting_locally);
    const bool ed(enable_diffing_globally || enable_diffing_locally);

    BOOST_LOG_SEV(lg, debug) << "Enable tracing: " << et
                             << " Enable reporting: " << er
                             << " Enable diffing: " << ed;

    mock_configuration_factory f(et, er, ed);
    auto r(f.make(target, run_activity));

    if (read_environment_variables_) {
        const auto variability_override = read_variability_override();
        if (!variability_override.empty()) {
            const std::vector<std::string> overrides({ variability_override });
            r.model_processing().variability_overrides(overrides);

            /*
             * Full generation requires us to fix the activity timestamp to a
             * well-known time point. This is because we need the tests to match
             * the code that was originally generated by the build.
             */
            using boost::gregorian::date;
            using boost::posix_time::ptime;
            using boost::posix_time::time_duration;
            ptime pt(date(2022, 10, 20), time_duration(10, 20, 30));
            r.model_processing().activity_timestamp(pt);
        } else {
            BOOST_LOG_SEV(lg, debug) << "No overrides present.";
        }
    } else {
        BOOST_LOG_SEV(lg, debug) << "Reading from environment disabled.";
    }

    return r;
}

dogen::physical::entities::model model_producer::
apply_physical_model_production(const boost::filesystem::path& target,
    const std::vector<boost::filesystem::path>& reference_directories,
    const boost::filesystem::path& output_dir,
    const bool enable_tracing_locally, const bool enable_reporting_locally,
    const bool enable_diffing_locally) {

    /*
     * Create the configuration.
     */
    const auto cfg(make_configuration(target, enable_tracing_locally,
            enable_reporting_locally, enable_diffing_locally));

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
    const auto r(physical_model_production_chain::apply(ctx, target));
    return r;
}

dogen::physical::entities::model model_producer::
apply_physical_model_production(const boost::filesystem::path& target,
    const boost::filesystem::path& output_dir,
    const bool enable_tracing_locally, const bool enable_reporting_locally,
    const bool enable_diffing_locally) {

    const std::vector<boost::filesystem::path> reference_directories;
    return apply_physical_model_production(target, reference_directories,
        output_dir, enable_tracing_locally, enable_reporting_locally,
        enable_diffing_locally);
}

bool model_producer::
has_differences(const physical::entities::artefact& a) {
    /*
     * We can safely ignore all files the user provided regexes
     * for.
     */
    using namespace dogen::physical::entities;
    if (a.operation().type() == operation_type::ignore &&
        a.operation().reason() == operation_reason::ignore_regex)
        return false;

    /*
     * If we are not writing or deleting the artefact, then its not a
     * difference.
     */
    if (a.operation().type() != operation_type::write &&
        a.operation().type() != operation_type::remove)
        return false;

    /*
     * All other cases are differences.
     */
    return true;
}

bool model_producer::check_for_differences(
    const boost::filesystem::path& output_dir,
    const dogen::physical::entities::model& m) {

    unsigned int diffs_found(0);
    const auto& artefacts(gather_artefacts(m));
    for (const auto& ptr : artefacts) {
        const auto& a(*ptr);
        if (!has_differences(a))
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
        using namespace dogen::physical::entities;
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
            } else {
                std::cout << "Unexpected write: " << gs << std::endl
                          << "Reason: " << rsn << std::endl;
                print_lines(a.unified_diff(), 20, std::cout);
            }
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

bool model_producer::
check_for_delete_extra(const boost::filesystem::path& output_dir,
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

bool model_producer::check_for_ignore_extra(
    const boost::filesystem::path& output_dir,
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

bool model_producer::check_for_force_write(
    const boost::filesystem::path& output_dir,
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

bool model_producer::check_out_of_sync(
    const boost::filesystem::path& output_dir,
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
