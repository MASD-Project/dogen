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
#ifndef DOGEN_STITCH_TYPES_TRAITS_FWD_HPP
#define DOGEN_STITCH_TYPES_TRAITS_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace stitch {

struct traits {
    /**
     * @brief Name of the model that owns the fields.
     */
    static std::string model_name();

    /**
     * @brief Name of the variable used for streaming.
     *
     * For example: @code stream_
     */
    static std::string stream_variable_name();

    /**
     * @brief Relative path to the directory in which to place the
     * output, if any.
     */
    static std::string relative_output_directory();

    /**
     * @brief Inclusion dependencies required by the template.
     */
    static std::string inclusion_dependency();

    /**
     * @brief Namespaces that contain the content in the template.
     */
    static std::string containing_namespaces();

    /**
     * @brief Name of the associated wale template, if any.
     */
    static std::string wale_template();

};

} }

#endif
