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
#include "dogen.assets/types/traits.hpp"

namespace dogen::assets {

std::string traits::enabled() {
    static std::string r("enabled");
    return r;
}

std::string traits::directory() {
    static std::string r("directory");
    return r;
}

std::string traits::postfix() {
    static std::string r("postfix");
    return r;
}

std::string traits::supported() {
    static std::string r("supported");
    return r;
}

std::string traits::overwrite() {
    static std::string r("overwrite");
    return r;
}

std::string traits::output_technical_space() {
    static std::string r("masd.extraction.output_technical_space");
    return r;
}

std::string traits::is_proxy_model() {
    static std::string r("masd.injection.is_proxy_model");
    return r;
}

std::string traits::external_modules() {
    static std::string r("masd.injection.external_modules");
    return r;
}

std::string traits::model_modules() {
    static std::string r("masd.injection.model_modules");
    return r;
}

std::string traits::extraction::force_write() {
    static std::string r("masd.extraction.force_write");
    return r;
}

std::string traits::extraction::delete_extra_files() {
    static std::string r("masd.extraction.delete_extra_files");
    return r;
}

std::string traits::extraction::ignore_files_matching_regex() {
    static std::string r("masd.extraction.ignore_files_matching_regex");
    return r;
}

std::string traits::extraction::cpp_headers_output_directory() {
    static std::string r("masd.generation.cpp_headers_output_directory");
    return r;
}

std::string traits::extraction::enable_backend_directories() {
    static std::string r("masd.extraction.enable_backend_directories");
    return r;
}

std::string traits::enable_backend_directories() {
    static std::string r("masd.extraction.enable_backend_directories");
    return r;
}

std::string traits::type_parameters::variable_number_of_parameters() {
    static std::string r("masd.type_parameters.variable_number_of_parameters");
    return r;
}

std::string traits::type_parameters::type_parameters_count() {
    static std::string r("masd.type_parameters.count");
    return r;
}

std::string traits::type_parameters::type_parameters_always_in_heap() {
    static std::string r("masd.type_parameters.always_in_heap");
    return r;
}

std::string traits::generalization::is_final() {
    static std::string r("masd.generalization.is_final");
    return r;
}

std::string traits::generalization::parent() {
    static std::string r("masd.generalization.parent");
    return r;
}

std::string traits::enumeration::
use_implementation_defined_underlying_element() {
    static std::string r(
        "masd.enumeration.use_implementation_defined_underlying_element");
    return r;
}

std::string traits::enumeration::underlying_element() {
    static std::string r("masd.enumeration.underlying_element");
    return r;
}

std::string traits::enumeration::
use_implementation_defined_enumerator_values() {
    static std::string r(
        "masd.enumeration.use_implementation_defined_enumerator_values");
    return r;
}

std::string traits::enumeration::add_invalid_enumerator() {
    static std::string r("masd.enumeration.add_invalid_enumerator");
    return r;
}

std::string traits::enumerator::value() {
    static std::string r("masd.enumerator.value");
    return r;
}

std::string traits::primitive::underlying_element() {
    static std::string r("masd.primitive.underlying_element");
    return r;
}

std::string traits::primitive::is_nullable() {
    static std::string r("masd.primitive.is_nullable");
    return r;
}

std::string traits::primitive::use_type_aliasing() {
    static std::string r("masd.primitive.use_type_aliasing");
    return r;
}

std::string traits::orm::database_system() {
    static std::string r("masd.orm.database_system");
    return r;
}

std::string traits::orm::table_name() {
    static std::string r("masd.orm.table_name");
    return r;
}

std::string traits::orm::schema_name() {
    static std::string r("masd.orm.schema_name");
    return r;
}

std::string traits::orm::is_primary_key() {
    static std::string r("masd.orm.is_primary_key");
    return r;
}

std::string traits::orm::column_name() {
    static std::string r("masd.orm.column_name");
    return r;
}

std::string traits::orm::is_nullable() {
    static std::string r("masd.orm.is_nullable");
    return r;
}

std::string traits::orm::letter_case() {
    static std::string r("masd.orm.letter_case");
    return r;
}

std::string traits::orm::type_override() {
    static std::string r("masd.orm.type_override");
    return r;
}

std::string traits::orm::is_composite() {
    static std::string r("masd.orm.is_composite");
    return r;
}

std::string traits::decoration::modeline::editor() {
    static std::string r("masd.decoration.modeline.editor");
    return r;
}

std::string traits::decoration::modeline::location() {
    static std::string r("masd.decoration.modeline.location");
    return r;
}
std::string traits::decoration::modeline::technical_space() {
    static std::string r("masd.decoration.modeline.technical_space");
    return r;
}

std::string traits::variability::binding_point() {
    static std::string r("masd.variability.binding_point");
    return r;
}

std::string traits::variability::labels() {
    static std::string r("masd.variability.labels");
    return r;
}

std::string traits::variability::archetype_location_kernel() {
    static std::string r("masd.variability.archetype_location.kernel");
    return r;
}

std::string traits::variability::archetype_location_backend() {
    static std::string r("masd.variability.archetype_location.backend");
    return r;
}

std::string traits::variability::archetype_location_facet() {
    static std::string r("masd.variability.archetype_location.facet");
    return r;
}

std::string traits::variability::archetype_location_archetype() {
    static std::string r("masd.variability.archetype_location.archetype");
    return r;
}

std::string traits::variability::template_kind() {
    static std::string r("masd.variability.template_kind");
    return r;
}

std::string traits::variability::qualified_name() {
    static std::string r("masd.variability.qualified_name");
    return r;
}

std::string traits::variability::untyped_value() {
    static std::string r("masd.variability.value");
    return r;
}

std::string traits::mapping::target() {
    static std::string r("masd.mapping.target");
    return r;
}

std::string traits::mapping::destination() {
    static std::string r("masd.mapping.destination");
    return r;
}

}
