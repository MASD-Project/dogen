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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_META_NAME_FACTORY_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_META_NAME_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.logical/types/entities/name.hpp"

namespace dogen::logical::helpers {

class meta_name_factory final {
private:
    static entities::location make_location();
    static entities::name make_name(const std::string& sn);

public:
    static entities::name make_model_name();

    static entities::name make_module_name();
    static entities::name make_object_template_name();
    static entities::name make_builtin_name();
    static entities::name make_enumeration_name();
    static entities::name make_primitive_name();
    static entities::name make_object_name();
    static entities::name make_exception_name();
    static entities::name make_visitor_name();
    static entities::name make_assistant_name();
    static entities::name make_entry_point_name();
    static entities::name make_licence_name();
    static entities::name make_modeline_name();
    static entities::name make_modeline_group_name();
    static entities::name make_generation_marker_name();
    static entities::name make_variability_profile_name();
    static entities::name make_variability_profile_template_name();
    static entities::name make_variability_feature_template_bundle_name();
    static entities::name make_variability_feature_bundle_name();
    static entities::name make_variability_initializer_name();
    static entities::name make_templating_logic_less_templates_name();
    static entities::name make_serialization_type_registrar_name();
    static entities::name make_visual_studio_solution_name();
    static entities::name make_visual_studio_project_name();
    static entities::name make_visual_studio_msbuild_targets_name();
    static entities::name make_orm_common_odb_options_name();
    static entities::name make_build_cmakelists_name();
};

}

#endif
