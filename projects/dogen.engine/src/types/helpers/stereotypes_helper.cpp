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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.utility/types/exception/invalid_enum_value.hpp"
#include "dogen.assets/io/meta_model/static_stereotypes_io.hpp"
#include "dogen.assets/types/meta_model/static_stereotypes.hpp"
#include "dogen.engine/types/helpers/stereotypes_helper.hpp"

namespace {

const std::string
transform_id("engine.helpers.stereotypes_helper");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string stereotype_object("masd::object");
const std::string stereotype_object_template("masd::object_template");
const std::string stereotype_exception("masd::exception");
const std::string stereotype_primitive("masd::primitive");
const std::string stereotype_enumeration("masd::enumeration");
const std::string stereotype_module("masd::module");
const std::string stereotype_builtin("masd::builtin");
const std::string stereotype_visitable("masd::visitable");
const std::string stereotype_fluent("masd::fluent");
const std::string stereotype_immutable("masd::immutable");
const std::string stereotype_orm_object("masd::orm::object");
const std::string stereotype_orm_value("masd::orm::value");
const std::string stereotype_modeline_group(
    "masd::decoration::modeline_group");
const std::string stereotype_modeline("masd::decoration::modeline");
const std::string stereotype_generation_marker(
    "masd::decoration::generation_marker");
const std::string stereotype_licence("masd::decoration::licence");
const std::string stereotype_variability_profile_template(
    "masd::variability::profile_template");
const std::string stereotype_variability_feature_bundle(
    "masd::variability::feature_bundle");
const std::string stereotype_variability_feature_template_initializer(
    "masd::variability::feature_template_initializer");
const std::string stereotype_mapping_fixed_mappable(
    "masd::mapping::fixed_mappable");
const std::string stereotype_mapping_extensible_mappable(
    "masd::mapping::extensible_mappable");
const std::string stereotype_templating_logic_less_templates(
    "masd::templating::logic_less_templates");
const std::string stereotype_serialization_type_registrar(
    "masd::serialization::type_registrar");
const std::string stereotype_build_visual_studio_component(
    "masd::build::visual_studio::component");
const std::string unsupported_stereotype("Invalid or unsupported stereotype: ");

}

