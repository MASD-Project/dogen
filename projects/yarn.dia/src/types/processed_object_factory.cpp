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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/dia/types/object.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/dia/types/composite.hpp"
#include "dogen/dia/types/diagram.hpp"
#include "dogen/yarn.dia/types/building_error.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/types/processed_comment_factory.hpp"
#include "dogen/yarn.dia/types/processed_object_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.processed_object_factory"));

const std::string dia_string("string");
const std::string dia_name("name");
const std::string dia_type("type");
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

const std::string object("yarn::object");
const std::string object_template("yarn::object_template");
const std::string enumeration("yarn::enumeration");
const std::string primitive("yarn::primitive");
const std::string exception("yarn::exception");

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
const std::string invalid_type_string(
    "String provided with type did not parse into Yarn names: ");
const std::string object_has_invalid_type("Invalid dia type: ");
const std::string unexpected_number_of_connections(
    "Expected 2 connections but found: ");
const std::string too_many_yarn_types(
    "Attempting to set the yarn type more than once.");

template<typename AttributeValue, typename Variant>
AttributeValue
get_attribute_value(const Variant& v, const std::string& desc) {

    AttributeValue r;
    try {
        r = boost::get<AttributeValue>(v);
    } catch (const boost::bad_get&) {
        BOOST_LOG_SEV(lg, error) << unexpected_attribute_value_type << desc;

        using dogen::yarn::dia::building_error;
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

namespace dogen {
namespace yarn {
namespace dia {

std::string processed_object_factory::
parse_string_attribute(const dogen::dia::attribute& a) {
    const auto values(a.values());
    if (values.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected attribute to have one"
                                 << " value but found " << values.size();
        BOOST_THROW_EXCEPTION(
            building_error(unexpected_attribute_value_size +
                boost::lexical_cast<std::string>(values.size())));
    }

    using dogen::dia::string;
    const auto v(get_attribute_value<string>(values.front(), dia_string));
    std::string name(v.value());
    boost::erase_first(name, hash_character);
    boost::erase_last(name, hash_character);
    boost::trim(name);
    return name;
}

processed_comment processed_object_factory::
create_processed_comment(const dogen::dia::attribute& a) {
    const auto s(parse_string_attribute(a));
    return processed_comment_factory::make(s);
}

dia_object_types processed_object_factory::
parse_object_type(const std::string& ot) {
    if (ot == uml_large_package)
        return dia_object_types::uml_large_package;

    if (ot == uml_class)
        return dia_object_types::uml_class;

    if (ot == uml_generalization)
        return dia_object_types::uml_generalization;

    if (ot == uml_association)
        return dia_object_types::uml_association;

    if (ot == uml_note)
        return dia_object_types::uml_note;

    if (ot == uml_message)
        return dia_object_types::uml_message;

    if (ot == uml_realization)
        return dia_object_types::uml_realization;

    BOOST_LOG_SEV(lg, error) << invalid_object_type << ot;
    BOOST_THROW_EXCEPTION(building_error(invalid_object_type + ot));
}

void processed_object_factory::
parse_connections(const dogen::dia::object& o, processed_object& po) {
    /*
     * If there are no connections we have no work to do.
     */
    if (o.connections().empty())
        return;

    /*
     * At present we only care about UML generalisation. We are
     * ignoring UML association and realisation.
     */
    if (po.dia_object_type() != dia_object_types::uml_generalization)
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
parse_as_dia_text(const dogen::dia::attribute a, processed_object& po) {
    if (a.values().size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected text attribute to "
                                 << "have a single value but found "
                                 << a.values().size();
        BOOST_THROW_EXCEPTION(building_error(one_value_expected));
    }


    using dogen::dia::composite;
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

    for (const auto a : c->value()) {
        if (a->name() == dia_string)
            po.comment(create_processed_comment(*a));
        else
            BOOST_LOG_SEV(lg, warn) << "Ignoring attribute: " << a->name();
    }
}

void  processed_object_factory::parse_as_class_attributes(
    const dogen::dia::attribute a, processed_object& po) {

    const auto& values(a.values());
    if (values.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Object has no UML attributes.";
        return;
    }

    for (const auto& v : values) {
        using dogen::dia::composite;
        const auto& c(get_attribute_value<composite>(v, dia_composite));
        if (c.type() != dia_uml_attribute) {
            BOOST_LOG_SEV(lg, error) << "Expected composite type "
                                     << " to be " << dia_uml_attribute
                                     << "but was " << c.type();

            BOOST_THROW_EXCEPTION(building_error(uml_attribute_expected));
        }
        BOOST_LOG_SEV(lg, debug) << "Found composite of type " << c.type();

        processed_attribute pa;
        for (const auto a : c.value()) {
            if (a->name() == dia_name)
                pa.name(parse_string_attribute(*a));
            else if (a->name() == dia_type)
                pa.type(parse_string_attribute(*a));
            else if (a->name() == dia_comment)
                pa.comment(create_processed_comment(*a));
            else
                BOOST_LOG_SEV(lg, warn) << "Ignoring attribute: " << a->name();
        }
        po.attributes().push_back(pa);
    }
}

void processed_object_factory::
require_yarn_type_not_set(const yarn_element_types yet) {
    if (yet == yarn_element_types::invalid)
        return;

    BOOST_LOG_SEV(lg, warn) << too_many_yarn_types;
    BOOST_THROW_EXCEPTION(building_error(too_many_yarn_types));
}

void processed_object_factory::
parse_as_stereotypes(dogen::dia::attribute a, processed_object& po) {
    const auto s(parse_string_attribute(a));

    using utility::string::splitter;
    const auto stereotypes(splitter::split_csv(s));

    for (const auto& stereotype : stereotypes) {
        if (stereotype == enumeration) {
            require_yarn_type_not_set(po.yarn_element_type());
            po.yarn_element_type(yarn_element_types::enumeration);
        } else if (stereotype == primitive) {
            require_yarn_type_not_set(po.yarn_element_type());
            po.yarn_element_type(yarn_element_types::primitive);
        } else if (stereotype == exception) {
            require_yarn_type_not_set(po.yarn_element_type());
            po.yarn_element_type(yarn_element_types::exception);
        } else if (stereotype == object_template) {
            require_yarn_type_not_set(po.yarn_element_type());
            po.yarn_element_type(yarn_element_types::object_template);
        } else if (stereotype == object) {
            require_yarn_type_not_set(po.yarn_element_type());
            po.yarn_element_type(yarn_element_types::object);
        } else
            po.stereotypes().push_back(stereotype);
    }
}

void processed_object_factory::
parse_attributes(const dogen::dia::object& o, processed_object& po) {
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

void processed_object_factory::
handle_yarn_element_type(processed_object& po) {
    /*
     * If its already setup there's nothing for us to do. This is the
     * case if the user has populated the stereotypes with an element.
     */
    if (po.yarn_element_type() != yarn_element_types::invalid)
        return;

    /*
     * If we're a UML class, map it to a yarn object. All other cases
     * don't have a mapping.
     */
    if (po.dia_object_type() == dia_object_types::uml_class)
        po.yarn_element_type(yarn_element_types::object);
    else
        po.yarn_element_type(yarn_element_types::not_applicable);
}

processed_object processed_object_factory::make(const dogen::dia::object& o) {
    BOOST_LOG_SEV(lg, debug) << "Processing dia object " << o.id();

    processed_object r;
    r.id(o.id());
    r.dia_object_type(parse_object_type(o.type()));

    if (o.child_node())
        r.child_node_id(o.child_node()->parent());

    parse_connections(o, r);
    parse_attributes(o, r);
    handle_yarn_element_type(r);

    BOOST_LOG_SEV(lg, debug) << "Finished processing dia object";
    return r;
}

std::list<processed_object>
processed_object_factory::make(const dogen::dia::diagram& d) {
    std::list<processed_object> r;
    for (const auto& l : d.layers()) {
        for (const auto& o : l.objects())
            r.push_back(make(o));
    }
    return r;
}

} } }
