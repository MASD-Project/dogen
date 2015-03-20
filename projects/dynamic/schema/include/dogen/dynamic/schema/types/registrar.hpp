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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_REGISTRAR_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/dynamic/schema/types/field_definition.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

class registrar {
public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Registers a field definition.
     */
    void register_field_definition(const field_definition& fd);

    /**
     * @brief Registers a list of field definitions.
     */
    void register_field_definitions(
        const std::list<field_definition>& fds);

public:
    /**
     * @brief Returns all registered field definitions.
     */
    const std::list<field_definition>& field_definitions() const;

private:
    std::list<field_definition> field_definitions_;
};

} } }

#endif
