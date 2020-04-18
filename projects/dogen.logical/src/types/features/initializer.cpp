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
#include "dogen.logical/types/features/orm.hpp"
#include "dogen.logical/types/features/origin.hpp"
#include "dogen.logical/types/features/mapping.hpp"
#include "dogen.logical/types/features/physical.hpp"
#include "dogen.logical/types/features/primitive.hpp"
#include "dogen.logical/types/features/enumerator.hpp"
#include "dogen.logical/types/features/enumeration.hpp"
#include "dogen.logical/types/features/initializer.hpp"
#include "dogen.logical/types/features/generalization.hpp"
#include "dogen.logical/types/features/type_parameters.hpp"
#include "dogen.logical/types/features/variability_bundle.hpp"
#include "dogen.logical/types/features/decoration_modeline.hpp"
#include "dogen.logical/types/features/variability_templates.hpp"
#include "dogen.logical/types/features/output_technical_space.hpp"

namespace dogen::logical::features {

void initializer::
register_entities(variability::helpers::registrar& rg) {
    rg.register_features(dogen::logical::features::decoration_modeline::make_features());
    rg.register_features(dogen::logical::features::enumeration::make_features());
    rg.register_features(dogen::logical::features::enumerator::make_features());
    rg.register_features(dogen::logical::features::generalization::make_features());
    rg.register_features(dogen::logical::features::mapping::make_features());
    rg.register_features(dogen::logical::features::origin::make_features());
    rg.register_features(dogen::logical::features::orm::make_features());
    rg.register_features(dogen::logical::features::output_technical_space::make_features());
    rg.register_features(dogen::logical::features::physical::make_features());
    rg.register_features(dogen::logical::features::primitive::make_features());
    rg.register_features(dogen::logical::features::type_parameters::make_features());
    rg.register_features(dogen::logical::features::variability_bundle::make_features());
    rg.register_features(dogen::logical::features::variability_templates::make_features());
}

}
