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
#include <iostream>
#include <boost/di.hpp>
#include "masd.dogen.cli/types/application.hpp"
#include "masd.dogen.cli/types/program_options_parser.hpp"
#include "masd.dogen.cli/types/command_line_parser.hpp"
#include "masd.dogen.cli/types/injector_factory.hpp"

using masd::dogen::cli::program_options_parser;
using masd::dogen::cli::command_line_parser;
using masd::dogen::cli::application;

int main(const int /*argc*/, const char* /*argv*/[]) {
    // const auto args(std::vector<std::string>(argv + 1, argv + argc));
    // masd::dogen::cli::program_options_parser pop;
    // masd::dogen::cli::application a(pop);
    // a.run(args, std::cout, std::cerr);

    // auto injector = masd::dogen::cli::injector_factory::make_injector();
    // auto injector = boost::di::make_injector(
    //     boost::di::bind<masd::dogen::cli::command_line_parser>.
    //     to<masd::dogen::cli::program_options_parser>()
    //     );

    // const auto a(injector.create<masd::dogen::cli::application>());
    // a.run(args, std::cout, std::cerr);
    // auto injector = di::make_injector();
    // injector.create<app>();
    auto injector = boost::di::make_injector(
        boost::di::bind<command_line_parser>.to<program_options_parser>());
    auto app_ = injector.create<application>();
    (void)app_;
    return 0;
}
