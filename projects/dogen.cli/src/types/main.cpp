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
#include <cstdlib>
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <boost/exception/diagnostic_information.hpp>
#include "dogen.utility/types/io/vector_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/log/severity_level.hpp"
#include "dogen.utility/types/log/logging_configuration.hpp"
#include "dogen.utility/types/log/scoped_lifecycle_manager.hpp"
#include "dogen.cli/io/configuration_io.hpp"
#include "dogen.cli/types/initializer.hpp"
#include "dogen.cli/types/application.hpp"
#include "dogen.cli/types/injector_factory.hpp"
#include "dogen.cli/types/parser_exception.hpp"
#include "dogen.cli/types/command_line_parser.hpp"
#include "dogen/config.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("main"));

const std::string err_prefix("Error: ");
const std::string activity_failure("Failed to execute command.");
const std::string force_terminate("Application was forced to terminate.");

/**
 * @brief Reports exceptions to the log and console.
 */
void report_exception(const bool can_log, const std::exception& e) {
    /*
     * Dump to the console first. Here we just want to make our output
     * as humanly readable as possible.
     */
    std::cerr << err_prefix << e.what() << std::endl;
    std::cerr << activity_failure << std::endl;

    if (!can_log)
        return;

    /*
     * Now we can try to dump useful, but less user-friendly
     * information by interrogating the exception. Note that we must
     * catch by std::exception and cast the boost exception; if we
     * were to catch boost exception, we would not have access to the
     * what() method and thus could not provide the exception message
     * to the console.
     */
    const auto be(dynamic_cast<const boost::exception* const>(&e));
    if (!be)
        return;

    using boost::diagnostic_information;
    BOOST_LOG_SEV(lg, error) << err_prefix << diagnostic_information(*be);
    BOOST_LOG_SEV(lg, error) << activity_failure;
}

/**
 * @brief Executes the CLI workflow.
 */
int execute_cli_workflow(const int argc, const char* argv[],
    dogen::utility::log::scoped_lifecycle_manager& slm) {

    /*
     * Perform DI initialisation and obtain the parser.
     */
    using namespace dogen::cli;
    auto inj(injector_factory::make_injector());
    const auto p(inj.create<std::unique_ptr<command_line_parser>>());

    /*
     * Create the configuration from command line options.
     */
    const auto args(std::vector<std::string>(argv + 1, argv + argc));
    const auto ocfg(p->parse(args, std::cout, std::cerr));

    /*
     * If we have no configuration, then there is nothing to do. This
     * can only happen if the user requested some valid options such
     * as help or version; any errors at the command line level are
     * treated as exceptions, and all other cases must result in a
     * configuration object.
     */
    if (!ocfg)
        return EXIT_SUCCESS;

    /*
     * Since we have a configuration, we can now attempt to
     * initialise the logging subsystem.
     */
    const auto& cfg(*ocfg);
    slm.initialise(cfg.logging());

    /*
     * Log the configuration and command line arguments.
     */
    BOOST_LOG_SEV(lg, info) << "Command line arguments: " << args;
    BOOST_LOG_SEV(lg, debug) << "Configuration: " << cfg;

    /*
     * Now perform legacy initialisation. It uses logging so it must
     * be done after logging initialisation. FIXME: To be removed once
     * we move all to DI.
     */
    initializer::initialize();

    /*
     * Execute the application.
     */
    const auto app(inj.create<std::unique_ptr<application>>());
    app->run(cfg);
    return EXIT_SUCCESS;
}

}

int main(const int argc, const char* argv[]) {
    dogen::utility::log::scoped_lifecycle_manager slm;
    try {
        return execute_cli_workflow(argc, argv, slm);
    } catch (const dogen::cli::parser_exception& /*e*/) {
        /*
         * Reporting of these types of errors to the console has
         * already been handled by the parser itself.
         */
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        report_exception(slm.is_initialised(), e);
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << force_terminate << std::endl;
        return EXIT_FAILURE;
    }
}
