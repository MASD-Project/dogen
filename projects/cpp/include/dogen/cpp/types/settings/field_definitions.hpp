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
#ifndef DOGEN_CPP_TYPES_SETTINGS_FIELD_DEFINITIONS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_FIELD_DEFINITIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/dynamic/schema/types/field_definition.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Fields supported by the cpp model.
 */
struct field_definitions {
    /**
     * @brief Returns all the field definitions available in this
     * class.
     */
    static const std::list<dynamic::schema::field_definition>&
    all_field_definitions();

    /**
     * @brief If set to false, the C++ backend will not
     * be generated.
     */
    static const dynamic::schema::field_definition& enabled();

    /**
     * @brief If true, the project will be split.
     *
     * @deprecated used only for backwards compatibility.
     */
    static const dynamic::schema::field_definition& split_project();

    /**
     * @brief Name of the directory in which to place the
     * implementation files.
     */
    static const dynamic::schema::field_definition& source_directory_name();

    /**
     * @brief Name of the directory in which to place the header
     * files.
     */
    static const dynamic::schema::field_definition& include_directory_name();

    /**
     * @brief Extension to use for header files, including the
     * leading dot.
     *
     * Example: @e .hpp, @e .hxx
     */
    static const dynamic::schema::field_definition& header_file_extension();

    /**
     * @brief Extension to use for implementation files, including
     * the leading dot.
     *
     * Example: @e .cpp, @e .cxx.
     */
    static const dynamic::schema::field_definition& implementation_file_extension();

    /**
     * @brief If true, files for each facet will be placed in a
     * folder for the facet.
     */
    static const dynamic::schema::field_definition& enable_facet_folders();

    /**
     * @brief If true, each file in each facet will have a name
     * unique across all facets.
     *
     * This is achieved by using the facet's postfix.
     */
    static const dynamic::schema::field_definition& enable_unique_file_names();

    /**
     * @brief Dynamic properties that belong to the type itself.
     */
    struct type {
        /**
         * @brief To which family does the type belong to.
         */
        static const dynamic::schema::field_definition& family();

        /**
         * @brief If true, a manual default constructor must be
         * generated for this type.
         */
        static const dynamic::schema::field_definition&
        requires_manual_default_constructor();

        /**
         * @brief If true, a manual move constructor must be generated
         * for this type.
         */
        static const dynamic::schema::field_definition&
        requires_manual_move_constructor();

        /**
         * @brief If false, type does not require any include
         * statements.
         */
        static const dynamic::schema::field_definition& inclusion_required();
    };
};

} } }

#endif
