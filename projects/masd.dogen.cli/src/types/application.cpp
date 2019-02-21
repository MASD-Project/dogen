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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.orchestration/types/weaver.hpp"
#include "masd.dogen.orchestration/types/generator.hpp"
#include "masd.dogen.orchestration/types/converter.hpp"
#include "masd.dogen.cli/types/configuration_validator.hpp"
#include "masd.dogen.cli/types/application_exception.hpp"
#include "masd.dogen.cli/types/application.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("cli.application"));

using masd::dogen::orchestration::weaver;
using masd::dogen::orchestration::generator;
using masd::dogen::orchestration::converter;
using masd::dogen::cli::configuration;
using masd::dogen::cli::application_exception;
using masd::dogen::cli::generation_configuration;
using masd::dogen::cli::weaving_configuration;
using masd::dogen::cli::conversion_configuration;

class execute_activity : public boost::static_visitor<> {
public:
    explicit execute_activity(const configuration& cfg)
        : configuration_(cfg) {}

public:
    void operator()(const generation_configuration& cfg) const {
        generator g;
        g.generate(configuration_.api(), cfg.target(),
            cfg.output_directory(),
            configuration_.cli().tracing_output_directory());
    }

    void operator()(const weaving_configuration& cfg) const {
        weaver w;
        w.weave(configuration_.api(), cfg.target(),
            configuration_.cli().tracing_output_directory());
    }

    void operator()(const conversion_configuration& cfg) const {
        converter c;
        c.convert(configuration_.api(), cfg.source(), cfg.destination(),
            configuration_.cli().tracing_output_directory());
    }

private:
    const configuration& configuration_;
};

}

namespace masd::dogen::cli {

void application::run(const configuration& cfg) const {
    BOOST_LOG_SEV(lg, debug) << "Application started.";

    configuration_validator::validate(cfg);
    boost::apply_visitor(execute_activity(cfg), cfg.cli().activity());

    BOOST_LOG_SEV(lg, debug) << "Application finished.";
}

}
