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
#ifndef DOGEN_CODEC_DIA_TYPES_PROCESSED_OBJECT_FACTORY_HPP
#define DOGEN_CODEC_DIA_TYPES_PROCESSED_OBJECT_FACTORY_HPP

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
#include "dogen.codec.dia/types/dia_object_types.hpp"
#include "dogen.codec/types/entities/object_fwd.hpp"
#include "dogen.codec/types/entities/comment_fwd.hpp"

namespace dogen::codec::dia {

/**
 * @brief Processes dia objects into an intermediate format.
 */
class processed_object_factory {
private:
    /**
     * @brief Parses the dia attribute as a string, returning its value.
     */
    static std::string parse_string_attribute(
        const dogen::dia::entities::attribute& a);

    /**
     * @brief Makes a processed comment from the input attribute.
     *
     * @pre Attribute must be of type string.
     */
    static entities::comment
    create_processed_comment(const dogen::dia::entities::attribute& a);

    /**
     * @brief Given a string with a dia object type, returns the
     * appropriate enum.
     */
    static dia_object_types parse_object_type(const std::string& ot);

    /**
     * @brief Parse connection information from Dia object.
     */
    static void parse_connections(const dogen::dia::entities::object& o,
        entities::object& po);

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
        entities::object& po);

public:
    /**
     * @brief Generates a processed object.
     */
    static entities::object make(const dogen::dia::entities::object& o);

    /**
     * @brief Generates a processed object representation of the
     * diagram.
     */
    static std::list<entities::object>
    make(const dogen::dia::entities::diagram& d);
};

}

#endif
