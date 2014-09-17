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
#ifndef DOGEN_FORMATTERS_TYPES_TRAITS_HPP
#define DOGEN_FORMATTERS_TYPES_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace formatters {
namespace meta_data {

struct traits {
    /**
     * @brief Valid values for Boolean types.
     */
    /*@{*/
    static const std::string bool_true;
    static const std::string bool_false;
    /*@}*/

    /**
     * @brief Key used to denote copyright holders.
     *
     * It is expected to be repeated in a model; order is kept as
     * provided by user.
     */
    static const std::string copyright_holder;

    /**
     * @brief Name of the legal licence to use.
     *
     * Must match licences available in library.
     */
    static const std::string licence_name;

    /**
     * @brief Name of the modeline group to use.
     *
     * Must match licences available in library.
     */
    static const std::string modeline_group_name;

    /**
     * @brief If set to true, the preamble will be generated.
     *
     * The preamble is made up of a modeline, copyright
     * information and licensing details.
     */
    static const std::string generate_preamble;

    /**
     * @brief Tags related to the code generation marker.
     */
    struct code_generation_marker {
        /**
         * @brief If true, add the generation date and time to the marker.
         */
        static const std::string add_date_time;

        /**
         * @brief If true, adds a warning not to modify
         * code-generated files.
         */
        static const std::string add_warning;

        /**
         * @brief Message to place on all code-generated files.
         */
        static const std::string message;
    };
};

} } }

#endif
