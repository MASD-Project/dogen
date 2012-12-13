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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/xml/node_types_io.hpp"
#include "dogen/dia/xml/dia_xml_exception.hpp"
#include "dogen/dia/xml/hydrator.hpp"

namespace {

static dogen::utility::log::logger
lg(dogen::utility::log::logger_factory("hydrator"));

// exception messages
const std::string unexpected_element("Unexpected element: ");
const std::string unexpected_eod("Unexpected end of document");
const std::string unsupported_value("Unsupported attribute value: ");
const std::string unexpected_connection_type("Unexpected connection type: ");
const std::string expected_self_closing("Expected self-closing: ");
const std::string expected_one_inner_composite("Expected only one inner composite");

// dia XML element names
const std::string dia_diagramdata("dia:diagramdata");
const std::string dia_diagram("dia:diagram");
const std::string dia_layer("dia:layer");
const std::string dia_child_node("dia:childnode");
const std::string dia_attribute("dia:attribute");
const std::string dia_color("dia:color");
const std::string dia_real("dia:real");
const std::string dia_point("dia:point");
const std::string dia_rectangle("dia:rectangle");
const std::string dia_integer("dia:int");
const std::string dia_boolean("dia:boolean");
const std::string dia_string("dia:string");
const std::string dia_font("dia:font");
const std::string dia_enum("dia:enum");
const std::string dia_composite("dia:composite");
const std::string dia_object("dia:object");
const std::string dia_connections("dia:connections");
const std::string dia_connection("dia:connection");

// dia XML attribute names
const std::string dia_name("name");
const std::string dia_val("val");
const std::string dia_family("family");
const std::string dia_style("style");
const std::string dia_type("type");
const std::string dia_version("version");
const std::string dia_id("id");
const std::string dia_parent("parent");
const std::string dia_layer_visible("visible");
const std::string dia_layer_active("active");
const std::string dia_handle("handle");
const std::string dia_to("to");
const std::string dia_connection_slot("connection");

// useful constants
const bool skip_whitespace(true);

}

