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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_ALL_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.variability/types/variability.hpp"
#include "masd.dogen.variability/types/meta_model/name.hpp"
#include "masd.dogen.variability/types/meta_model/text.hpp"
#include "masd.dogen.variability/types/meta_model/value.hpp"
#include "masd.dogen.variability/types/meta_model/number.hpp"
#include "masd.dogen.variability/types/meta_model/boolean.hpp"
#include "masd.dogen.variability/types/meta_model/element.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/profile.hpp"
#include "masd.dogen.variability/types/transforms/context.hpp"
#include "masd.dogen.variability/types/helpers/value_factory.hpp"
#include "masd.dogen.variability/types/meta_model/meta_model.hpp"
#include "masd.dogen.variability/types/meta_model/value_type.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/meta_model/binding_point.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.variability/types/meta_model/template_kind.hpp"
#include "masd.dogen.variability/types/meta_model/value_visitor.hpp"
#include "masd.dogen.variability/types/helpers/value_type_mapper.hpp"
#include "masd.dogen.variability/types/meta_model/binding_action.hpp"
#include "masd.dogen.variability/types/meta_model/key_value_pair.hpp"
#include "masd.dogen.variability/types/helpers/building_exception.hpp"
#include "masd.dogen.variability/types/meta_model/text_collection.hpp"
#include "masd.dogen.variability/types/helpers/hydration_exception.hpp"
#include "masd.dogen.variability/types/helpers/selection_exception.hpp"
#include "masd.dogen.variability/types/meta_model/feature_template.hpp"
#include "masd.dogen.variability/types/meta_model/profile_template.hpp"
#include "masd.dogen.variability/types/meta_model/potential_binding.hpp"
#include "masd.dogen.variability/types/helpers/configuration_factory.hpp"
#include "masd.dogen.variability/types/helpers/template_instantiator.hpp"
#include "masd.dogen.variability/types/meta_model/profile_repository.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_model.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_point.hpp"
#include "masd.dogen.variability/types/helpers/instantiation_exception.hpp"
#include "masd.dogen.variability/types/transforms/transformation_error.hpp"
#include "masd.dogen.variability/types/helpers/feature_template_hydrator.hpp"
#include "masd.dogen.variability/types/helpers/profile_template_hydrator.hpp"
#include "masd.dogen.variability/types/helpers/configuration_point_merger.hpp"
#include "masd.dogen.variability/types/helpers/feature_template_registrar.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_model_set.hpp"
#include "masd.dogen.variability/types/transforms/feature_model_transform.hpp"
#include "masd.dogen.variability/types/transforms/profile_binding_transform.hpp"
#include "masd.dogen.variability/types/transforms/profile_merging_transform.hpp"
#include "masd.dogen.variability/types/meta_model/feature_template_repository.hpp"
#include "masd.dogen.variability/types/meta_model/profile_template_repository.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_point_template.hpp"
#include "masd.dogen.variability/types/transforms/feature_model_production_chain.hpp"
#include "masd.dogen.variability/types/transforms/profile_repository_production_chain.hpp"
#include "masd.dogen.variability/types/transforms/feature_template_hydration_transform.hpp"
#include "masd.dogen.variability/types/transforms/global_configuration_binding_transform.hpp"
#include "masd.dogen.variability/types/transforms/feature_template_instantiation_transform.hpp"
#include "masd.dogen.variability/types/transforms/implicit_configuration_binding_transform.hpp"
#include "masd.dogen.variability/types/transforms/profile_template_instantiation_transform.hpp"

#endif
