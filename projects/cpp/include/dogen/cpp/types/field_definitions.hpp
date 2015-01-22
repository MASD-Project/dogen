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
#ifndef DOGEN_CPP_TYPES_FIELD_DEFINITIONS_HPP
#define DOGEN_CPP_TYPES_FIELD_DEFINITIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/types/field_definition.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Fields supported by the cpp model.
 */
struct field_definitions {
    /**
     * @brief If set to false, the C++ backend will not
     * be generated.
     */
    static const dynamic::field_definition& enabled();

    /**
     * @brief If true, the project will be split.
     *
     * @deprecated used only for backwards compatibility.
     */
    static const dynamic::field_definition& split_project();

    /**
     * @brief Name of the directory in which to place the
     * implementation files.
     */
    static const dynamic::field_definition& source_directory();

    /**
     * @brief Name of the directory in which to place the header
     * files.
     */
    static const dynamic::field_definition& include_directory();

    /**
     * @brief Extension to use for header files, including the
     * leading dot.
     *
     * Example: @e .hpp, @e .hxx
     */
    static const dynamic::field_definition& header_file_extension();

    /**
     * @brief Extension to use for implementation files, including
     * the leading dot.
     *
     * Example: @e .cpp, @e .cxx.
     */
    static const dynamic::field_definition& implementation_file_extension();

    /**
     * @brief If true, files for each facet will be placed in a
     * folder for the facet.
     */
    static const dynamic::field_definition& enable_facet_folders();

    /**
     * @brief If true, each file in each facet will have a name
     * unique across all facets.
     *
     * This is achieved by using the facet's postfix.
     */
    static const dynamic::field_definition& enable_unique_file_names();
};

} }

#endif
