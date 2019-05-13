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
#include <string>
#include <ostream>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/exception/invalid_enum_value.hpp"
#include "dogen.utility/types/xml/node_types_io.hpp"

namespace {

const std::string none("none");
const std::string element("element");
const std::string attribute("attribute");
const std::string text("text");
const std::string cdata("cdata");
const std::string entity_reference("entity_reference");
const std::string entity("entity");
const std::string processing_instruction("processing_instruction");
const std::string comment("comment");
const std::string document("document");
const std::string document_type("document_type_declaration");
const std::string document_fragment("document_fragment");
const std::string notation("notation");
const std::string whitespace("whitespace");
const std::string significant_whitespace("significant_whitespace");
const std::string end_element("end_element");
const std::string end_entity("end_entity");
const std::string xml_declaration("xml_declaration");

const std::string error_message("Invalid or unexpected node type");

}

namespace dogen::utility::xml {

std::ostream& operator<<(std::ostream& stream, node_types value) {
    switch (value) {
    case node_types::none: return stream << none;
    case node_types::element: return stream << element;
    case node_types::attribute: return stream << attribute;
    case node_types::text: return stream << text;
    case node_types::cdata: return stream << cdata;
    case node_types::entity_reference: return stream << entity_reference;
    case node_types::entity: return stream << entity;
    case node_types::processing_instruction:
        return stream << processing_instruction;
    case node_types::comment: return stream << comment;
    case node_types::document: return stream << document;
    case node_types::document_type: return stream << document_type;
    case node_types::document_fragment: return stream << document_fragment;
    case node_types::notation: return stream << notation;
    case node_types::whitespace: return stream << whitespace;
    case node_types::significant_whitespace:
        return stream << significant_whitespace;
    case node_types::end_element: return stream << end_element;
    case node_types::end_entity: return stream << end_entity;
    case node_types::xml_declaration: return stream << xml_declaration;
    }
    BOOST_THROW_EXCEPTION(dogen::utility::exception::invalid_enum_value(error_message));
}

}
