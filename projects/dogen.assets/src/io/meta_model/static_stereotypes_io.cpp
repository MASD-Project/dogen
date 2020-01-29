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
    case static_stereotypes::object:
        attr = "\"object\"";
        break;
    case static_stereotypes::object_template:
        attr = "\"object_template\"";
        break;
    case static_stereotypes::exception:
        attr = "\"exception\"";
        break;
    case static_stereotypes::primitive:
        attr = "\"primitive\"";
        break;
    case static_stereotypes::enumeration:
        attr = "\"enumeration\"";
        break;
    case static_stereotypes::module:
        attr = "\"module\"";
        break;
    case static_stereotypes::builtin:
        attr = "\"builtin\"";
        break;
    case static_stereotypes::visitable:
        attr = "\"visitable\"";
        break;
    case static_stereotypes::fluent:
        attr = "\"fluent\"";
        break;
    case static_stereotypes::immutable:
        attr = "\"immutable\"";
        break;
    case static_stereotypes::orm_object:
        attr = "\"orm_object\"";
        break;
    case static_stereotypes::orm_value:
        attr = "\"orm_value\"";
        break;
    case static_stereotypes::modeline_group:
        attr = "\"modeline_group\"";
        break;
    case static_stereotypes::modeline:
        attr = "\"modeline\"";
        break;
    case static_stereotypes::generation_marker:
        attr = "\"generation_marker\"";
        break;
    case static_stereotypes::licence:
        attr = "\"licence\"";
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
    case static_stereotypes::build_visual_studio_component:
        attr = "\"build_visual_studio_component\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for static_stereotypes");
    }
    s << attr << " }";
    return s;
}

}
