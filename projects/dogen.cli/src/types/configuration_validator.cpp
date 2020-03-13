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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen/types/invalid_configuration_exception.hpp"
#include "dogen/types/configuration_validator.hpp"
#include "dogen.cli/types/configuration_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cli.configuration_validator"));

const std::string missing_target("Mandatory parameter target is missing");
const std::string non_absolute_target("Target path is not absolute: ");
const std::string missing_output_dir(
    "You must supply the output directory path");
const std::string non_absolute_output(
    "The output directory path is not absolute: ");

using dogen::cli::configuration;
using dogen::cli::configuration_validator;
using dogen::cli::generation_configuration;
using dogen::cli::conversion_configuration;
using dogen::cli::dumpspecs_configuration;

class activity_dispatcher : public boost::static_visitor<> {
public:
    void operator()(const conversion_configuration& cfg) const {
        configuration_validator::validate(cfg);
    }

    void operator()(const generation_configuration& cfg) const {
        configuration_validator::validate(cfg);
    }

    void operator()(const dumpspecs_configuration&) const {
        // nothing to validate
    }
};

}

namespace dogen::cli {

void configuration_validator::validate(const generation_configuration& cfg) {
    BOOST_LOG_SEV(lg, info) << "Validating generation configuration.";

    /*
     * User must supply a path to the target.
     */
    const auto t(cfg.target());
    if (t.empty()) {
        BOOST_LOG_SEV(lg, error) << missing_target;
        BOOST_THROW_EXCEPTION(invalid_configuration_exception(missing_target));
    }

    /*
     * We require the target path supplied to us to be an absolute
     * path. This is because we perform calculations off of it such as
     * locating the reference models and so forth. The end-user is not
     * required to have supplied an absolute path, but someone above
     * us must be responsible for ensuring we receive an absolute
     * path.
     */
    auto gs(t.generic_string());
    if (!t.is_absolute()) {
        BOOST_LOG_SEV(lg, error) << non_absolute_target << gs;
        BOOST_THROW_EXCEPTION(
            invalid_configuration_exception(non_absolute_target + gs));
    }

    /*
     * User must supply a path to the output directory, or the system
     * must have defaulted it to something sensible.
     */
    const auto od(cfg.output_directory());
    if (od.empty()) {
        BOOST_LOG_SEV(lg, error) << missing_output_dir;
        BOOST_THROW_EXCEPTION(
            invalid_configuration_exception(missing_output_dir));
    }

    /*
     * As with the target, we also expect the output directory to be
     * absolute. This just makes our life easier in terms of
     * assumptions.
     */
    gs = od.generic_string();
    if (!od.is_absolute()) {
        BOOST_LOG_SEV(lg, error) << non_absolute_output << gs;
        BOOST_THROW_EXCEPTION(
            invalid_configuration_exception(non_absolute_output + gs));
    }
    BOOST_LOG_SEV(lg, info) << "Generation configuration is valid.";
}

void configuration_validator::
validate(const conversion_configuration& /*cfg*/) {
    // FIXME: implement validation
}

void configuration_validator::validate(const configuration& cfg) {
    BOOST_LOG_SEV(lg, debug) << "Validating configuration.";

    activity_dispatcher d;
    boost::apply_visitor(d, cfg.cli().activity());
    dogen::configuration_validator::validate(cfg.api());

    BOOST_LOG_SEV(lg, debug) << "Configuration is valid.";
}

}
