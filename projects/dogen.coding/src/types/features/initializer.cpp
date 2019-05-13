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
#include "dogen.coding/types/features/orm.hpp"
#include "dogen.coding/types/features/naming.hpp"
#include "dogen.coding/types/features/origin.hpp"
#include "dogen.coding/types/features/primitive.hpp"
#include "dogen.coding/types/features/enumerator.hpp"
#include "dogen.coding/types/features/enumeration.hpp"
#include "dogen.coding/types/features/initializer.hpp"
#include "dogen.coding/types/features/generalization.hpp"
#include "dogen.coding/types/features/type_parameters.hpp"
#include "dogen.coding/types/features/decoration_modeline.hpp"
#include "dogen.coding/types/features/variability_templates.hpp"
#include "dogen.coding/types/features/output_technical_space.hpp"

namespace dogen::coding::features {

void initializer::
register_templates(variability::helpers::feature_template_registrar& rg) {
    rg.register_templates(dogen::coding::features::decoration_modeline::make_templates());
    rg.register_templates(dogen::coding::features::enumeration::make_templates());
    rg.register_templates(dogen::coding::features::enumerator::make_templates());
    rg.register_templates(dogen::coding::features::generalization::make_templates());
    rg.register_templates(dogen::coding::features::naming::make_templates());
    rg.register_templates(dogen::coding::features::origin::make_templates());
    rg.register_templates(dogen::coding::features::orm::make_templates());
    rg.register_templates(dogen::coding::features::output_technical_space::make_templates());
    rg.register_templates(dogen::coding::features::primitive::make_templates());
    rg.register_templates(dogen::coding::features::type_parameters::make_templates());
    rg.register_templates(dogen::coding::features::variability_templates::make_templates());

}

}
