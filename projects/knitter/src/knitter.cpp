/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <iostream>
#include <boost/exception/diagnostic_information.hpp>
#include "dogen/utility/log/life_cycle_manager.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/config/version.hpp"
#include "dogen/knitter/program_options_parser.hpp"
#include "dogen/knitter/parser_validation_error.hpp"
#include "dogen/config/types/settings.hpp"
#include "dogen/knit/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("knitter"));
const std::string log_file("log/dogen_knitter");
const std::string get_help("Use --help option to see usage instructions.");
const std::string knitter_product("Dogen Knitter v" DOGEN_VERSION);
const std::string usage_error_msg("Usage error: ");
const std::string fatal_error_msg("Fatal Error: " );
const std::string log_file_msg("See the log file for details: ");
const std::string errors_msg(" finished with errors.");


/**
 * @brief Print the program's help text.
 */
void help(const std::string& d) {
    std::cout << "Dogen Knitter." << std::endl
              << "Generates domain objects from a Dia diagram."
              << std::endl << std::endl << d << std::endl;
}

/**
 * @brief Print the program's version details.
 */
void version() {
    std::cout << knitter_product << std::endl
              << "Copyright (C) 2012 Kitanda." << std::endl
              << "License: GPLv3 - GNU GPL version 3 or later "
              << "<http://gnu.org/licenses/gpl.html>."
              << std::endl;
}

/**
 * @brief Given the main arguments, generates the Dogen settings.
 */
boost::optional<dogen::config::settings>
settings_factory(int argc, char* argv[]) {
    dogen::knitter::program_options_parser p(argc, argv);
    p.help_function(help);
    p.version_function(version);
    return p.parse();
}

/**
 * @brief Given Knitters's settings, creates a code generation
 * workflow.
 */
dogen::knit::workflow workflow_factory(const dogen::config::settings& s) {
    if (!s.output().output_to_stdout())
        return dogen::knit::workflow(s);

    auto lambda([]() -> std::ostream& {return std::cout;});
    return dogen::knit::workflow(s, lambda);
}

/**
 * @brief Performs the initialisation of logging system.
 */
void initialise_logging(const dogen::config::settings& s) {
    life_cycle_manager lcm;
    const bool v(s.troubleshooting().verbose());
    lcm.initialise(log_file, v ? severity_level::debug : severity_level::info);
}

}

int main(int argc, char* argv[]) {
    bool can_log(false);
    try {
        const auto o(settings_factory(argc, argv));
        if (o) {
            const auto& s(*o);
            initialise_logging(s);
            can_log = true;
            BOOST_LOG_SEV(lg, info) << knitter_product << " started.";
            auto w(workflow_factory(s));
            w.execute();
            BOOST_LOG_SEV(lg, info) << knitter_product << " finished.";
        }
    } catch (const dogen::knitter::parser_validation_error& e) {
        // log known not to be initialised as we are still parsing
        // command line options.
        std::cerr << usage_error_msg << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        // we must catch by std::exception and cast the boost
        // exception here; if we were to catch boost exception, we
        // would not have access to the what() method and thus could
        // not provide a user-friendly message to the console.
        const auto be(dynamic_cast<const boost::exception* const>(&e));
        if (be && can_log) {
            BOOST_LOG_SEV(lg, fatal) << "Error: "
                                     << boost::diagnostic_information(*be);
        }

        std::cerr << "Error: " << e.what() << ". See the log file for details."
                  << std::endl;

        if (can_log)
            BOOST_LOG_SEV(lg, warn) << knitter_product << errors_msg;

        return 1;
    }
    return 0;
}
