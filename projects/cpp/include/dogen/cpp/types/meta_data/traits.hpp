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
#ifndef DOGEN_CPP_TYPES_META_DATA_TRAITS_HPP
#define DOGEN_CPP_TYPES_META_DATA_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace cpp {
namespace meta_data {

/**
 * @brief Constants for all the top-level meta-data keys for the C++
 * backend.
 */
struct traits {
    /**
     * @brief Valid values for Boolean types.
     */
    /*@{*/
    static const std::string bool_true;
    static const std::string bool_false;
    /*@}*/

    /**
     * @brief If set to false, the C++ backend will not
     * be generated.
     */
    static const std::string enabled;

    /**
     * @brief If true, the project will be split.
     *
     * @deprecated used only for backwards compatibility.
     */
    static const std::string split_project;

    /**
     * @brief Name of the directory in which to place the
     * implementation files.
     */
    static const std::string source_directory;

    /**
     * @brief Name of the directory in which to place the header
     * files.
     */
    static const std::string include_directory;

    /**
     * @brief Extension to use for header files, including the
     * leading dot.
     *
     * Example: @e .hpp, @e .hxx
     */
    static const std::string header_file_extension;

    /**
     * @brief Extension to use for implementation files, including
     * the leading dot.
     *
     * Example: @e .cpp, @e .cxx.
     */
    static const std::string implementation_file_extension;

    /**
     * @brief If true, files for each facet will be placed in a
     * folder for the facet.
     */
    static const std::string enable_facet_folders;

    /**
     * @brief If true, each file in each facet will have a name
     * unique across all facets.
     *
     * This is achieved by using the facet's postfix.
     */
    static const std::string enable_unique_file_names;

    /**
     * @brief Tags related to facets.
     */
    struct facet {
        /**
         * @brief If set to false, the facet will not be generated.
         */
        static const std::string enabled;

        /**
         * @brief Directory in which to place files for this facet.
         */
        static const std::string directory;

        /**
         * @brief Post-fix to apply to file names for this facet.
         */
        static const std::string postfix;
    };
};

} } }

#endif