namespace dogen {
namespace dia {
namespace xml {

using namespace dogen::utility::log;

hydrator::hydrator(boost::filesystem::path file_name)
    : file_name_(file_name),
      reader_(file_name, skip_whitespace) { }

void hydrator::validate_current_element(std::string name) const {
    if (reader_.name() != name ||
        reader_.node_type() != utility::xml::node_types::element)
        BOOST_THROW_EXCEPTION(xml::exception(unexpected_element + reader_.name()));
}

void hydrator::next_element(std::string name) {
    if (!reader_.read())
        BOOST_THROW_EXCEPTION(xml::exception(unexpected_eod));

    validate_current_element(name);
}

bool hydrator::is_attribute_value(std::string name) const {
    return
        name == dia_color || name == dia_integer || name == dia_real ||
        name == dia_point ||name == dia_boolean || name == dia_string ||
        name == dia_rectangle || name == dia_font || name == dia_enum ||
        name == dia_composite;
}

bool hydrator::is_start_element(std::string element_name) const {
    return reader_.is_start_element() && reader_.name() == element_name;
}

bool hydrator::is_end_element(std::string element_name) const {
    return reader_.is_end_element() && reader_.name() == element_name;
}

void hydrator::validate_self_closing() const {
    const bool is_self_closing(reader_.is_empty());
    if (!is_self_closing) {
        using xml::exception;
        BOOST_THROW_EXCEPTION(exception(expected_self_closing + reader_.name()));
    }
}

std::string hydrator::read_xml_string_attribute(std::string name) {
    return reader_.get_attribute<std::string>(name);
}

int hydrator::read_xml_int_attribute(std::string name) {
    return reader_.get_attribute<int>(name);
}

bool hydrator::read_xml_bool_attribute(std::string name) {
    return reader_.get_attribute<bool>(name);
}

bool hydrator::try_read_xml_bool_attribute(std::string name) {
    if (reader_.has_attribute(name))
        return reader_.get_attribute<bool>(name);
    return false;
}

child_node hydrator::read_child_node() {
    validate_current_element(dia_child_node);

    child_node child_node;
    child_node.parent(read_xml_string_attribute(dia_parent));
    validate_self_closing();

    if (!reader_.read())
        BOOST_THROW_EXCEPTION(xml::exception(unexpected_eod));

    return child_node;
}

template<typename AttributeValue>
AttributeValue hydrator::read_attribute_value() {
    AttributeValue result;
    result.value(read_xml_string_attribute(dia_val));
    reader_.skip();

    BOOST_LOG_SEV(lg, debug) << "Reading generic attribute value: "
                             << result.value();
    return result;
}

template<>
dia::string hydrator::read_attribute_value() {
    reader_.read();
    dia::string result;
    result.value(reader_.value<std::string>());
    reader_.read();
    reader_.skip();

    BOOST_LOG_SEV(lg, debug) << "Reading string attribute value: "
                             << result.value();
    return result;
}

template<>
font hydrator::read_attribute_value() {
    font result;
    result.family(read_xml_string_attribute(dia_family));
    result.style(read_xml_string_attribute(dia_style));
    result.name(read_xml_string_attribute(dia_name));
    reader_.skip();

    BOOST_LOG_SEV(lg, debug) << "Reading font attribute value: "
                             << result.name();
    return result;
}

template<>
composite hydrator::read_attribute_value() {
    composite result;
    result.type(read_xml_string_attribute(dia_type));
    BOOST_LOG_SEV(lg, debug) << "Reading composite attribute value: "
                             << result.type();

    const bool is_self_closing(reader_.is_empty());
    reader_.read();

    if (is_self_closing)
        return result;

    typedef boost::shared_ptr<attribute> attribute_ptr;
    std::vector<attribute_ptr> attributes;

    typedef boost::shared_ptr<composite> composite_ptr;
    composite_ptr inner_composite;
    do {
        if (is_start_element(dia_composite)) {
            validate_self_closing();

            if (inner_composite) {
                using xml::exception;
                BOOST_THROW_EXCEPTION(exception(expected_one_inner_composite));
            }

            inner_composite = composite_ptr(new composite());
            inner_composite->type(read_xml_string_attribute(dia_type));
            result.inner_composite(inner_composite);
            reader_.skip();
        } else if (is_start_element(dia_attribute)) {
            attribute_ptr ptr(new attribute(read_attribute()));
            attributes.push_back(ptr);
        } else {
            BOOST_THROW_EXCEPTION(xml::exception(unexpected_element));
        }
    } while (!is_end_element(dia_composite));
    result.value(attributes);
    reader_.skip(); // skip the composite end element

    return result;
}

attribute hydrator::read_attribute() {
    validate_current_element(dia_attribute);

    attribute attribute;
    attribute.name(read_xml_string_attribute(dia_name));
    BOOST_LOG_SEV(lg, debug) << "Reading attribute: " << attribute.name();
    const bool is_self_closing(reader_.is_empty());

    if (!reader_.read())
        BOOST_THROW_EXCEPTION(xml::exception(unexpected_eod));

    if (is_self_closing)
        return attribute; // no more content to read related to this attribute

    std::vector<attribute::attribute_value> values;
    while (reader_.is_start_element()) {
        // are we inside an attribute? the attribute values below
        // should only appear if we are.
        const std::string name(reader_.name());
        if (!is_attribute_value(name)) {
            BOOST_THROW_EXCEPTION(xml::exception(unsupported_value + name));
        }

        if (name == dia_color)
            values.push_back(read_attribute_value<color>());
        else if (name == dia_integer)
            values.push_back(read_attribute_value<integer>());
        else if (name == dia_real)
            values.push_back(read_attribute_value<real>());
        else if (name == dia_point)
            values.push_back(read_attribute_value<point>());
        else if (name == dia_boolean)
            values.push_back(read_attribute_value<boolean>());
        else if (name == dia_string)
            values.push_back(read_attribute_value<string>());
        else if (name == dia_rectangle)
            values.push_back(read_attribute_value<rectangle>());
        else if (name == dia_font)
            values.push_back(read_attribute_value<font>());
        else if (name == dia_enum)
            values.push_back(read_attribute_value<enumeration>());
        else if (name == dia_composite)
            values.push_back(read_attribute_value<composite>());
    }
    attribute.values(values);

    // if we were not on a self-closing attribute tag, then we need to
    // consume the attribute end element.
    if (is_end_element(dia_attribute))
        reader_.read();

    return attribute;
}

connection hydrator::read_connection() {
    validate_current_element(dia_connection);
    connection r;

    r.handle(read_xml_string_attribute(dia_handle));
    r.to(read_xml_string_attribute(dia_to));
    r.connection_slot(read_xml_string_attribute(dia_connection_slot));
    reader_.skip();
    return r;
}

std::vector<connection> hydrator::read_connections() {
    validate_current_element(dia_connections);
    reader_.read();

    std::vector<connection> r;
    do {
        if (!is_start_element(dia_connection)) {
            BOOST_LOG_SEV(lg, error) << unexpected_connection_type
                                     << reader_.name();
            BOOST_THROW_EXCEPTION(xml::exception(unexpected_connection_type +
                reader_.name()));
        }
        r.push_back(read_connection());
    } while (!is_end_element(dia_connections));
    reader_.read();

    BOOST_LOG_SEV(lg, debug) << "Object has " << r.size() << " connections";
    return r;
}

object hydrator::read_object() {
    validate_current_element(dia_object);
    object object;

