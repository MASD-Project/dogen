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
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/vector_io.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.dia/types/entities/object.hpp"
#include "dogen.dia/types/entities/attribute.hpp"
#include "dogen.dia/types/entities/composite.hpp"
#include "dogen.dia/types/entities/diagram.hpp"
#include "dogen.codec/io/entities/object_io.hpp"
#include "dogen.codec.dia/types/building_error.hpp"
#include "dogen.codec/types/entities/object.hpp"
#include "dogen.codec.dia/types/processed_comment_factory.hpp"
#include "dogen.codec.dia/types/processed_object_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("codec.dia.processed_object_factory"));

const std::string dia_string("string");
const std::string dia_name("name");
const std::string dia_type("type");
const std::string dia_value("value");
const std::string dia_text("text");
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
const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string uml_attribute_expected("UML atttribute expected");
const std::string text_attribute_expected("Text attribute expected");
const std::string one_value_expected("Attribute should have exactly one value");
const std::string name_attribute_expected(
    "Could not find name attribute. ID: ");
const std::string type_attribute_expected(
    "Could not find type attribute. ID: ");
const std::string unexpected_attribute_value_type(
    "Did not find expected attribute value type: ");
const std::string unexpected_attribute_value_size(
    "Unexpected attribute value size: ");
const std::string object_has_invalid_type("Invalid dia type: ");
const std::string unexpected_number_of_connections(
    "Expected 2 connections but found: ");

template<typename AttributeValue, typename Variant>
AttributeValue
get_attribute_value(const Variant& v, const std::string& desc) {

    AttributeValue r;
    try {
        r = boost::get<AttributeValue>(v);
    } catch (const boost::bad_get&) {
        BOOST_LOG_SEV(lg, error) << unexpected_attribute_value_type << desc;

        using dogen::codec::dia::building_error;
        BOOST_THROW_EXCEPTION(
            building_error(unexpected_attribute_value_type + desc));
    }
    return r;
}

template<typename AttributeValue, typename Variant>
boost::optional<AttributeValue> try_get_attribute_value(const Variant& v) {
    AttributeValue r;
    // FIXME: we should probably replace this with a static visitor.
    try {
        r = boost::get<AttributeValue>(v);
    } catch (const boost::bad_get&) {
        return boost::optional<AttributeValue>();
    }
    return r;
}

}

