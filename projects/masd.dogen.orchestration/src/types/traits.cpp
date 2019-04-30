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
#include "masd.dogen.orchestration/types/traits.hpp"

namespace masd::dogen::orchestration {

std::string traits::variability::binding_point() {
    static std::string r("masd.variability.binding_point");
    return r;
}

std::string traits::variability::labels() {
    static std::string r("masd.variability.labels");
    return r;
}

std::string traits::variability::archetype_location_kernel() {
    static std::string r("masd.variability.archetype_location.kernel");
    return r;
}

std::string traits::variability::archetype_location_backend() {
    static std::string r("masd.variability.archetype_location.backend");
    return r;
}

std::string traits::variability::template_kind() {
    static std::string r("masd.variability.template_kind");
    return r;
}

}
