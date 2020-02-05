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
    fluent = 1,
    immutable = 2,
    visitable = 3,
    structural_object = 4,
    structural_object_template = 5,
    structural_exception = 6,
    structural_primitive = 7,
    structural_enumeration = 8,
    structural_module = 9,
    structural_builtin = 10,
    structural_entry_point = 11,
    orm_object = 12,
    orm_value = 13,
    decoration_modeline_group = 14,
    decoration_modeline = 15,
    decoration_generation_marker = 16,
    decoration_licence = 17,
    variability_profile_template = 18,
    variability_feature_bundle = 19,
    variability_feature_template_initializer = 20,
    mapping_fixed_mappable = 21,
    mapping_extensible_mappable = 22,
    templating_logic_less_template = 23,
    serialization_type_registrar = 24,
    build_visual_studio_solution = 25,
    build_visual_studio_project = 26
};

}

#endif
