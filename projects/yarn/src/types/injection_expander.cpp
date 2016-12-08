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
#include "dogen/yarn/types/injection_error.hpp"
#include "dogen/yarn/types/injection_expander.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.injection_expander"));

}

namespace dogen {
namespace yarn {

void injection_expander::
expand(const annotations::type_repository& atrp,
    const annotations::annotation& ra, const injector_registrar& rg,
    intermediate_model& m) {

    const auto id(m.name().id());
    BOOST_LOG_SEV(lg, debug) << "Performing injection expansion on: " << id;

    for (const auto& inj : rg.injectors())
        inj->inject(atrp, ra, m);

    BOOST_LOG_SEV(lg, debug) << "Finished performing injection expansion.";
}

} }
