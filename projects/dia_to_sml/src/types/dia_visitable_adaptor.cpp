/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/visitation_error.hpp"
#include "dogen/dia_to_sml/types/dia_visitable_adaptor.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.dia_visitable_adaptor"));

const std::string dia_string("string");
const std::string dia_name("name");
const std::string dia_type("type");
const std::string dia_comment("comment");
const std::string dia_stereotype("stereotype");
const std::string dia_attributes("attributes");
const std::string dia_composite("composite");
const std::string dia_uml_attribute("umlattribute");
const std::string hash_character("#");

const std::string uml_large_package("UML - LargePackage");
const std::string uml_class("UML - Class");
const std::string uml_generalization("UML - Generalization");
const std::string uml_association("UML - Association");
const std::string uml_note("UML - Note");
const std::string uml_message("UML - Message");
const std::string uml_realization("UML - Realizes");
const std::string invalid_object_type("Invalid value for object type: ");
const std::string invalid_stereotype("Invalid value for stereotype: ");

const std::string enumeration("enumeration");
const std::string exception("exception");
const std::string entity("entity");
const std::string value("value");
const std::string service("service");
const std::string nongeneratable("nongeneratable");

const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string uml_attribute_expected("UML atttribute expected");
const std::string error_parsing_stereotype("Fail to parse stereotype: ");
const std::string name_attribute_expected(
    "Could not find name attribute. ID: ");
const std::string type_attribute_expected(
    "Could not find type attribute. ID: ");
const std::string unexpected_attribute_value_type(
    "Did not find expected attribute value type: ");
const std::string unexpected_attribute_value_size(
    "Unexpected attribute value size: ");
const std::string invalid_type_string(
    "String provided with type did not parse into SML qnames: ");
const std::string object_has_invalid_type("Invalid dia type: ");
const std::string invalid_stereotype_in_graph("Invalid stereotype: ");

template<typename AttributeValue, typename Variant>
AttributeValue
attribute_value(const Variant& v, const std::string& desc) {

    AttributeValue r;
    try {
        r = boost::get<AttributeValue>(v);
    } catch (const boost::bad_get&) {
        BOOST_LOG_SEV(lg, error) << unexpected_attribute_value_type << desc;

        using dogen::dia_to_sml::visitation_error;
        BOOST_THROW_EXCEPTION(
            visitation_error(unexpected_attribute_value_type + desc));
    }
    return r;
}

}

namespace dogen {
namespace dia_to_sml {

object_types
dia_visitable_adaptor::parse_object_type(const std::string& ot) const {
    if (ot == uml_large_package)
        return object_types::uml_large_package;

    if (ot == uml_class)
        return object_types::uml_class;

    if (ot == uml_generalization)
        return object_types::uml_generalization;

    if (ot == uml_association)
        return object_types::uml_association;

    if (ot == uml_note)
        return object_types::uml_note;

    if (ot == uml_message)
        return object_types::uml_message;

    if (ot == uml_realization)
        return object_types::uml_realization;

    BOOST_LOG_SEV(lg, error) << invalid_object_type << ot;
    BOOST_THROW_EXCEPTION(visitation_error(invalid_object_type + ot));
}

stereotypes dia_visitable_adaptor::
parse_stereotype(const std::string& st) const {
    if (st == enumeration)
        return stereotypes::enumeration;

    if (st == exception)
        return stereotypes::exception;

    if (st == entity)
        return stereotypes::entity;

    if (st == value)
        return stereotypes::value;

    if (st == service)
        return stereotypes::service;

    if (st == nongeneratable)
        return stereotypes::nongeneratable;

    BOOST_LOG_SEV(lg, error) << invalid_stereotype << st;
    BOOST_THROW_EXCEPTION(visitation_error(invalid_stereotype + st));
}

std::string dia_visitable_adaptor::
parse_string_attribute(const dia::attribute& a) const {
    const auto values(a.values());
    if (values.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected attribute to have one"
                                 << " value but found " << values.size();
        BOOST_THROW_EXCEPTION(
            visitation_error(unexpected_attribute_value_size +
                boost::lexical_cast<std::string>(values.size())));
    }

    using dia::string;
    const auto v(attribute_value<string>(values.front(), dia_string));
    std::string name(v.value());
    boost::erase_first(name, hash_character);
    boost::erase_last(name, hash_character);
    boost::trim(name);
    return name;
}

void dia_visitable_adaptor::accept(const dia::object& o, dia_visitor& v) {
    v.object_type(parse_object_type(o.type()));
    for (auto a : o.attributes()) {
        BOOST_LOG_SEV(lg, debug) << "Found attribute: " << a.name();

        if (a.name() == dia_name)
            v.name(parse_string_attribute(a));
        else if (a.name() == dia_stereotype)
            v.stereotype(parse_stereotype(parse_string_attribute(a)));
        else if (a.name() == dia_comment)
            v.comment(parse_string_attribute(a));
        else if (a.name() == dia_attributes) {
            const auto& values(a.values());
            if (values.empty()) {
                BOOST_LOG_SEV(lg, debug) << "Attribute is empty.";
                continue;
            }

            for (const auto& val : values) {
                using dia::composite;
                v.composite(attribute_value<composite>(val, dia_composite));
            }
        }
    }
}

void dia_visitable_adaptor::accept(const dia::object& o, const dia_visitor& v) {
    v.object_type(parse_object_type(o.type()));
    for (auto a : o.attributes()) {
        BOOST_LOG_SEV(lg, debug) << "Found attribute: " << a.name();

        if (a.name() == dia_name)
            v.name(parse_string_attribute(a));
        else if (a.name() == dia_stereotype)
            v.stereotype(parse_stereotype(parse_string_attribute(a)));
        else if (a.name() == dia_comment)
            v.comment(parse_string_attribute(a));
        else if (a.name() == dia_attributes) {
            const auto& values(a.values());
            if (values.empty()) {
                BOOST_LOG_SEV(lg, debug) << "Attribute is empty.";
                continue;
            }

            for (const auto& val : values) {
                using dia::composite;
                v.composite(attribute_value<composite>(val, dia_composite));
            }
        }
    }
}

void dia_visitable_adaptor::
accept(const dia::composite& c, const dia_visitor& v) {
    for (const auto a : c.value()) {
        if (a->name() == dia_name)
            v.name(parse_string_attribute(*a));
        else if (a->name() == dia_stereotype)
            v.stereotype(parse_stereotype(parse_string_attribute(*a)));
        else if (a->name() == dia_comment)
            v.comment(parse_string_attribute(*a));
    }
}

void dia_visitable_adaptor::
accept(const dia::composite& c, dia_visitor& v) {
    for (const auto a : c.value()) {
        if (a->name() == dia_name)
            v.name(parse_string_attribute(*a));
        else if (a->name() == dia_stereotype)
            v.stereotype(parse_stereotype(parse_string_attribute(*a)));
        else if (a->name() == dia_comment)
            v.comment(parse_string_attribute(*a));
    }
}

} }
