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
#ifndef DOGEN_CPP_TYPES_TRAITS_HPP
#define DOGEN_CPP_TYPES_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace cpp {

/**
 * @brief Constants for all the top-level meta-data keys for the C++
 * backend.
 */
struct traits {
    /**
     * @brief If set to false, no generation will occur.
     */
    static std::string enabled();

    /**
     * @brief If set to true, the facet is not supported.
     */
    static std::string supported();

    /**
     * @brief Directory in which to place files for this facet.
     */
    static std::string directory();

    /**
     * @brief Post-fix to apply to file names.
     */
    static std::string postfix();

    /**
     * @brief All facets that have been integrated with the present
     * facet.
     */
    static std::string integrated_facet();

    /**
     * @brief Full path to the file for this formatter.
     */
    static std::string file_path();

    /**
     * @brief Header guards to use for this file, if any.
     */
    static std::string header_guard();

    /**
     * @brief Delimited include path to use for type.
     */
    static std::string inclusion_directive();

    /**
     * @brief Files this file must include
     */
    static std::string inclusion_dependency();

    /**
     * @brief Is inclusion required for this type and formatter.
     */
    static std::string inclusion_required();

    /**
     * @brief Disables the generation of the complete constructor.
     */
    static std::string disable_complete_constructor();

    /**
     * @brief Disables XML support in boost serialisation.
     */
    static std::string disable_xml_serialization();

    /**
     * @brief Disables EOS support in boost serialisation.
     */
    static std::string disable_eos_serialization();

    /**
     * @brief Disables versioning support.
     */
    static std::string disable_versioning();

    struct cpp {
        /**
         * @brief Is inclusion required for all formatters.
         */
        static std::string inclusion_required();

        /**
         * @brief File extension to use for header files.
         */
        static std::string header_file_extension();

        /**
         * @brief File extension to use for implementation files.
         */
        static std::string implementation_file_extension();

        /**
         * @brief Name of the directory containing the include files.
         */
        static std::string include_directory_name();

        /**
         * @brief Name of the directory containing the source files.
         */
        static std::string source_directory_name();
    };
};

} }

#endif
