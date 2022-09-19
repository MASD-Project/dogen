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
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen/io/configuration_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/differ.hpp"
#include "dogen.utility/types/environment/variable_reader.hpp"
#include "dogen/types/mock_configuration_builder.hpp"

namespace  {

using namespace dogen::utility::log;
auto lg(logger_factory("dogen.mock_configuration_builder"));

/*
 * Set these flag to true if you want to dump information for all tests. All
 * except for diffing should normally be set to false, unless we are diagnosing
 * some kind of problem. Don't check it in as true as it slows down the tests
 * for no good reason.
 */
const bool enable_tracing_globally(false);
const bool enable_reporting_globally(false);
const bool enable_diffing_globally(false);
const bool read_environment_globally(false);

constexpr std::string_view dot(".");
constexpr std::string_view run_identifier_prefix("tests.");

const std::string byproduct_directory("dogen.byproducts/");
const std::string tracing_directory("tracing");

}

namespace dogen {

mock_configuration_builder& mock_configuration_builder::
target(const boost::filesystem::path& target) {
    BOOST_LOG_SEV(lg, debug) << "Setting target: " << target;
    target_ = target;
    return *this;
}

mock_configuration_builder& mock_configuration_builder::
activity(const std::string& activity) {
    BOOST_LOG_SEV(lg, debug) << "Setting activity: " << activity_;
    activity_ = activity;
    return *this;
}

mock_configuration_builder& mock_configuration_builder::
enable_tracing(const bool enable_tracing) {
    BOOST_LOG_SEV(lg, debug) << "Setting enable tracing: " << enable_tracing;
    enable_tracing_locally_ = enable_tracing;
    return *this;
}

mock_configuration_builder& mock_configuration_builder::
enable_reporting(const bool enable_reporting) {
    BOOST_LOG_SEV(lg, debug) << "Setting enable reporting: " << enable_reporting;
    enable_reporting_locally_ = enable_reporting;
    return *this;
}

mock_configuration_builder& mock_configuration_builder::
enable_diffing(const bool enable_diffing) {
    BOOST_LOG_SEV(lg, debug) << "Setting enable diffing: " << enable_diffing;
    enable_diffing_locally_ = enable_diffing;
    return *this;
}

mock_configuration_builder& mock_configuration_builder::
read_environment(const bool read_environment) {
    BOOST_LOG_SEV(lg, debug) << "Setting read environment: "
                             << read_environment;
    read_environment_locally_ = read_environment;
    return *this;
}

std::string mock_configuration_builder::read_variability_override() const {
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

configuration mock_configuration_builder::build() const {
    const bool et(enable_tracing_globally || enable_tracing_locally_);
    const bool er(enable_reporting_globally || enable_reporting_locally_);
    const bool ed(enable_diffing_globally || enable_diffing_locally_);

    BOOST_LOG_SEV(lg, debug) << "Enable tracing: " << et
                             << " Enable reporting: " << er
                             << " Enable diffing: " << ed;

    using namespace dogen;
    configuration r;

    std::ostringstream s;
    s << run_identifier_prefix << activity_;

    const auto fn(target_.filename().string());
    if (!fn.empty())
        s << dot << fn;

    const auto run_id(s.str());
    using boost::filesystem::absolute;
    r.byproduct_directory(absolute(byproduct_directory + run_id));

    if (ed) {
        BOOST_LOG_SEV(lg, debug) << "Diffing enabled.";
        diffing_configuration dcfg;
        dcfg.destination(diffing_destination::file);
        dcfg.output_directory(r.byproduct_directory());
        r.diffing(dcfg);
    }

    if (et) {
        BOOST_LOG_SEV(lg, debug) << "Tracing enabled.";
        tracing_configuration tcfg;
        tcfg.level(tracing_level::detail);
        tcfg.format(tracing_format::org_mode);
        tcfg.backend(tracing_backend::file);
        tcfg.guids_enabled(true);
        tcfg.logging_impact("severe");
        tcfg.output_directory(r.byproduct_directory() / tracing_directory);
        r.tracing(tcfg);
    }

    if (er) {
        BOOST_LOG_SEV(lg, debug) << "Reporting enabled.";
        reporting_configuration rcfg;
        rcfg.style(reporting_style::org_mode);
        rcfg.output_directory(r.byproduct_directory());
        r.reporting(rcfg);
    }

    const bool re(read_environment_globally || read_environment_locally_);
    if (!re) {
        BOOST_LOG_SEV(lg, debug) << "Reading from environment disabled.";
    } else {
        const auto variability_override = read_variability_override();
        if (!variability_override.empty()) {
            const std::vector<std::string> overrides({ variability_override });
            r.model_processing().variability_overrides(overrides);
        }
        BOOST_LOG_SEV(lg, debug) << "No overrides present.";
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating mock configuration. Result: "
                             << r;
    return r;
}

}
