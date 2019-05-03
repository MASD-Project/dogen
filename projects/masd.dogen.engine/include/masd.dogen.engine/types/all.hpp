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
#ifndef MASD_DOGEN_ENGINE_TYPES_ALL_HPP
#define MASD_DOGEN_ENGINE_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.engine/types/engine.hpp"
#include "masd.dogen.engine/types/traits.hpp"
#include "masd.dogen.engine/types/converter.hpp"
#include "masd.dogen.engine/types/generator.hpp"
#include "masd.dogen.engine/types/helpers/adapter.hpp"
#include "masd.dogen.engine/types/injector_factory.hpp"
#include "masd.dogen.engine/types/transforms/context.hpp"
#include "masd.dogen.engine/types/helpers/stereotypes_helper.hpp"
#include "masd.dogen.engine/types/transforms/context_factory.hpp"
#include "masd.dogen.engine/types/helpers/adaptation_exception.hpp"
#include "masd.dogen.engine/types/transforms/factory_exception.hpp"
#include "masd.dogen.engine/types/transforms/transform_exception.hpp"
#include "masd.dogen.engine/types/transforms/naming_configuration.hpp"
#include "masd.dogen.engine/types/transforms/code_generation_chain.hpp"
#include "masd.dogen.engine/types/transforms/scoped_context_manager.hpp"
#include "masd.dogen.engine/types/transforms/profile_binding_transform.hpp"
#include "masd.dogen.engine/types/helpers/stereotypes_conversion_result.hpp"
#include "masd.dogen.engine/types/transforms/profile_repository_transform.hpp"
#include "masd.dogen.engine/types/transforms/dynamic_stereotypes_transform.hpp"
#include "masd.dogen.engine/types/transforms/extraction_model_production_chain.hpp"
#include "masd.dogen.engine/types/transforms/profile_template_adaption_transform.hpp"
#include "masd.dogen.engine/types/transforms/injection_model_to_coding_model_transform.hpp"
#include "masd.dogen.engine/types/transforms/coding_model_to_generation_model_transform.hpp"
#include "masd.dogen.engine/types/transforms/injection_model_set_to_coding_model_set_chain.hpp"
#include "masd.dogen.engine/types/transforms/coding_model_set_to_configuration_model_set_transform.hpp"

#endif
