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
#include "dogen/options/types/validation_error.hpp"
#include "dogen/options/types/knitting_options_validator.hpp"
#include "dogen/utility/log/logger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("options.knitting_options_validator"));

const std::string missing_target("Mandatory parameter target is missing");
const std::string missing_project_dir(
    "You must supply the project directory path for split projects");

}

namespace dogen {
namespace options {

void knitting_options_validator::validate(const knitting_options& o) {
    if (o.target().empty()) {
        BOOST_LOG_SEV(lg, error) << missing_target;
        BOOST_THROW_EXCEPTION(validation_error(missing_target));
    }

    if (o.project_directory_path().empty()) {
        BOOST_LOG_SEV(lg, error) << missing_project_dir;
        BOOST_THROW_EXCEPTION(validation_error(missing_project_dir));
    }
}

} }
