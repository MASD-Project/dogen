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
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.csharp/types/fabric/injector.hpp"
#include "dogen/quilt.csharp/types/fabric/external_expander.hpp"

namespace {

const std::string id("quilt.csharp.fabric.external_expander");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace fabric {

void external_expander::expand_injection(
    const annotations::type_repository& atrp,
    yarn::intermediate_model& im) const {
    injector i;
    i.inject(atrp, im);
}

std::string external_expander::id() const {
    return ::id;
}

void external_expander::expand(const annotations::type_repository& atrp,
    const dogen::formatters::decoration_properties_factory& /*dpf*/,
    yarn::intermediate_model& im) const {
    expand_injection(atrp, im);
}

} } } }
