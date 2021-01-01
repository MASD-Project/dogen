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
#ifndef DOGEN_CODEC_TYPES_HELPERS_DIA_TO_CODEC_PROJECTOR_HPP
#define DOGEN_CODEC_TYPES_HELPERS_DIA_TO_CODEC_PROJECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen.dia/types/entities/attribute_fwd.hpp"
#include "dogen.dia/types/entities/object_fwd.hpp"
#include "dogen.dia/types/entities/attribute_fwd.hpp"
#include "dogen.dia/types/entities/composite_fwd.hpp"
#include "dogen.dia/types/entities/diagram_fwd.hpp"
#include "dogen.codec/types/entities/object_fwd.hpp"
#include "dogen.codec/types/entities/comment_fwd.hpp"

namespace dogen::codec::helpers {

/**
 * @brief Projects dia objects into the codec space.
 */
class dia_to_codec_projector final {
public:
    /**
     * @brief Processes comments in dia diagrams.
     *
     * Comments can be stored in class objects, member functions, note
     * objects, etc.
     *
     * Any line starting with the well defined marker @e #DOGEN -
     * known as the instruction marker - will be interpreted as
     * carrying an instruction in a key-value pair form, where the key
     * and the value are separated by the assignment operator @e =.
     *
     * @note public just for testing purposes.
     */
    static entities::comment process_comment(const std::string& c);

private:
    /**
     * @brief Parses the dia attribute as a string, returning its value.
     */
    static std::string parse_string_attribute(
        const dogen::dia::entities::attribute& a);

    /**
     * @brief Makes a comment from the input attribute.
     *
     * @pre Attribute must be of type string.
     */
    static entities::comment
    create_comment(const dogen::dia::entities::attribute& a);

    /**
     * @brief Parse connection information from Dia object.
     */
    static void parse_connections(const dogen::dia::entities::object& o,
        entities::object& co);

    /**
     * @brief Parse the attribute as a Dia text.
     */
    static void parse_as_dia_text(const dogen::dia::entities::attribute a,
        entities::object& o);

    /**
     * @brief Processes the raw Dia stereotypes.
     */
    static void parse_as_stereotypes(dogen::dia::entities::attribute a,
        entities::object& o);

    /**
     * @brief Parses the contents of the Dia attribute assuming it
     * contains UML attributes.
     */
    static void parse_as_class_attributes(
        const dogen::dia::entities::attribute a, entities::object& o);

    /**
     * @brief Parses the Dia attributes from the Dia object.
     */
    static void parse_attributes(const dogen::dia::entities::object& o,
        entities::object& co);

public:
    /**
     * @brief Projects a dia object into a codec object.
     */
    static entities::object project(const dogen::dia::entities::object& o);

    /**
     * @brief Generates a codec object representation of the Dia
     * diagram.
     */
    static std::list<entities::object>
    project(const dogen::dia::entities::diagram& d);
};

}

#endif
