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
#include "masd.dogen.coding/types/transforms/context_factory.hpp"
#include "masd.dogen.coding/test/mock_context_factory.hpp"

namespace masd::dogen::coding::test {

transforms::context mock_context_factory::make() {
    masd::dogen::coding::transforms::options o;
    using masd::dogen::coding::transforms::context_factory;

    annotations::archetype_location_repository alrp;
    std::unordered_map<
        std::string,
        coding::meta_model::intra_backend_segment_properties> ibsp;
    const auto r(context_factory::make(alrp, ibsp, o, false/*enable_validation*/));
    return r;
}

}
