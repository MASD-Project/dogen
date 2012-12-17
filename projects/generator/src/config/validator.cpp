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
#include <boost/throw_exception.hpp>
#include "dogen/generator/config/configuration_error.hpp"
#include "dogen/generator/config/validator.hpp"
#include "dogen/utility/log/logger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("validator"));

const std::string missing_target("Mandatory parameter target is missing");
const std::string missing_source_include(
    "You must supply source and include directories for split projects");
const std::string missing_project_dir(
    "You must supply the project directory for split projects");
const std::string unexpected_source_include(
    "Source and include directories cannot be used with non-split projects");
const std::string unexpected_project_dir(
    "Project directories cannot be used with split projects");

}

namespace dogen {
namespace generator {
namespace config {

void validator::validate(const settings& s) {
    if (s.modeling().target().empty()) {
        BOOST_LOG_SEV(lg, error) << missing_target;
        BOOST_THROW_EXCEPTION(configuration_error(missing_target));
    }

    const auto cpp(s.cpp());
    if (cpp.split_project()) {
        if (cpp.include_directory().empty() || cpp.source_directory().empty()) {
            BOOST_LOG_SEV(lg, error) << missing_source_include;
            BOOST_THROW_EXCEPTION(configuration_error(missing_source_include));
        }

        if (!cpp.project_directory().empty()) {
            BOOST_LOG_SEV(lg, error) << unexpected_project_dir;
            BOOST_THROW_EXCEPTION(configuration_error(unexpected_project_dir));
        }
    } else {
        if (!cpp.include_directory().empty() || !cpp.source_directory().empty()) {
            BOOST_LOG_SEV(lg, error) << unexpected_source_include;
            BOOST_THROW_EXCEPTION(configuration_error(unexpected_source_include));
        }

        if (cpp.project_directory().empty()) {
            BOOST_LOG_SEV(lg, error) << missing_project_dir;
            BOOST_THROW_EXCEPTION(configuration_error(missing_project_dir));
        }
    }
}

} } }
