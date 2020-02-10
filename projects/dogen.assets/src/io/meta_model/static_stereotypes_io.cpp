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
#include <string>
#include <ostream>
#include <stdexcept>
#include "dogen.assets/io/meta_model/static_stereotypes_io.hpp"

namespace dogen::assets::meta_model {

std::ostream& operator<<(std::ostream& s, const static_stereotypes& v) {
    s << "{ " << "\"__type__\": " << "\"static_stereotypes\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case static_stereotypes::invalid:
        attr = "\"invalid\"";
        break;
    case static_stereotypes::fluent:
        attr = "\"fluent\"";
        break;
    case static_stereotypes::immutable:
        attr = "\"immutable\"";
        break;
    case static_stereotypes::visitable:
        attr = "\"visitable\"";
        break;
    case static_stereotypes::structural_object:
        attr = "\"structural_object\"";
        break;
    case static_stereotypes::structural_object_template:
        attr = "\"structural_object_template\"";
        break;
    case static_stereotypes::structural_exception:
        attr = "\"structural_exception\"";
        break;
    case static_stereotypes::structural_primitive:
        attr = "\"structural_primitive\"";
        break;
    case static_stereotypes::structural_enumeration:
        attr = "\"structural_enumeration\"";
        break;
    case static_stereotypes::structural_module:
        attr = "\"structural_module\"";
        break;
    case static_stereotypes::structural_builtin:
        attr = "\"structural_builtin\"";
        break;
    case static_stereotypes::structural_entry_point:
        attr = "\"structural_entry_point\"";
        break;
    case static_stereotypes::orm_object:
        attr = "\"orm_object\"";
        break;
    case static_stereotypes::orm_value:
        attr = "\"orm_value\"";
        break;
    case static_stereotypes::decoration_modeline_group:
        attr = "\"decoration_modeline_group\"";
        break;
    case static_stereotypes::decoration_modeline:
        attr = "\"decoration_modeline\"";
        break;
    case static_stereotypes::decoration_generation_marker:
        attr = "\"decoration_generation_marker\"";
        break;
    case static_stereotypes::decoration_licence:
        attr = "\"decoration_licence\"";
        break;
    case static_stereotypes::variability_profile_template:
        attr = "\"variability_profile_template\"";
        break;
    case static_stereotypes::variability_feature_bundle:
        attr = "\"variability_feature_bundle\"";
        break;
    case static_stereotypes::variability_feature_template_initializer:
        attr = "\"variability_feature_template_initializer\"";
        break;
    case static_stereotypes::mapping_fixed_mappable:
        attr = "\"mapping_fixed_mappable\"";
        break;
    case static_stereotypes::mapping_extensible_mappable:
        attr = "\"mapping_extensible_mappable\"";
        break;
    case static_stereotypes::templating_logic_less_template:
        attr = "\"templating_logic_less_template\"";
        break;
    case static_stereotypes::serialization_type_registrar:
        attr = "\"serialization_type_registrar\"";
        break;
    case static_stereotypes::build_visual_studio_solution:
        attr = "\"build_visual_studio_solution\"";
        break;
    case static_stereotypes::build_visual_studio_project:
        attr = "\"build_visual_studio_project\"";
        break;
    case static_stereotypes::orm_common_odb_options:
        attr = "\"orm_common_odb_options\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for static_stereotypes");
    }
    s << attr << " }";
    return s;
}

}