namespace dogen::engine::helpers {

using assets::meta_model::static_stereotypes;

static_stereotypes stereotypes_helper::from_string(const std::string& s) const {
    BOOST_LOG_SEV(lg, debug) << "Converting stereotype: " << s;

    if (s == stereotype_object)
        return static_stereotypes::object;
    else if (s == stereotype_object_template)
        return static_stereotypes::object_template;
    else if (s == stereotype_exception)
        return static_stereotypes::exception;
    else if (s == stereotype_primitive)
        return static_stereotypes::primitive;
    else if (s == stereotype_enumeration)
        return static_stereotypes::enumeration;
    else if (s == stereotype_module)
        return static_stereotypes::module;
    else if (s == stereotype_builtin)
        return static_stereotypes::builtin;
    else if (s == stereotype_visitable)
        return static_stereotypes::visitable;
    else if (s == stereotype_fluent)
        return static_stereotypes::fluent;
    else if (s == stereotype_immutable)
        return static_stereotypes::immutable;
    else if (s == stereotype_orm_object)
        return static_stereotypes::orm_object;
    else if (s == stereotype_orm_value)
        return static_stereotypes::orm_value;
    else if (s == stereotype_modeline_group)
        return static_stereotypes::modeline_group;
    else if (s == stereotype_modeline)
        return static_stereotypes::modeline;
    else if (s == stereotype_generation_marker)
        return static_stereotypes::generation_marker;
    else if (s == stereotype_licence)
        return static_stereotypes::licence;
    else if (s == stereotype_variability_profile_template)
        return static_stereotypes::variability_profile_template;
    else if (s == stereotype_variability_feature_bundle)
        return static_stereotypes::variability_feature_bundle;
    else if (s == stereotype_variability_feature_template_initializer)
        return static_stereotypes::variability_feature_template_initializer;
    else if (s == stereotype_mapping_fixed_mappable)
        return static_stereotypes::mapping_fixed_mappable;
    else if (s == stereotype_mapping_extensible_mappable)
        return static_stereotypes::mapping_extensible_mappable;
    else if (s == stereotype_templating_logic_less_templates)
        return static_stereotypes::templating_logic_less_template;
    else if (s == stereotype_serialization_type_registrar)
        return static_stereotypes::serialization_type_registrar;
    else if (s == stereotype_build_visual_studio_component)
        return static_stereotypes::build_visual_studio_component;

    BOOST_LOG_SEV(lg, debug) << "Could not convert stereotype."
                             << " Assuming dynamic.";
    return static_stereotypes::invalid;
}

stereotypes_conversion_result
stereotypes_helper::from_csv_string(const std::string& s) const {
    if (s.empty()) {
        stereotypes_conversion_result r;
        return r;
    }

    using utility::string::splitter;
    const auto stereotypes(splitter::split_csv(s));
    return from_string(stereotypes);
}

stereotypes_conversion_result stereotypes_helper::
from_string(const std::list<std::string>& stereotypes) const {
    stereotypes_conversion_result r;
    if (stereotypes.empty())
        return r;

    for (const auto& stereotype : stereotypes) {
        const auto ss(from_string(stereotype));
        if (ss != static_stereotypes::invalid)
            r.static_stereotypes().push_back(ss);
        else
            r.dynamic_stereotypes().push_back(stereotype);
    }
    return r;
}

std::string stereotypes_helper::
to_string(const static_stereotypes ss) const {
    switch(ss) {
    case static_stereotypes::object: return stereotype_object;
    case static_stereotypes::object_template: return stereotype_object;
    case static_stereotypes::exception: return stereotype_exception;
    case static_stereotypes::primitive: return stereotype_primitive;
    case static_stereotypes::enumeration: return stereotype_enumeration;
    case static_stereotypes::module: return stereotype_module;
    case static_stereotypes::builtin: return stereotype_builtin;
    case static_stereotypes::visitable: return stereotype_visitable;
    case static_stereotypes::fluent: return stereotype_fluent;
    case static_stereotypes::immutable: return stereotype_immutable;
    case static_stereotypes::orm_object: return stereotype_orm_object;
    case static_stereotypes::orm_value: return stereotype_orm_value;
    case static_stereotypes::modeline_group: return stereotype_modeline_group;
    case static_stereotypes::modeline: return stereotype_modeline;
    case static_stereotypes::generation_marker:
        return stereotype_generation_marker;
    case static_stereotypes::licence: return stereotype_licence;
    case static_stereotypes::variability_profile_template:
        return stereotype_variability_profile_template;
    case static_stereotypes::variability_feature_bundle:
        return stereotype_variability_feature_template_initializer;
    case static_stereotypes::variability_feature_template_initializer:
        return stereotype_variability_feature_template_initializer;
    case static_stereotypes::mapping_fixed_mappable:
        return stereotype_mapping_fixed_mappable;
    case static_stereotypes::mapping_extensible_mappable:
        return stereotype_mapping_extensible_mappable;
    case static_stereotypes::templating_logic_less_template:
        return stereotype_templating_logic_less_templates;
    case static_stereotypes::serialization_type_registrar:
        return stereotype_serialization_type_registrar;
    case static_stereotypes::build_visual_studio_component:
        return stereotype_build_visual_studio_component;

    default: {
        const std::string s(boost::lexical_cast<std::string>(ss));
        BOOST_LOG_SEV(lg, error) << unsupported_stereotype << s;
        using dogen::utility::exception::invalid_enum_value;
        BOOST_THROW_EXCEPTION(invalid_enum_value(unsupported_stereotype + s));
    } }
}

bool stereotypes_helper::
is_element_type(const static_stereotypes ss) const {
    return
        ss == static_stereotypes::object ||
        ss == static_stereotypes::object_template ||
        ss == static_stereotypes::exception ||
        ss == static_stereotypes::primitive ||
        ss == static_stereotypes::enumeration ||
        ss == static_stereotypes::module ||
        ss == static_stereotypes::builtin ||
        ss == static_stereotypes::modeline_group ||
        ss == static_stereotypes::modeline ||
        ss == static_stereotypes::generation_marker ||
        ss == static_stereotypes::licence ||
        ss == static_stereotypes::variability_profile_template ||
        ss == static_stereotypes::variability_feature_bundle ||
        ss == static_stereotypes::variability_feature_template_initializer ||
        ss == static_stereotypes::mapping_fixed_mappable ||
        ss == static_stereotypes::mapping_extensible_mappable ||
        ss == static_stereotypes::templating_logic_less_template ||
        ss == static_stereotypes::serialization_type_registrar ||
        ss == static_stereotypes::build_visual_studio_component;
}

std::list<static_stereotypes> stereotypes_helper::extract_element_types(
    const std::list<static_stereotypes>& ss) const {

    std::list<static_stereotypes> r;
    for (const auto st : ss)
        if (is_element_type(st))
            r.push_back(st);

    return r;
}

std::list<static_stereotypes> stereotypes_helper::
extract_non_element_types(const std::list<static_stereotypes>& ss) const {
    std::list<static_stereotypes> r;
    for (const auto st : ss)
        if (!is_element_type(st))
            r.push_back(st);

    return r;
}

}
