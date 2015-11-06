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
#include "dogen/yarn/types/modules_expander.hpp"
#include "dogen/yarn/types/properties_expander.hpp"
#include "dogen/yarn/types/expander.hpp"

namespace dogen {
namespace yarn {

void expander::expand_modules(intermediate_model& m) const {
    modules_expander e;
    e.expand(m);
}

void expander::expand_properties(intermediate_model& m) const {
    properties_expander e;
    e.expand(m);
}

void expander::expand(intermediate_model& m) const {
    expand_modules(m);
    expand_properties(m);
}

} }
