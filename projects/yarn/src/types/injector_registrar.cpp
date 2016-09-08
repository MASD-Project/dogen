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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/registrar_error.hpp"
#include "dogen/yarn/types/injector_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.injector_registrar"));

const std::string no_injectors("No injectors provided.");
const std::string null_frontend("Frontend supplied is null.");

}

namespace dogen {
namespace yarn {

void injector_registrar::
register_injector(std::shared_ptr<const injector_interface> inj) {
    // note: not logging by design
    if (!inj)
        BOOST_THROW_EXCEPTION(registrar_error(null_frontend));

    injectors_.push_back(inj);
}

void injector_registrar::validate() const {
    if (injectors_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_injectors;
        // FIXME:
        // BOOST_THROW_EXCEPTION(registrar_error(no_injectors));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";

    BOOST_LOG_SEV(lg, debug) << "Found "
                             << injectors_.size()
                             << " registered injectors. Details: ";

    for (const auto& inj : injectors_)
        BOOST_LOG_SEV(lg, debug) << "id: '" << inj->id() << "'";
}

std::list<std::shared_ptr<const injector_interface>>
injector_registrar::injectors() const {
    return injectors_;
}

} }
