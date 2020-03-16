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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_STATIC_STEREOTYPES_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_STATIC_STEREOTYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::logical::meta_model {

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
    structural_assistant = 12,
    orm_object = 13,
    orm_value = 14,
    decoration_modeline_group = 15,
    decoration_modeline = 16,
    decoration_generation_marker = 17,
    decoration_licence = 18,
    variability_profile = 19,
    variability_profile_template = 20,
    variability_feature_bundle = 21,
    variability_feature_template_bundle = 22,
    variability_initializer = 23,
    mapping_fixed_mappable = 24,
    mapping_extensible_mappable = 25,
    templating_logic_less_template = 26,
    serialization_type_registrar = 27,
    visual_studio_solution = 28,
    visual_studio_project = 29,
    visual_studio_msbuild_targets = 30,
    orm_common_odb_options = 31,
    build_cmakelists = 32
};

}

#endif
