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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_STATIC_STEREOTYPES_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_STATIC_STEREOTYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::assets::meta_model {

/**
 * @brief Lists all stereotypes defined in the masd UML profile.
 */
enum class static_stereotypes : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    object = 1,
    object_template = 2,
    exception = 3,
    primitive = 4,
    enumeration = 5,
    module = 6,
    builtin = 7,
    visitable = 8,
    fluent = 9,
    immutable = 10,
    orm_object = 11,
    orm_value = 12,
    modeline_group = 13,
    modeline = 14,
    generation_marker = 15,
    licence = 16,
    variability_profile_template = 17,
    variability_feature_bundle = 18,
    variability_feature_template_initializer = 19,
    mapping_fixed_mappable = 20,
    mapping_extensible_mappable = 21,
    templating_logic_less_template = 22,
    serialization_type_registrar = 23,
    build_visual_studio_project = 24,
    build_visual_studio_solution = 25
};

}

#endif
