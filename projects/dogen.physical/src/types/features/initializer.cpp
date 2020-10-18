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
#include "dogen.physical/types/features/enablement.hpp"
#include "dogen.physical/types/features/filesystem.hpp"
#include "dogen.physical/types/features/formatting.hpp"
#include "dogen.physical/types/features/initializer.hpp"
#include "dogen.physical/types/features/path_features.hpp"
#include "dogen.physical/types/features/facet_features.hpp"
#include "dogen.physical/types/features/backend_features.hpp"
#include "dogen.physical/types/features/archetype_features.hpp"
#include "dogen.physical/types/features/directive_features.hpp"
#include "dogen.physical/types/features/inclusion_features.hpp"

namespace dogen::physical::features {

void initializer::
register_entities(variability::helpers::registrar& rg) {
    rg.register_templates(dogen::physical::features::archetype_features::make_templates());
    rg.register_templates(dogen::physical::features::backend_features::make_templates());
    rg.register_templates(dogen::physical::features::directive_features::make_templates());
    rg.register_templates(dogen::physical::features::enablement::make_templates());
    rg.register_templates(dogen::physical::features::facet_features::make_templates());
    rg.register_templates(dogen::physical::features::formatting::make_templates());
    rg.register_features(dogen::physical::features::filesystem::make_features());
    rg.register_features(dogen::physical::features::inclusion_features::make_features());
    rg.register_features(dogen::physical::features::path_features::make_features());
}

}
