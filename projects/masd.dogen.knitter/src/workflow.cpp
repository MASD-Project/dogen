/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2014 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <iostream>
#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include "masd.dogen/version.hpp"
#include "masd.dogen.utility/types/log/lifecycle_manager.hpp"
#include "masd.dogen.utility/types/log/severity_level.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.extraction/types/formatting_error.hpp"
#include "masd.dogen.coding/types/transforms/options.hpp"
#include "masd.dogen.coding/types/transforms/context_factory.hpp"
#include "masd.dogen.coding/types/transforms/code_generation_chain.hpp"
#include "masd.dogen.knitter/initializer.hpp"
#include "masd.dogen.knitter/workflow_error.hpp"
#include "masd.dogen.knitter/program_options_parser.hpp"
#include "masd.dogen.knitter/parser_validation_error.hpp"
#include "masd.dogen.knitter/workflow.hpp"

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("knitter"));
const std::string log_file_prefix("dogen.knitter.");
const std::string more_information(
    "Try `dogen.knitter --help' for more information.");
const std::string knitter_product("Dogen Knitter v" DOGEN_VERSION);
const std::string knitter_build_info(DOGEN_BUILD_INFO);
const std::string usage_error_msg("Usage error: ");
const std::string fatal_error_msg("Fatal Error: " );
const std::string code_generation_failure("Code generation failure.");
const std::string log_file_msg("See the log file for details: ");
const std::string errors_msg(" finished with errors.");

/**
 * @brief Print the program's help text.
 */
void help(const std::string& d) {
    std::cout << "MASD Dogen Knitter." << std::endl
              << "Model driven engineering tool to generate source code "
              << std::endl << "from supported input models."
              << std::endl << std::endl << d << std::endl;
}

/**
 * @brief Print the program's version details.
 */
void version() {
    std::cout << knitter_product << std::endl
              << "Copyright (C) 2015-2017 Domain Driven Consulting Plc."
              << std::endl
              << "Copyright (C) 2012-2015 Marco Craveiro." << std::endl
              << "License: GPLv3 - GNU GPL version 3 or later "
              << "<http://gnu.org/licenses/gpl.html>." << std::endl;

    if (!knitter_build_info.empty()) {
        std::cout << knitter_build_info << std::endl;
        std::cout << "IMPORTANT: build details are NOT for security purposes."
                  << std::endl;
    }
}

}

namespace masd::dogen::knitter {

workflow::workflow() : can_log_(false) { }

void workflow::
initialise_model_name(const coding::transforms::options& o) {
    const boost::filesystem::path p(o.target());
    model_name_ = p.stem().filename().string();
}

boost::optional<coding::transforms::options>
workflow::generate_options(const int argc, const char* argv[]) const {
    program_options_parser p(argc, argv);
    p.help_function(help);
    p.version_function(version);

    auto r(p.parse());
    if (!r)
        return r;

    return r;
}

void workflow::initialise_logging(const coding::transforms::options& o) {
    log_path_ = o.log_file();
    const auto sev(utility::log::to_severity_level(o.log_level()));
    lifecycle_manager::initialise(o.log_file(), sev);
    can_log_ = true;
}

void workflow::knit(const coding::transforms::options& o) const {
    BOOST_LOG_SEV(lg, info) << knitter_product << " started.";

    initializer::initialize();

    try {
        using namespace coding::transforms;
        const auto ctx(context_factory::make(o));
        code_generation_chain::transform(ctx);
    } catch(const masd::dogen::extraction::formatting_error& e) {
        BOOST_THROW_EXCEPTION(workflow_error(e.what()));
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << knitter_product << " finished.";
}

void workflow::report_exception_common() const {
    if (can_log_) {
        BOOST_LOG_SEV(lg, warn) << knitter_product << errors_msg;
        std::cerr << log_file_msg << "'" << log_path_.generic_string()
                  << "' " << std::endl;
    }

    if (model_name_.empty())
        return;

    std::cerr << "Failed to generate model: '" << model_name_ << "'."
              << std::endl;
}

void workflow::report_exception(const std::exception& e) const {
    /*
     * We must catch by std::exception and cast the boost exception
     * here; if we were to catch boost exception, we would not have
     * access to the what() method and thus could not provide a
     * user-friendly message to the console.
     */
    const auto be(dynamic_cast<const boost::exception* const>(&e));
    if (be && can_log_) {
        BOOST_LOG_SEV(lg, error) << "Error: "
                                 << boost::diagnostic_information(*be);
    }

    std::cerr << "Error: " << e.what() << std::endl;
    report_exception_common();
}

void workflow::report_exception() const {
    std::cerr << "Knitter was forced to terminate." << std::endl;
    report_exception_common();
}

int workflow::execute(const int argc, const char* argv[]) {
    try {
        const auto o(generate_options(argc, argv));

        /*
         * Can only happen if the options are valid but do not
         * require any action.
         */
        if (!o)
            return 0;

        const auto& s(*o);
        initialise_model_name(s);
        initialise_logging(s);
        knit(s);
    } catch (const knitter::parser_validation_error& e) {
        /*
         * Log known not to be initialised as we are still parsing
         * command line options.
         */
        std::cerr << usage_error_msg << e.what() << std::endl
                  << more_information << std::endl;
        return 1;
    } catch (const std::exception& e) {
        report_exception(e);
        return 1;
    } catch(...) {
        report_exception();
        return 1;
    }
    lifecycle_manager::shutdown();
    return 0;
}

}
