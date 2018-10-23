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
#ifndef DOGEN_UTILITY_XML_NODE_TYPES_HPP
#define DOGEN_UTILITY_XML_NODE_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::utility::xml {

/**
 * @brief A given set of XML data is modeled as a tree of
 * nodes. This enumeration specifies the different node types.
 */
enum class node_types : unsigned int {
    none = 0, ///< Read method has not yet been called
    element = 1, ///< An element's start tag
    attribute = 2, ///< An attribute (e.g.: id='123' )
    text = 3, ///< The text content of a node.
    cdata = 4, ///< A CDATA section (e.g.: <![CDATA[escaped text]]>)
    entity_reference = 5, ///< A reference to an entity
    entity = 6, ///< An entity declaration (e.g.: <!ENTITY...>)
    processing_instruction = 7, ///< A processing instruction
    comment = 8, ///< A comment
    document = 9, ///< A document object
    document_type = 10, ///< The document type declaration
    document_fragment = 11, ///< A document fragment
    notation = 12, ///< A notation in the DTD
    whitespace = 13, ///< White space between markup
    significant_whitespace = 14, /**< White space between markup in a
                                  * mixed content model or white space
                                  * within the xml:space="preserve"
                                  * scope
                                  */
    end_element = 15, ///< An end element tag
    end_entity = 16, /**< When we get to the end of the entity
                      * replacement as a result of a call to
                      * ResolveEntity.
                      */
    xml_declaration = 17 ///< The XML declaration
};

}

#endif