namespace dogen::codec::dia {

std::string processed_object_factory::
parse_string_attribute(const dogen::dia::entities::attribute& a) {
    const auto values(a.values());
    if (values.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected attribute to have one"
                                 << " value but found " << values.size();
        BOOST_THROW_EXCEPTION(
            building_error(unexpected_attribute_value_size +
                boost::lexical_cast<std::string>(values.size())));
    }

    using dogen::dia::entities::string;
    const auto v(get_attribute_value<string>(values.front(), dia_string));
    std::string name(v.value());
    boost::erase_first(name, hash_character);
    boost::erase_last(name, hash_character);
    boost::trim(name);
    return name;
}

entities::comment processed_object_factory::
create_processed_comment(const dogen::dia::entities::attribute& a) {
    const auto s(parse_string_attribute(a));
    return processed_comment_factory::make(s);
}

void processed_object_factory::
parse_connections(const dogen::dia::entities::object& o, entities::object& po) {
    /*
     * If there are no connections we have no work to do.
     */
    if (o.connections().empty())
        return;

    /*
     * At present we only care about UML generalisation. We are
     * ignoring UML association and realisation.
     */
    if (po.object_type() != uml_generalization)
        return;

    /*
     * Each connection can only connect two objects. This is a bit of
     * a Dia invariant, but might as well check it in case we have a
     * dodgy diagram file.
     */
    const auto s(o.connections().size());
    if (s != 2) {
        const auto size(boost::lexical_cast<std::string>(s));
        BOOST_LOG_SEV(lg, error) << unexpected_number_of_connections << s;
        BOOST_THROW_EXCEPTION(
            building_error(unexpected_number_of_connections + size));
    }

    BOOST_LOG_SEV(lg, debug) << "Processing connections for object: '"
                             << o.id() << "' of type: '" << o.type() << "'";

    const auto parent(o.connections().front());
    const auto child(o.connections().back());
    po.connection(std::make_pair(parent.to(), child.to()));
}

void processed_object_factory::
parse_as_dia_text(const dogen::dia::entities::attribute a, entities::object& o) {
    if (a.values().size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected text attribute to "
                                 << "have a single value but found "
                                 << a.values().size();
        BOOST_THROW_EXCEPTION(building_error(one_value_expected));
    }


    using dogen::dia::entities::composite;
    const auto c(try_get_attribute_value<composite>(a.values().front()));
    if (!c)
        return;

    if (c->type() != dia_text) {
        BOOST_LOG_SEV(lg, error) << "Expected composite type "
                                 << "to be " << dia_text
                                 << "but was " << c->type();

        BOOST_THROW_EXCEPTION(building_error(text_attribute_expected));
    }

    BOOST_LOG_SEV(lg, debug) << "Found composite of type " << c->type();

    for (const auto& a : c->value()) {
        if (a->name() == dia_string)
            o.comment(create_processed_comment(*a));
        else
            BOOST_LOG_SEV(lg, warn) << "Ignoring attribute: " << a->name();
    }
}

void  processed_object_factory::parse_as_class_attributes(
    const dogen::dia::entities::attribute a, entities::object& o) {

    const auto& values(a.values());
    if (values.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Object has no UML attributes.";
        return;
    }

    for (const auto& v : values) {
        using dogen::dia::entities::composite;
        const auto& c(get_attribute_value<composite>(v, dia_composite));
        if (c.type() != dia_uml_attribute) {
            BOOST_LOG_SEV(lg, error) << "Expected composite type "
                                     << " to be " << dia_uml_attribute
                                     << "but was " << c.type();

            BOOST_THROW_EXCEPTION(building_error(uml_attribute_expected));
        }
        BOOST_LOG_SEV(lg, debug) << "Found composite of type " << c.type();

        entities::attribute pa;
        for (const auto& a : c.value()) {
            if (a->name() == dia_name)
                pa.name().simple(parse_string_attribute(*a));
            else if (a->name() == dia_type)
                pa.type(parse_string_attribute(*a));
            else if (a->name() == dia_value)
                pa.value(parse_string_attribute(*a));
            else if (a->name() == dia_comment)
                pa.comment(create_processed_comment(*a));
            else
                BOOST_LOG_SEV(lg, warn) << "Ignoring attribute: " << a->name();
        }
        o.attributes().push_back(pa);
    }
}

void processed_object_factory::
parse_as_stereotypes(dogen::dia::entities::attribute a, entities::object& o) {
    /*
     * When it comes to stereotypes, we only care about objects and
     * packages.
     */
    if (o.object_type() != uml_class && o.object_type() != uml_large_package) {
        BOOST_LOG_SEV(lg, debug) << "Not processing stereotypes for object: "
                                 << o.id() << " of type: "
                                 << o.object_type();
        return;
    }

    const auto s(parse_string_attribute(a));
    o.stereotypes(s);
}

void processed_object_factory::
parse_attributes(const dogen::dia::entities::object& o, entities::object& po) {
    for (auto a : o.attributes()) {
        if (a.name() == dia_name)
            po.name(parse_string_attribute(a));
        else if (a.name() == dia_stereotype)
            parse_as_stereotypes(a, po);
        else if (a.name() == dia_comment)
            po.comment(create_processed_comment(a));
        else if (a.name() ==  dia_text)
            parse_as_dia_text(a, po);
        else if (a.name() == dia_attributes)
            parse_as_class_attributes(a, po);
    }
}

entities::object processed_object_factory::
make(const dogen::dia::entities::object& o) {
    BOOST_LOG_SEV(lg, debug) << "Processing dia object " << o.id();

    entities::object r;
    r.id(o.id());
    r.object_type(o.type());

    if (o.child_node())
        r.container_id(o.child_node()->parent());

    parse_connections(o, r);
    parse_attributes(o, r);

    BOOST_LOG_SEV(lg, debug) << "Finished processing dia object. Result: " << r;
    return r;
}

std::list<entities::object>
processed_object_factory::make(const dogen::dia::entities::diagram& d) {
    std::list<entities::object> r;
    for (const auto& l : d.layers()) {
        for (const auto& o : l.objects())
            r.push_back(make(o));
    }
    return r;
}

}