    object.type(read_xml_string_attribute(dia_type));
    object.version(read_xml_int_attribute(dia_version));
    object.id(read_xml_string_attribute(dia_id));
    BOOST_LOG_SEV(lg, debug) << "Reading object: '" << object.id()
                             << "' of type: " << object.type();

    if (!reader_.read())
        BOOST_THROW_EXCEPTION(xml::exception(unexpected_eod));

    std::vector<attribute> attributes;
    do {
        if (is_start_element(dia_attribute))
            attributes.push_back(read_attribute());
        else if (is_start_element(dia_child_node))
            object.child_node(read_child_node());
        else if (is_start_element(dia_connections)) {
            object.connections(read_connections());
        } else {
            BOOST_LOG_SEV(lg, warn) << "Skipping element: '" << reader_.name();
            reader_.skip();
        }
    } while (!is_end_element(dia_object));

    reader_.read();
    object.attributes(attributes);

    BOOST_LOG_SEV(lg, debug) << "Read object: " << object.id();
    return object;
}

layer hydrator::read_layer() {
    validate_current_element(dia_layer);

    layer layer;
    layer.name(read_xml_string_attribute(dia_name));
    layer.visible(try_read_xml_bool_attribute(dia_layer_visible));
    layer.active(try_read_xml_bool_attribute(dia_layer_active));
    BOOST_LOG_SEV(lg, debug) << "Reading layer: " << layer.name();

    std::vector<object> objects;
    const bool is_self_closing(reader_.is_empty());

    reader_.read();
    if (!is_self_closing) {
        do {
            objects.push_back(read_object());
        } while (!is_end_element(dia_layer));
        reader_.read();
    }

    layer.objects(objects);
    BOOST_LOG_SEV(lg, debug) << "Read layer: " << layer.name();
    return layer;
}

diagram_data hydrator::read_diagram_data() {
    next_element(dia_diagramdata);
    diagram_data diagram_data;
    BOOST_LOG_SEV(lg, debug) << "Reading diagram data.";

    if (!reader_.read())
        BOOST_THROW_EXCEPTION(xml::exception(unexpected_eod));

    std::vector<attribute> attributes;
    do {
        attributes.push_back(read_attribute());
    } while (!is_end_element(dia_diagramdata));

    reader_.read();

    diagram_data.attributes(attributes);
    BOOST_LOG_SEV(lg, debug) << "Read diagram data.";
    return diagram_data;
}

diagram hydrator::read_diagram() {
    next_element(dia_diagram);
    BOOST_LOG_SEV(lg, debug) << "Reading diagram.";

    diagram diagram;
    diagram.diagram_data(read_diagram_data());
    std::vector<layer> layers;

    do {
        layers.push_back(read_layer());
    } while (!is_end_element(dia_diagram));

    diagram.layers(layers);
    BOOST_LOG_SEV(lg, debug) << "Read diagram.";
    return diagram;
}

diagram hydrator::hydrate() {
    BOOST_LOG_SEV(lg, debug) << "Hydrating dia file: " << file_name_;
    return read_diagram();
}

} } }
