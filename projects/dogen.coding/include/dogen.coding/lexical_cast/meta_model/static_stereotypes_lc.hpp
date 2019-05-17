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
#ifndef DOGEN_CODING_LEXICAL_CAST_META_MODEL_STATIC_STEREOTYPES_LC_HPP
#define DOGEN_CODING_LEXICAL_CAST_META_MODEL_STATIC_STEREOTYPES_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.coding/types/meta_model/static_stereotypes.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::coding::meta_model::static_stereotypes& v) {
    using dogen::coding::meta_model::static_stereotypes;

    switch (v) {
    case static_stereotypes::invalid:
        return "static_stereotypes::invalid";
    case static_stereotypes::object:
        return "static_stereotypes::object";
    case static_stereotypes::object_template:
        return "static_stereotypes::object_template";
    case static_stereotypes::exception:
        return "static_stereotypes::exception";
    case static_stereotypes::primitive:
        return "static_stereotypes::primitive";
    case static_stereotypes::enumeration:
        return "static_stereotypes::enumeration";
    case static_stereotypes::module:
        return "static_stereotypes::module";
    case static_stereotypes::builtin:
        return "static_stereotypes::builtin";
    case static_stereotypes::visitable:
        return "static_stereotypes::visitable";
    case static_stereotypes::fluent:
        return "static_stereotypes::fluent";
    case static_stereotypes::immutable:
        return "static_stereotypes::immutable";
    case static_stereotypes::orm_object:
        return "static_stereotypes::orm_object";
    case static_stereotypes::orm_value:
        return "static_stereotypes::orm_value";
    case static_stereotypes::modeline_group:
        return "static_stereotypes::modeline_group";
    case static_stereotypes::modeline:
        return "static_stereotypes::modeline";
    case static_stereotypes::generation_marker:
        return "static_stereotypes::generation_marker";
    case static_stereotypes::licence:
        return "static_stereotypes::licence";
    case static_stereotypes::variability_profile_template:
        return "static_stereotypes::variability_profile_template";
    case static_stereotypes::variability_feature_bundle:
        return "static_stereotypes::variability_feature_bundle";
    case static_stereotypes::variability_feature_template_initializer:
        return "static_stereotypes::variability_feature_template_initializer";
    case static_stereotypes::mapping_fixed_mappable:
        return "static_stereotypes::mapping_fixed_mappable";
    case static_stereotypes::mapping_extensible_mappable:
        return "static_stereotypes::mapping_extensible_mappable";
    case static_stereotypes::templating_logic_less_template:
        return "static_stereotypes::templating_logic_less_template";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::coding::meta_model::static_stereotypes lexical_cast(const std::string & s) {
    using dogen::coding::meta_model::static_stereotypes;

    if (s == "invalid" || s == "static_stereotypes::invalid")
        return static_stereotypes::invalid;
    if (s == "object" || s == "static_stereotypes::object")
        return static_stereotypes::object;
    if (s == "object_template" || s == "static_stereotypes::object_template")
        return static_stereotypes::object_template;
    if (s == "exception" || s == "static_stereotypes::exception")
        return static_stereotypes::exception;
    if (s == "primitive" || s == "static_stereotypes::primitive")
        return static_stereotypes::primitive;
    if (s == "enumeration" || s == "static_stereotypes::enumeration")
        return static_stereotypes::enumeration;
    if (s == "module" || s == "static_stereotypes::module")
        return static_stereotypes::module;
    if (s == "builtin" || s == "static_stereotypes::builtin")
        return static_stereotypes::builtin;
    if (s == "visitable" || s == "static_stereotypes::visitable")
        return static_stereotypes::visitable;
    if (s == "fluent" || s == "static_stereotypes::fluent")
        return static_stereotypes::fluent;
    if (s == "immutable" || s == "static_stereotypes::immutable")
        return static_stereotypes::immutable;
    if (s == "orm_object" || s == "static_stereotypes::orm_object")
        return static_stereotypes::orm_object;
    if (s == "orm_value" || s == "static_stereotypes::orm_value")
        return static_stereotypes::orm_value;
    if (s == "modeline_group" || s == "static_stereotypes::modeline_group")
        return static_stereotypes::modeline_group;
    if (s == "modeline" || s == "static_stereotypes::modeline")
        return static_stereotypes::modeline;
    if (s == "generation_marker" || s == "static_stereotypes::generation_marker")
        return static_stereotypes::generation_marker;
    if (s == "licence" || s == "static_stereotypes::licence")
        return static_stereotypes::licence;
    if (s == "variability_profile_template" || s == "static_stereotypes::variability_profile_template")
        return static_stereotypes::variability_profile_template;
    if (s == "variability_feature_bundle" || s == "static_stereotypes::variability_feature_bundle")
        return static_stereotypes::variability_feature_bundle;
    if (s == "variability_feature_template_initializer" || s == "static_stereotypes::variability_feature_template_initializer")
        return static_stereotypes::variability_feature_template_initializer;
    if (s == "mapping_fixed_mappable" || s == "static_stereotypes::mapping_fixed_mappable")
        return static_stereotypes::mapping_fixed_mappable;
    if (s == "mapping_extensible_mappable" || s == "static_stereotypes::mapping_extensible_mappable")
        return static_stereotypes::mapping_extensible_mappable;
    if (s == "templating_logic_less_template" || s == "static_stereotypes::templating_logic_less_template")
        return static_stereotypes::templating_logic_less_template;
    throw boost::bad_lexical_cast();
}

}

#endif
