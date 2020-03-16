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
#include "dogen.variability/io/entities/value_type_io.hpp"
#include "dogen.variability/io/entities/binding_point_io.hpp"
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

const std::string invalid_scope("Invalid or unsupported scope type: ");
const std::string invalid_value_type("Invalid or unsupported value type: ");

}

namespace dogen::variability::helpers {

entities::value_type
enum_mapper::to_value_type(const std::string& s) {
    using entities::value_type;
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

entities::binding_point enum_mapper::to_binding_point(const std::string& s) {
    using entities::binding_point;
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

std::string enum_mapper::from_value_type(const entities::value_type v,
    const bool qualified) {
    using entities::value_type;
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

std::string enum_mapper::from_binding_point(const entities::binding_point v) {
    using entities::binding_point;
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
