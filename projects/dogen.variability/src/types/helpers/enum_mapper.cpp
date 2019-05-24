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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/io/meta_model/value_type_io.hpp"
#include "dogen.variability/io/meta_model/template_kind_io.hpp"
#include "dogen.variability/io/meta_model/binding_point_io.hpp"
#include "dogen.variability/types/helpers/enum_mapping_exception.hpp"
#include "dogen.variability/types/helpers/enum_mapper.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("variability.helpers.enum_mapper"));

const std::string input_value_type_text("masd::variability::text");
const std::string input_value_type_text_collection(
    "masd::variability::text_collection");
const std::string input_value_type_number("masd::variability::number");
const std::string input_value_type_boolean("masd::variability::boolean");
const std::string input_value_type_kvp("masd::variability::key_value_pair");

const std::string output_value_type_text("value_type::text");
const std::string output_value_type_text_collection(
    "value_type::text_collection");
const std::string output_value_type_number("value_type::number");
const std::string output_value_type_boolean("value_type::boolean");
const std::string output_value_type_kvp("value_type::key_value_pair");

const std::string output_value_type_text_simple("text");
const std::string output_value_type_text_collection_simple(
    "text_collection");
const std::string output_value_type_number_simple("number");
const std::string output_value_type_boolean_simple("boolean");
const std::string output_value_type_kvp_simple("key_value_pair");

const std::string input_binding_point_any("any");
const std::string input_binding_point_global("global");
const std::string input_binding_point_element("element");
const std::string input_binding_point_property("property");
const std::string input_binding_point_operation("operation");

const std::string output_binding_point_any("binding_point::any");
const std::string output_binding_point_global("binding_point::global");
const std::string output_binding_point_element("binding_point::element");
const std::string output_binding_point_property("binding_point::property");
const std::string output_binding_point_operation("binding_point::operation");

const std::string input_template_kind_instance("instance");
const std::string input_template_kind_recursive_template("recursive_template");
const std::string input_template_kind_backend_template("backend_template");
const std::string input_template_kind_facet_template("facet_template");
const std::string input_template_kind_archetype_template("archetype_template");

const std::string output_template_kind_instance("template_kind::instance");
const std::string output_template_kind_recursive_template(
    "template_kind::recursive_template");
const std::string output_template_kind_backend_template(
    "template_kind::backend_template");
const std::string output_template_kind_facet_template(
    "template_kind::facet_template");
const std::string output_template_kind_archetype_template(
    "template_kind::archetype_template");

const std::string invalid_scope("Invalid or unsupported scope type: ");
const std::string invalid_value_type("Invalid or unsupported value type: ");
const std::string invalid_template_kind(
    "Invalid or unsupported template kind: ");

}

namespace dogen::variability::helpers {

meta_model::value_type
enum_mapper::to_value_type(const std::string& s) {
    using meta_model::value_type;
    if (s == input_value_type_text)
        return value_type::text;
    else if (s == input_value_type_text_collection)
        return value_type::text_collection;
    else if (s == input_value_type_number)
        return value_type::number;
    else if (s == input_value_type_boolean)
        return value_type::boolean;
    else if (s == input_value_type_kvp)
        return value_type::key_value_pair;

    BOOST_LOG_SEV(lg, error) << invalid_value_type << "'" << s << "'";
    BOOST_THROW_EXCEPTION(enum_mapping_exception(invalid_value_type + s));
}

meta_model::template_kind enum_mapper::to_template_kind(const std::string& s) {
    using meta_model::template_kind;
    if (s == input_template_kind_instance)
        return template_kind::instance;
    if (s == input_template_kind_recursive_template)
        return template_kind::recursive_template;
    if (s == input_template_kind_backend_template)
        return template_kind::backend_template;
    if (s == input_template_kind_facet_template)
        return template_kind::facet_template;
    if (s == input_template_kind_archetype_template)
        return template_kind::archetype_template;

    BOOST_LOG_SEV(lg, error) << invalid_template_kind << "'" << s << "'";
    BOOST_THROW_EXCEPTION(enum_mapping_exception(invalid_template_kind + s));
}

meta_model::binding_point enum_mapper::to_binding_point(const std::string& s) {
    using meta_model::binding_point;
    if (s == input_binding_point_any)
        return binding_point::any;
    else if (s == input_binding_point_global)
        return binding_point::global;
    else if (s == input_binding_point_element)
        return binding_point::element;
    else if (s == input_binding_point_property)
        return binding_point::property;
    else if (s == input_binding_point_operation)
        return binding_point::operation;

    BOOST_LOG_SEV(lg, error) << invalid_scope << "'" << s << "'";
    BOOST_THROW_EXCEPTION(enum_mapping_exception(invalid_scope + s));
}

std::string enum_mapper::from_value_type(const meta_model::value_type v,
    const bool qualified) {
    using meta_model::value_type;
    switch(v) {
    case value_type::text:
        return qualified ?
            output_value_type_text : output_value_type_text_simple;
    case value_type::text_collection:
        return qualified ?
            output_value_type_text_collection :
        output_value_type_text_collection_simple;
    case value_type::number:
        return qualified ? output_value_type_number :
        output_value_type_number_simple;
    case value_type::boolean:
        return qualified ? output_value_type_boolean :
        output_value_type_boolean_simple;
    case value_type::key_value_pair:
        return qualified ? output_value_type_kvp :
        output_value_type_kvp_simple;
    default: {
        const auto s(boost::lexical_cast<std::string>(v));
        BOOST_LOG_SEV(lg, error) << invalid_value_type << "'" << s << "'";
        BOOST_THROW_EXCEPTION(enum_mapping_exception(invalid_value_type + s));
    } }
}

std::string enum_mapper::from_template_kind(const meta_model::template_kind v) {
    using meta_model::template_kind;
    switch (v) {
    case template_kind::instance:
        return output_template_kind_instance;
    case template_kind::recursive_template:
        return output_template_kind_recursive_template;
    case template_kind::backend_template:
        return output_template_kind_backend_template;
    case template_kind::facet_template:
        return output_template_kind_facet_template;
    case template_kind::archetype_template:
        return output_template_kind_archetype_template;
    default: {
        const auto s(boost::lexical_cast<std::string>(v));
        BOOST_LOG_SEV(lg, error) << invalid_template_kind << "'" << s << "'";
        BOOST_THROW_EXCEPTION(
            enum_mapping_exception(invalid_template_kind + s));
    } }
}

std::string enum_mapper::from_binding_point(const meta_model::binding_point v) {
    using meta_model::binding_point;
    switch(v) {
    case binding_point::any: return output_binding_point_any;
    case binding_point::global: return output_binding_point_global;
    case binding_point::element: return output_binding_point_element;
    case binding_point::property: return output_binding_point_property;
    case binding_point::operation: return output_binding_point_operation;
    default: {
        const auto s(boost::lexical_cast<std::string>(v));
        BOOST_LOG_SEV(lg, error) << invalid_scope << "'" << s << "'";
      BOOST_THROW_EXCEPTION(enum_mapping_exception(invalid_scope + s));
    } }
}

}
