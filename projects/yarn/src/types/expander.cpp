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
<<<<<<< 24090da86c0fe4a597dfa9c7b5e3ed377e4b57f4:projects/tack/src/types/expander.cpp
#include "dogen/tack/types/modules_expander.hpp"
#include "dogen/tack/types/properties_expander.hpp"
#include "dogen/tack/types/references_expander.hpp"
#include "dogen/tack/types/expander.hpp"
=======
#include "dogen/yarn/types/properties_expander.hpp"
#include "dogen/yarn/types/expander.hpp"
>>>>>>> rename tack to yarn:projects/yarn/src/types/expander.cpp

namespace dogen {
namespace yarn {

void expander::expand_properties(model& m) const {
    properties_expander e;
    e.expand(m);
}

void expander::expand_modules(model& m) const {
    modules_expander e;
    e.expand(m);
}

void expander::expand_references(model& m) const {
    references_expander e;
    e.expand(m);
}

void expander::expand(model& m) const {
    expand_properties(m);
    expand_modules(m);
    expand_references(m);
}

} }
