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
#include <iostream>
#include <boost/exception/diagnostic_information.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/log/severity_level.hpp"
#include "masd.dogen.utility/types/log/lifecycle_manager.hpp"
#include "masd.dogen.cli/types/application.hpp"
#include "masd.dogen/types/configuration.hpp"
#include "masd.dogen/io/configuration_io.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("knitter"));

const std::string log_file_prefix("masd.dogen.cli.");

}

namespace masd::dogen::cli {

application::application(const command_line_parser& clp)
    : command_line_parser_(clp) { }

void application::execute(const std::vector<std::string>& args,
    std::ostream& info, std::ostream& error) const {
    const auto ocfg(command_line_parser_.parse(args, info, error));
    if (!ocfg)
        return;

    const auto& cfg(*ocfg);
    std::cout << cfg << std::endl;
}

int application::run(const std::vector<std::string>& args,
    std::ostream& info, std::ostream& error) const {
    try {
        execute(args, info, error);
        return EXIT_SUCCESS;
    } catch(const std::exception& e) {
        info << "failure, errors: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

}
