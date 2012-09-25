/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/utility/xml/node_types_io.hpp"
#include "dogen/dia/xml/dia_xml_exception.hpp"
#include "dogen/dia/xml/hydrator.hpp"

namespace {

// exception messages
const std::string unexpected_element("Unexpected element: ");
const std::string unexpected_eod("Unexpected end of document");
const std::string unsupported_value("Unsupported attribute value: ");
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

// useful constants
const bool skip_whitespace(true);

}

namespace dogen {
namespace dia {
namespace xml {

hydrator::hydrator(boost::filesystem::path file_name)
    : file_name_(file_name),
      reader_(file_name, skip_whitespace) { }

void hydrator::validate_current_element(std::string name) const {
    if (reader_.name() != name ||
        reader_.node_type() != utility::xml::node_types::element)
        throw xml::exception(unexpected_element + reader_.name());
}

void hydrator::next_element(std::string name) {
    if (!reader_.read())
        throw xml::exception(unexpected_eod);

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
        throw exception(expected_self_closing + reader_.name());
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
        throw xml::exception(unexpected_eod);

    return child_node;
}

template<typename AttributeValue>
AttributeValue hydrator::read_attribute_value() {
    AttributeValue result;
    result.value(read_xml_string_attribute(dia_val));
    reader_.skip();
    return result;
}

template<>
dia::string hydrator::read_attribute_value() {
    reader_.read();
    dia::string result;
    result.value(reader_.value<std::string>());
    reader_.read();
    reader_.skip();
    return result;
}

template<>
font hydrator::read_attribute_value() {
    font result;
    result.family(read_xml_string_attribute(dia_family));
    result.style(read_xml_string_attribute(dia_style));
    result.name(read_xml_string_attribute(dia_name));
    reader_.skip();
    return result;
}

template<>
std::vector<composite> hydrator::read_attribute_value() {
    // attributes can have values with multiple composites. we need to
    // loop and read them all.
    std::vector<composite> result;
    while (is_start_element(dia_composite)) {
        composite c;
        c.type(read_xml_string_attribute(dia_type));

        const bool is_self_closing(reader_.is_empty());
        reader_.read();

        if (is_self_closing) {
            result.push_back(c);
            continue;
        }

        typedef boost::shared_ptr<attribute> attribute_ptr;
        std::vector<attribute_ptr> attributes;

        typedef boost::shared_ptr<composite> composite_ptr;
        composite_ptr inner_composite;
        do {
            if (is_start_element(dia_composite)) {
                validate_self_closing();

                if (inner_composite) {
                    using xml::exception;
                    throw exception(expected_one_inner_composite);
                }

                inner_composite = composite_ptr(new composite());
                inner_composite->type(read_xml_string_attribute(dia_type));
                c.inner_composite(inner_composite);
                reader_.skip();
            } else if (is_start_element(dia_attribute)) {
                attribute_ptr ptr(new attribute(read_attribute()));
                attributes.push_back(ptr);
            } else {
                throw xml::exception(unexpected_element);
            }
        } while (!is_end_element(dia_composite));
        c.value(attributes);
        result.push_back(c);
        reader_.skip(); // skip the composite end element
    }
    return result;
}

attribute hydrator::read_attribute() {
    validate_current_element(dia_attribute);

    attribute attribute;
    attribute.name(read_xml_string_attribute(dia_name));
    const bool is_self_closing(reader_.is_empty());

    if (!reader_.read())
        throw xml::exception(unexpected_eod);

    if (is_self_closing)
        return attribute; // no more content to read related to this attribute

    if (reader_.is_start_element()) {
        // are we inside an attribute? the attribute values below
        // should only appear if we are.
        const std::string name(reader_.name());
        if (!is_attribute_value(name))
            throw xml::exception(unsupported_value + name);

        if (name == dia_color)
            attribute.value(read_attribute_value<color>());
        else if (name == dia_integer)
            attribute.value(read_attribute_value<integer>());
        else if (name == dia_real)
            attribute.value(read_attribute_value<real>());
        else if (name == dia_point)
            attribute.value(read_attribute_value<point>());
        else if (name == dia_boolean)
            attribute.value(read_attribute_value<boolean>());
        else if (name == dia_string)
            attribute.value(read_attribute_value<string>());
        else if (name == dia_rectangle)
            attribute.value(read_attribute_value<rectangle>());
        else if (name == dia_font)
            attribute.value(read_attribute_value<font>());
        else if (name == dia_enum)
            attribute.value(read_attribute_value<enumeration>());
        else if (name == dia_composite)
            attribute.value(
                read_attribute_value<std::vector<composite> >());
    }

    // if we were not on a self-closing attribute tag, then we need to
    // consume the attribute end element.
    if (is_end_element(dia_attribute))
        reader_.read();

    return attribute;
}

object hydrator::read_object() {
    validate_current_element(dia_object);
    object object;

    object.type(read_xml_string_attribute(dia_type));
    object.version(read_xml_int_attribute(dia_version));
    object.id(read_xml_string_attribute(dia_id));

    if (!reader_.read())
        throw xml::exception(unexpected_eod);

    std::vector<attribute> attributes;
    do {
        if (is_start_element(dia_attribute))
            attributes.push_back(read_attribute());
        else if (is_start_element(dia_child_node))
            object.child_node(read_child_node());
        else
            reader_.skip();
    } while (!is_end_element(dia_object));

    reader_.read();
    object.attributes(attributes);
    return object;
}

layer hydrator::read_layer() {
    validate_current_element(dia_layer);

    layer layer;
    layer.name(read_xml_string_attribute(dia_name));
    layer.visible(try_read_xml_bool_attribute(dia_layer_visible));
    layer.active(try_read_xml_bool_attribute(dia_layer_active));

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
    return layer;
}

diagram_data hydrator::read_diagram_data() {
    next_element(dia_diagramdata);
    diagram_data diagram_data;

    if (!reader_.read())
        throw xml::exception(unexpected_eod);

    std::vector<attribute> attributes;
    do {
        attributes.push_back(read_attribute());
    } while (!is_end_element(dia_diagramdata));

    reader_.read();

    diagram_data.attributes(attributes);
    return diagram_data;
}

diagram hydrator::read_diagram() {
    next_element(dia_diagram);

    diagram diagram;
    diagram.diagram_data(read_diagram_data());
    std::vector<layer> layers;

    do {
        layers.push_back(read_layer());
    } while (!is_end_element(dia_diagram));

    diagram.layers(layers);
    return diagram;
}

diagram hydrator::hydrate() {
    return read_diagram();
}

} } }
