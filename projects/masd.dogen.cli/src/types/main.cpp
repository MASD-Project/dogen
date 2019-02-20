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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/log/severity_level.hpp"
#include "masd.dogen.utility/types/log/logging_configuration.hpp"
#include "masd.dogen.utility/types/log/scoped_lifecycle_manager.hpp"
#include "masd.dogen.cli/types/initializer.hpp"
#include "masd.dogen.cli/types/application.hpp"
#include "masd.dogen.cli/types/injector_factory.hpp"
#include "masd.dogen.cli/types/parser_exception.hpp"
#include "masd.dogen.cli/types/command_line_parser.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("main"));

const std::string err_prefix("Error: ");
const std::string gen_failure("Failed to generate model.");
const std::string force_terminate("dogen.cli was forced to terminate.");

void report_exception(const bool can_log, const std::exception& e) {
    /*
     * Dump to the console first.
     */
    std::cerr << err_prefix << e.what() << std::endl;
    std::cerr << gen_failure << std::endl;

    if (!can_log)
        return;

    /*
     * We must catch by std::exception and cast the boost exception
     * here; if we were to catch boost exception, we would not have
     * access to the what() method and thus could not provide a
     * user-friendly message to the console.
     */
    const auto be(dynamic_cast<const boost::exception* const>(&e));
    if (!be)
        return;

    using boost::diagnostic_information;
    BOOST_LOG_SEV(lg, error) << err_prefix << diagnostic_information(*be);
    BOOST_LOG_SEV(lg, error) << gen_failure;
}

}

int main(const int argc, const char* argv[]) {
    using namespace masd::dogen::cli;
    using masd::dogen::utility::log::scoped_lifecycle_manager;
    scoped_lifecycle_manager slm;

    try {
        /*
         * Perform DI initialisation and obtain the parser.
         */
        auto inj(injector_factory::make_injector());
        const auto clp(inj.create<std::unique_ptr<command_line_parser>>());

        /*
         * Create the configuration from command line options.
         */
        const auto args(std::vector<std::string>(argv + 1, argv + argc));
        const auto ocfg(clp->parse(args, std::cout, std::cerr));

        /*
         * If we have no configuration, then there is nothing to
          * do. This can only happen if the user requested some valid
          * options such as help or version; any errors at the command
          * line level are treated as exceptions, and all other cases
          * must result in a configuration object.
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
         * Now perform legacy initialisation. It uses logging so it
         * must be done after logging initialisation. FIXME: To be
         * removed once we move all to DI.
         */
        initializer::initialize();

        /*
         * Finally, we can execute the application.
         */
        application app;
        app.run(cfg);
    } catch (const parser_exception& /*e*/) {
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
    return EXIT_SUCCESS;
}
