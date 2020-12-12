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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/xml/text_reader.hpp"
#include "dogen.utility/types/xml/node_types_io.hpp"
#include "dogen.dia/types/entities/composite.hpp"
#include "dogen.dia/types/entities/rectangle.hpp"
#include "dogen.dia/types/entities/boolean.hpp"
#include "dogen.dia/types/entities/color.hpp"
#include "dogen.dia/types/entities/enumeration.hpp"
#include "dogen.dia/types/entities/font.hpp"
#include "dogen.dia/types/entities/integer.hpp"
#include "dogen.dia/types/entities/point.hpp"
#include "dogen.dia/types/entities/real.hpp"
#include "dogen.dia/types/entities/string.hpp"
#include "dogen.dia/types/entities/attribute.hpp"
#include "dogen.dia/types/entities/child_node.hpp"
#include "dogen.dia/types/entities/connection.hpp"
#include "dogen.dia/types/entities/object.hpp"
#include "dogen.dia/types/transforms/transformation_error.hpp"
#include "dogen.dia/types/transforms/string_to_diagram_transform.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("dia.transforms.diagram string_to_diagram_transform"));

// exception messages
const std::string unexpected_element("Unexpected element: ");
const std::string unsupported_value("Unsupported attribute value: ");
const std::string unexpected_connection_type("Unexpected connection type: ");
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

namespace dogen::dia::transforms {

using namespace dogen::dia::entities;

class hydrator {
public:
    hydrator(const std::string& s);

private:
    bool is_attribute_value(const std::string& name) const;

private:
    std::string read_xml_string_attribute(const std::string& name);
    int read_xml_int_attribute(const std::string& name);
    bool read_xml_bool_attribute(const std::string& name);
    bool try_read_xml_bool_attribute(const std::string& name);

    child_node read_child_node();
    connection read_connection();
    std::vector<connection> read_connections();
    object read_object();
    template<typename AttributeValue> AttributeValue read_attribute_value();
    attribute read_attribute();
    layer read_layer();
    diagram_data read_diagram_data();
    diagram read_diagram();

public:
    diagram hydrate();

private:
    utility::xml::text_reader reader_;
};

hydrator::hydrator(const std::string& s)
    : reader_(s, skip_whitespace) { }

bool hydrator::is_attribute_value(const std::string& name) const {
    return
        name == dia_color || name == dia_integer || name == dia_real ||
        name == dia_point ||name == dia_boolean || name == dia_string ||
        name == dia_rectangle || name == dia_font || name == dia_enum ||
        name == dia_composite;
}

std::string hydrator::read_xml_string_attribute(const std::string& name) {
    return reader_.get_attribute<std::string>(name);
}

int hydrator::read_xml_int_attribute(const std::string& name) {
    return reader_.get_attribute<int>(name);
}

bool hydrator::read_xml_bool_attribute(const std::string& name) {
    return reader_.get_attribute<bool>(name);
}

bool hydrator::try_read_xml_bool_attribute(const std::string& name) {
    if (reader_.has_attribute(name))
        return reader_.get_attribute<bool>(name);
    return false;
}

child_node hydrator::read_child_node() {
    reader_.validate_current_element(dia_child_node);

    child_node child_node;
    child_node.parent(read_xml_string_attribute(dia_parent));
    reader_.validate_self_closing();
    reader_.move_next();
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
dia::entities::string hydrator::read_attribute_value() {
    reader_.read();
    dia::entities::string result;
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
        if (reader_.is_start_element(dia_composite)) {
            reader_.validate_self_closing();

            if (inner_composite) {
                BOOST_LOG_SEV(lg, error) << expected_one_inner_composite;
                BOOST_THROW_EXCEPTION(
                    transformation_error(expected_one_inner_composite));
            }

            inner_composite = composite_ptr(new composite());
            inner_composite->type(read_xml_string_attribute(dia_type));
            result.inner_composite(inner_composite);
            reader_.skip();
        } else if (reader_.is_start_element(dia_attribute)) {
            attribute_ptr ptr(new attribute(read_attribute()));
            attributes.push_back(ptr);
        } else {
            BOOST_LOG_SEV(lg, error) << unexpected_element;
            BOOST_THROW_EXCEPTION(transformation_error(unexpected_element));
        }
    } while (!reader_.is_end_element(dia_composite));
    result.value(attributes);
    reader_.skip(); // skip the composite end element

    return result;
}

attribute hydrator::read_attribute() {
    reader_.validate_current_element(dia_attribute);

    attribute attribute;
    attribute.name(read_xml_string_attribute(dia_name));
    BOOST_LOG_SEV(lg, debug) << "Reading attribute: " << attribute.name();
    const bool is_self_closing(reader_.is_empty());
    reader_.move_next();
    if (is_self_closing)
        return attribute; // no more content to read related to this attribute

    while (reader_.is_start_element()) {
        // are we inside an attribute? the attribute values below
        // should only appear if we are.
        const std::string name(reader_.name());
        if (!is_attribute_value(name)) {
            BOOST_LOG_SEV(lg, error) << unsupported_value << name;
            BOOST_THROW_EXCEPTION(transformation_error(unsupported_value + name));
        }

        if (name == dia_color)
            attribute.values().push_back(read_attribute_value<color>());
        else if (name == dia_integer)
            attribute.values().push_back(read_attribute_value<integer>());
        else if (name == dia_real)
            attribute.values().push_back(read_attribute_value<real>());
        else if (name == dia_point)
            attribute.values().push_back(read_attribute_value<point>());
        else if (name == dia_boolean)
            attribute.values().push_back(read_attribute_value<boolean>());
        else if (name == dia_string)
            attribute.values().push_back(read_attribute_value<string>());
        else if (name == dia_rectangle)
            attribute.values().push_back(read_attribute_value<rectangle>());
        else if (name == dia_font)
            attribute.values().push_back(read_attribute_value<font>());
        else if (name == dia_enum)
            attribute.values().push_back(read_attribute_value<enumeration>());
        else if (name == dia_composite)
            attribute.values().push_back(read_attribute_value<composite>());
    }

    // if we were not on a self-closing attribute tag, then we need to
    // consume the attribute end element.
    if (reader_.is_end_element(dia_attribute))
        reader_.read();

    return attribute;
}

connection hydrator::read_connection() {
    reader_.validate_current_element(dia_connection);
    connection r;

    r.handle(read_xml_string_attribute(dia_handle));
    r.to(read_xml_string_attribute(dia_to));
    r.connection_slot(read_xml_string_attribute(dia_connection_slot));
    reader_.skip();
    return r;
}

std::vector<connection> hydrator::read_connections() {
    reader_.validate_current_element(dia_connections);
    reader_.read();

    std::vector<connection> r;
    do {
        if (!reader_.is_start_element(dia_connection)) {
            BOOST_LOG_SEV(lg, error) << unexpected_connection_type
                                     << reader_.name();
            BOOST_THROW_EXCEPTION(transformation_error(
                    unexpected_connection_type + reader_.name()));
        }
        r.push_back(read_connection());
    } while (!reader_.is_end_element(dia_connections));
    reader_.read();

    BOOST_LOG_SEV(lg, debug) << "Object has " << r.size() << " connections";
    return r;
}

object hydrator::read_object() {
    reader_.validate_current_element(dia_object);
    object object;

