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
#ifndef DOGEN_FORMATTERS_TYPES_FIELD_DEFINITIONS_HPP
#define DOGEN_FORMATTERS_TYPES_FIELD_DEFINITIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <forward_list>
#include "dogen/dynamic/schema/types/field_definition.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Fields supported by the generic formatters model.
 */
struct field_definitions {
    /**
     * @brief Returns all the field definitions available in this
     * class.
     */
    static const std::forward_list<dynamic::schema::field_definition>&
    all_field_definitions();

    /**
     * @brief Key used to denote copyright notices.
     *
     * It is expected to be repeated in a model; order is kept as
     * provided by user.
     */
    static const dynamic::schema::field_definition& copyright_notices();

    /**
     * @brief Name of the legal licence to use.
     *
     * Must match licences available in library.
     */
    static const dynamic::schema::field_definition& licence_name();

    /**
     * @brief Name of the modeline group to use.
     *
     * Must match licences available in library.
     */
    static const dynamic::schema::field_definition& modeline_group_name();

    /**
     * @brief Whether to generate the preamble or not.
     *
     * The preamble is made up of a modeline, copyright
     * information and licensing details.
     */
    static const dynamic::schema::field_definition& generate_preamble();

    /**
     * @brief Tags related to the code generation marker.
     */
    struct code_generation_marker {
        /**
         * @brief Whether to add the generation date and time to the
         * marker or not.
         */
        static const dynamic::schema::field_definition& add_date_time();

        /**
         * @brief Whether to add a warning not to modify code-generated
         * files or not.
         */
        static const dynamic::schema::field_definition& add_warning();

        /**
         * @brief Message to place on all code-generated files.
         */
        static const dynamic::schema::field_definition& message();
    };
};

} }

#endif
