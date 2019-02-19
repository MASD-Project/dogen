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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/optional_io.hpp"
#include "masd.dogen/io/error_handling_configuration_io.hpp"
#include "masd.dogen/io/tracing_configuration_io.hpp"
#include "masd.dogen/io/diffing_configuration_io.hpp"
#include "masd.dogen/types/configuration_validator.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("configuration_validator"));

}

namespace masd::dogen {

void configuration_validator::
validate(const boost::optional<error_handling_configuration>& ocfg) {
    BOOST_LOG_SEV(lg, debug) << "Validating error handling configuration.";

    if (!ocfg) {
        BOOST_LOG_SEV(lg, debug) << "No configuration supplied.";
        return;
    }

    const auto& cfg(*ocfg);
    BOOST_LOG_SEV(lg, debug) << cfg;
    BOOST_LOG_SEV(lg, debug) << "Error handling configuration is valid.";
}

void configuration_validator::
validate(const boost::optional<tracing_configuration>& ocfg) {
    BOOST_LOG_SEV(lg, debug) << "Validating tracing configuration.";

    if (!ocfg) {
        BOOST_LOG_SEV(lg, debug) << "No configuration supplied.";
        return;
    }

    const auto& cfg(*ocfg);
    BOOST_LOG_SEV(lg, debug) << cfg;
    BOOST_LOG_SEV(lg, debug) << "Tracing configuration is valid.";
}

void configuration_validator::
validate(const boost::optional<diffing_configuration>& ocfg) {
    BOOST_LOG_SEV(lg, debug) << "Validating diffing configuration.";
    if (!ocfg) {
        BOOST_LOG_SEV(lg, debug) << "No configuration supplied.";
        return;
    }

    const auto& cfg(*ocfg);
    BOOST_LOG_SEV(lg, debug) << cfg;
    BOOST_LOG_SEV(lg, debug) << "Diffing configuration is valid.";
}

void configuration_validator::validate(const configuration& cfg) {
    BOOST_LOG_SEV(lg, debug) << "Validating API configuration.";

    validate(cfg.error_handling());
    validate(cfg.tracing());
    validate(cfg.diffing());

    BOOST_LOG_SEV(lg, debug) << "API configuration is valid.";
}

}
