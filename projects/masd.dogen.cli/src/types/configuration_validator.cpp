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
#include "masd.dogen/types/configuration_validator.hpp"
#include "masd.dogen.cli/types/configuration_validator.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("cli.configuration_validator"));

}

namespace masd::dogen::cli {

void configuration_validator::validate(const configuration& cfg) {
    BOOST_LOG_SEV(lg, debug) << "Validating configuration.";

    masd::dogen::configuration_validator::validate(cfg.api());

    BOOST_LOG_SEV(lg, debug) << "Configuration is valid.";
}

}
