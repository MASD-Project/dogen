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
#include <boost/variant.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen/types/specs.hpp"
#include "dogen.cli/types/configuration_validator.hpp"
#include "dogen.cli/types/application_exception.hpp"
#include "dogen.cli/types/application.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cli.application"));

using dogen::generator;
using dogen::converter;
using dogen::spec_dumper;
using dogen::cli::configuration;
using dogen::cli::application_exception;
using dogen::cli::generation_configuration;
using dogen::cli::conversion_configuration;
using dogen::cli::dumpspecs_configuration;

void print_specs(const dogen::specs& s) {
    if (s.groups().empty()) {
        std::cout << "No specs found" << std::endl;
        return;
    }

    bool is_first(true);
    for (const auto& g : s.groups()) {
        if (!is_first)
            std::cout << std::endl;

        std::cout << "Group: " << g.name() << std::endl
                  << "Purpose: " << g.description() << std::endl;

        for (const auto& e : g.entries()) {
            std::cout << "    " << e.name() << ": "
                      << e.description() << std::endl;
        }
        is_first = false;
    }
}

/**
 * @brief Given the configuration selected by the user, dispatches to
 * the appropriate activity.
 */
class activity_dispatcher : public boost::static_visitor<> {
public:
    activity_dispatcher(const converter& c, const generator& g,
        const spec_dumper& sd, const configuration& cfg)
        : converter_(c), generator_(g), dumper_(sd), configuration_(cfg) {}

public:
    /**
     * @brief Dispatches to the converter.
     */
    void operator()(const conversion_configuration& cfg) const {
        converter_.convert(configuration_.api(), cfg.source(),
            cfg.destination());
    }

    /**
     * @brief Dispatches to the generator.
     */
    void operator()(const generation_configuration& cfg) const {
        generator_.generate(configuration_.api(), cfg.target(),
            cfg.output_directory());
    }

    /**
     * @brief Dispatches to the spec dumper.
     */
    void operator()(const dumpspecs_configuration&) const {
        const auto s(dumper_.dump(configuration_.api()));
        print_specs(s);
    }

private:
    const converter& converter_;
    const generator& generator_;
    const spec_dumper& dumper_;
    const configuration& configuration_;
};

}

namespace dogen::cli {

application::
application(const converter& c, const generator& g, const spec_dumper& sd)
    : converter_(c), generator_(g), dumper_(sd) {}

void application::run(const configuration& cfg) const {
    BOOST_LOG_SEV(lg, debug) << "Application started.";

    /*
     * Before anything else, lets make sure the configuration makes
     * sense. No point in proceeding otherwise.
     */
    configuration_validator::validate(cfg);
    activity_dispatcher d(converter_, generator_, dumper_, cfg);
    boost::apply_visitor(d, cfg.cli().activity());

    BOOST_LOG_SEV(lg, debug) << "Application finished.";
}

}
