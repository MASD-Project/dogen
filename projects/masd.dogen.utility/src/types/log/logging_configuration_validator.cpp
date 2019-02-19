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
#include <boost/throw_exception.hpp>
#include <boost/filesystem/operations.hpp>
#include "masd.dogen.utility/types/log/invalid_logging_configuration.hpp"
#include "masd.dogen.utility/types/log/logging_configuration_validator.hpp"

namespace {

const std::string no_logging("Must log to file and/or console");
const std::string unexpected_dir(
    "Output directory supplied without a file name.");

}

namespace masd::dogen::utility::log {

void logging_configuration_validator::
validate(const logging_configuration& cfg) {
    /*
     * We must have at least one form of logging, file or console.
     */
    const bool output_to_file(!cfg.filename().empty());
    if (!cfg.output_to_console() && !output_to_file)
        BOOST_THROW_EXCEPTION(invalid_logging_configuration(no_logging));

    /*
     * If the filename was not supplied, we do not expect the output
     * directory to have been supplied either, as its only applicable
     * to file logging.
     */
    if (cfg.filename().empty() && !cfg.output_directory().empty())
        BOOST_THROW_EXCEPTION(invalid_logging_configuration(unexpected_dir));
}

}