    object.type(read_xml_string_attribute(dia_type));
    object.version(read_xml_int_attribute(dia_version));
    object.id(read_xml_string_attribute(dia_id));
    BOOST_LOG_SEV(lg, debug) << "Reading object: '" << object.id()
                             << "' of type: " << object.type();

    reader_.move_next();

    std::vector<attribute> attributes;
    do {
        if (reader_.is_start_element(dia_attribute))
            attributes.push_back(read_attribute());
        else if (reader_.is_start_element(dia_child_node))
            object.child_node(read_child_node());
        else if (reader_.is_start_element(dia_connections)) {
            object.connections(read_connections());
        } else {
            BOOST_LOG_SEV(lg, warn) << "Skipping element: '" << reader_.name();
            reader_.skip();
        }
    } while (!reader_.is_end_element(dia_object));

    reader_.read();
    object.attributes(attributes);

    BOOST_LOG_SEV(lg, debug) << "Read object: " << object.id();
    return object;
}

layer hydrator::read_layer() {
    reader_.validate_current_element(dia_layer);

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
        } while (!reader_.is_end_element(dia_layer));
        reader_.read();
    }

    layer.objects(objects);
    BOOST_LOG_SEV(lg, debug) << "Read layer: " << layer.name();
    return layer;
}

diagram_data hydrator::read_diagram_data() {
    reader_.next_element(dia_diagramdata);
    diagram_data diagram_data;
    BOOST_LOG_SEV(lg, debug) << "Reading diagram data.";

    reader_.move_next();

    std::vector<attribute> attributes;
    do {
        attributes.push_back(read_attribute());
    } while (!reader_.is_end_element(dia_diagramdata));

    reader_.read();

    diagram_data.attributes(attributes);
    BOOST_LOG_SEV(lg, debug) << "Read diagram data.";
    return diagram_data;
}

diagram hydrator::read_diagram() {
    reader_.next_element(dia_diagram);
    BOOST_LOG_SEV(lg, debug) << "Reading diagram.";

    diagram diagram;
    diagram.diagram_data(read_diagram_data());
    std::vector<layer> layers;

    do {
        layers.push_back(read_layer());
    } while (!reader_.is_end_element(dia_diagram));

    diagram.layers(layers);
    BOOST_LOG_SEV(lg, debug) << "Read diagram.";
    return diagram;
}

diagram hydrator::hydrate() {
    BOOST_LOG_SEV(lg, debug) << "Hydrating dia diagram from string.";
    return read_diagram();
}

entities::diagram string_to_diagram_transform::apply(const std::string& s) {
    hydrator h(s);
    return h.hydrate();
}

}
