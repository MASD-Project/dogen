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
#include "dogen/utility/log/life_cycle_manager.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/config/version.hpp"
#include "dogen/driver/program_options_parser.hpp"
#include "dogen/generator/config/settings.hpp"
#include "dogen/generator/generator.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("dogen"));
const std::string log_dir("log/dogen");

/**
 * @brief Print the program's help text.
 */
void help(const std::string& d) {
    std::cout << "Dogen - the domain generator." << std::endl
              << "Generates domain objects from a Dia diagram."
              << std::endl << std::endl << d << std::endl;
}

/**
 * @brief Print the program's version details.
 */
void version() {
    std::cout << "dogen v" << DOGEN_VERSION << std::endl
              << "Copyright (C) 2012 Kitanda." << std::endl
              << "Licence: Kitanda Proprietary Software Licence."
              << std::endl;
}

/**
 * @brief Given the main arguments, generates the Dogen settings.
 */
boost::optional<dogen::generator::config::settings>
settings_factory(int argc, char* argv[]) {
    dogen::driver::program_options_parser p(argc, argv);
    p.help_function(help);
    p.version_function(version);
    return p.parse();
}

/**
 * @brief Given Dogen's settings, creates a code generator.
 */
dogen::generator::generator
code_generator_factory(const dogen::generator::config::settings& s) {
    if (!s.output().output_to_stdout())
        return dogen::generator::generator(s);

    auto lambda([]() -> std::ostream& {return std::cout;});
    return dogen::generator::generator(s, lambda);
}

/**
 * @brief Performs the initialisation of logging system.
 */
void initialise_logging(const dogen::generator::config::settings& s) {
    life_cycle_manager lcm;
    const bool v(s.troubleshooting().verbose());
    lcm.initialise(log_dir, v ? severity_level::debug : severity_level::info);
}

}

int main(int argc, char* argv[]) {
    try {
        const auto o(settings_factory(argc, argv));
        if (o) {
            const auto& s(*o);
            initialise_logging(s);
            auto cg(code_generator_factory(s));
            cg.generate();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        BOOST_LOG_SEV(lg, fatal) << e.what();
        return 1;
    }
    return 0;
}
