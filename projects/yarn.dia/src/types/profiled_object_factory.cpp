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
#include "dogen/dia/types/object.hpp"
#include "dogen/dia/types/diagram.hpp"
#include "dogen/yarn.dia/types/profiler.hpp"
#include "dogen/yarn.dia/types/object_processor.hpp"
#include "dogen/yarn.dia/types/profiled_object_factory.hpp"

namespace dogen {
namespace yarn {
namespace dia {

processed_object profiled_object_factory::
make_processed_object(const dogen::dia::object& o) const {
    object_processor op;
    return op.process(o);
}

profile profiled_object_factory::
make_profile(const processed_object& po) const {
    profiler prf;
    return prf.generate(po);
}

std::list<profiled_object> profiled_object_factory::
make(const dogen::dia::diagram& d) const {
    std::list<profiled_object> r;
    for (const auto& l : d.layers()) {
        for (const auto& o : l.objects()) {
            const auto po(make_processed_object(o));
            const auto prf(make_profile(po));
            r.push_back(profiled_object(po, prf));
        }
    }
    return r;
}

} } }
