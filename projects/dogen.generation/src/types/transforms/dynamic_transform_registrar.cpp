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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.generation/types/transforms/registrar_error.hpp"
#include "dogen.generation/types/transforms/dynamic_transform_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("generation.transforms.dynamic_transform_registrar"));

const std::string no_transforms("No transforms provided.");
const std::string null_frontend("Frontend supplied is null.");

}

namespace dogen::generation::transforms {

void dynamic_transform_registrar::register_dynamic_transform(
    std::shared_ptr<const dynamic_transform_interface> dt) {
    if (!dt) {
        BOOST_LOG_SEV(lg, error) << null_frontend;
        BOOST_THROW_EXCEPTION(registrar_error(null_frontend));
    }

    transforms_.push_back(dt);

    BOOST_LOG_SEV(lg, debug) << "Registrered external transform: " << dt->id();
}

void dynamic_transform_registrar::validate() const {
    if (transforms_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_transforms;
        // BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";

    BOOST_LOG_SEV(lg, debug) << "Found "
                             << transforms_.size()
                             << " registered external transforms. Details: ";

    for (const auto& dt : transforms_)
        BOOST_LOG_SEV(lg, debug) << "id: '" << dt->id() << "'";
}

std::list<std::shared_ptr<const dynamic_transform_interface>>
dynamic_transform_registrar::dynamic_transforms() const {
    return transforms_;
}

}
