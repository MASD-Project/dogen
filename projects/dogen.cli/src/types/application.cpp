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
#include <boost/variant.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
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

class activity_dispatcher : public boost::static_visitor<> {
public:
    activity_dispatcher(const converter& c, const generator& g,
        const spec_dumper& sd, const configuration& cfg)
        : converter_(c), generator_(g), dumper_(sd), configuration_(cfg) {}

public:
    void operator()(const conversion_configuration& cfg) const {
        converter_.convert(configuration_.api(), cfg.source(),
            cfg.destination());
    }

    void operator()(const generation_configuration& cfg) const {
        generator_.generate(configuration_.api(), cfg.target(),
            cfg.output_directory());
    }

    void operator()(const dumpspecs_configuration&) const {
        dumper_.dump(configuration_.api());
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
