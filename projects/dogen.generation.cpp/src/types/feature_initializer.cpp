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
#include "dogen.generation.cpp/types/feature_initializer.hpp"
#include "dogen.generation.cpp/types/formatters/global_features.hpp"
#include "dogen.generation.cpp/types/formatters/archetype_features.hpp"

namespace dogen::generation::cpp {

void feature_initializer::
register_entities(variability::helpers::registrar& rg) {
    rg.register_templates(dogen::generation::cpp::formatters::archetype_features::make_templates());
    rg.register_features(dogen::generation::cpp::formatters::global_features::make_features());
}

}
