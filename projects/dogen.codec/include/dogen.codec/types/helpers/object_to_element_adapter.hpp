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
#ifndef DOGEN_CODEC_TYPES_HELPERS_OBJECT_TO_ELEMENT_ADAPTER_HPP
#define DOGEN_CODEC_TYPES_HELPERS_OBJECT_TO_ELEMENT_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.codec/types/entities/object.hpp"
#include "dogen.codec/types/entities/comment.hpp"
#include "dogen.codec/types/entities/attribute.hpp"

namespace dogen::codec::helpers {

/**
 * @brief Adapts objects into elements.
 */
class object_to_element_adapter final {
private:
    /**
     * @brief Ensure the name is valid.
     */
    static void validate_name(const std::string& n);

    /**
     * @brief Constructs a qualified name, taking into account the
     * contents of the contained by parameter.
     */
    static std::string qualified_name(const std::string& contained_by,
        const std::string& simple_name);

    /**
     * @brief Processes the stereotypes field.
     */
    static void process_stereotypes(const entities::object& po,
        codec::entities::element& e);

private:
    /**
     * @brief Adapts attributes.
     */
    static codec::entities::attribute
    adapt(const entities::attribute& a, const std::string& qualified_owner);

public:
    /**
     * @brief Adapts an object into an element.
     */
    static codec::entities::element
    adapt(const entities::object& po, const std::string& contained_by,
        const std::list<std::string>& parents);
};

}

#endif
