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
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.modeling/io/transforms/options_io.hpp"
#include "masd.dogen.modeling/types/transforms/validation_error.hpp"
#include "masd.dogen.modeling/types/transforms/options_validator.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("yarn.transforms.options_validator"));

const std::string missing_target("Mandatory parameter target is missing");
const std::string non_absolute_target("Target path is not absolute: ");
const std::string missing_output_dir(
    "You must supply the output directory path");
const std::string non_absolute_output(
    "The output directory path is not absolute: ");

}

namespace masd::dogen::modeling::transforms {

void options_validator::validate(const options& o) {
    BOOST_LOG_SEV(lg, info) << "Validating options: " << o;

    /*
     * User must supply a path to the target.
     */
    const auto tp(o.target());
    if (tp.empty()) {
        BOOST_LOG_SEV(lg, error) << missing_target;
        BOOST_THROW_EXCEPTION(validation_error(missing_target));
    }

    /**
     * We require the target path supplied to us to be an absolute
     * path. This is because we perform calculations off of it such as
     * locating the reference models and so forth. The end-user is not
     * required to have supplied an absolute path, but someone above
     * us must be responsible for ensuring we receive an absolute
     * path.
     */
    auto gs(tp.generic_string());
    if (!tp.is_absolute()) {
        BOOST_LOG_SEV(lg, error) << non_absolute_target << gs;
        BOOST_THROW_EXCEPTION(validation_error(non_absolute_target + gs));
    }

    /*
     * User must supply a path to the output directory, or the system
     * must have defaulted it to something sensible.
     */
    const auto odp(o.output_directory_path());
    if (odp.empty()) {
        BOOST_LOG_SEV(lg, error) << missing_output_dir;
        BOOST_THROW_EXCEPTION(validation_error(missing_output_dir));
    }

    /*
     * As with the target, we also expect the output directory to be
     * absolute. This just makes our life easier in terms of
     * assumptions.
     */
    gs = odp.generic_string();
    if (!odp.is_absolute()) {
        BOOST_LOG_SEV(lg, error) << non_absolute_output << gs;
        BOOST_THROW_EXCEPTION(validation_error(non_absolute_output + gs));
    }

    BOOST_LOG_SEV(lg, info) << "Options are valid.";
}

}
