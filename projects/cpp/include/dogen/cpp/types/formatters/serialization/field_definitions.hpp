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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_SERIALIZATION_FIELD_DEFINITIONS_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_SERIALIZATION_FIELD_DEFINITIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/dynamic/schema/types/field_definition.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

/**
 * @brief Fields supported by the serialization facet and its formatters.
 */
struct field_definitions {
    /**
     * @brief Returns all the field definitions available in this
     * class.
     */
    static const std::list<dynamic::schema::field_definition>&
    all_field_definitions();

    /**
     * @brief If set to false, the facet will not be generated.
     */
    static const dynamic::schema::field_definition& enabled();

    /**
     * @brief If set to false, the type does not support the current
     * facet.
     */
    static const dynamic::schema::field_definition& supported();

    /**
     * @brief Directory in which to place files for this facet.
     */
    static const dynamic::schema::field_definition& directory();

    /**
     * @brief Post-fix to apply to file names for this facet.
     */
    static const dynamic::schema::field_definition& postfix();

    /**
     * @brief Fields supported by the class header formatter.
     */
    struct class_header_formatter {
        /**
         * @brief If set to false, the formatter will not be generated.
         */
        static const dynamic::schema::field_definition& enabled();

        /**
         * @brief Post-fix to apply to file names for this formatter.
         */
        static const dynamic::schema::field_definition& postfix();

        /**
         * @brief Inclusion path override.
         */
        static const dynamic::schema::field_definition& inclusion_path();

        /**
         * @brief Delimiter to use for the inclusion path.
         */
        static const dynamic::schema::field_definition& inclusion_delimiter();
    };

    /**
     * @brief Fields supported by the class implementation formatter.
     */
    struct class_implementation_formatter {
        /**
         * @brief If set to false, the formatter will not be generated.
         */
        static const dynamic::schema::field_definition& enabled();

        /**
         * @brief Post-fix to apply to file names for this formatter.
         */
        static const dynamic::schema::field_definition& postfix();
    };

    /**
     * @brief Fields supported by the enumeration header formatter.
     */
    struct enumeration_header_formatter {
        /**
         * @brief If set to false, the formatter will not be generated.
         */
        static const dynamic::schema::field_definition& enabled();

        /**
         * @brief Post-fix to apply to file names for this formatter.
         */
        static const dynamic::schema::field_definition& postfix();
    };

    /**
     * @brief Fields supported by the enumeration implementation formatter.
     */
    struct enumeration_implementation_formatter {
        /**
         * @brief If set to false, the formatter will not be generated.
         */
        static const dynamic::schema::field_definition& enabled();

        /**
         * @brief Post-fix to apply to file names for this formatter.
         */
        static const dynamic::schema::field_definition& postfix();
    };

};

} } } }

#endif
