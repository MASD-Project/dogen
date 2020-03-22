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
#ifndef DOGEN_M2T_CPP_TYPES_TRAITS_HPP
#define DOGEN_M2T_CPP_TYPES_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen::m2t::cpp {

/**
 * @brief Constants for all the top-level meta-data keys for the C++
 * backend.
 */
struct traits {
    /**
     * @brief Name of this backend.
     */
    static std::string backend();

    /**
     * @brief If set to false, no generation will occur.
     */
    static std::string enabled();

    /**
     * @brief If set to true, the facet is not supported.
     */
    static std::string supported();

    /**
     * @brief If set to true, the file will be overwritten.
     */
    static std::string overwrite();

    /**
     * @brief Directory in which to place files for this facet.
     */
    static std::string directory();

    /**
     * @brief Post-fix to apply to file names.
     */
    static std::string postfix();

    /**
     * @brief Full path to the file for this formatter.
     */
    static std::string file_path();

    /**
     * @brief Header guards to use for this file, if any.
     */
    static std::string header_guard();

    /**
     * @brief Primary inclusion directive to use for type, if any.
     */
    static std::string primary_inclusion_directive();

    /**
     * @brief Any additional inclusion directives to use for type, if
     * any.
     */
    static std::string secondary_inclusion_directive();

    /**
     * @brief Files this file must include
     */
    static std::string inclusion_dependency();

    /**
     * @brief Is inclusion required for this type and formatter.
     */
    static std::string inclusion_required();

    /**
     * @brief Available families.
     */
    /**@{*/
    static std::string header_family();
    static std::string implementation_family();
    static std::string cmake_family();
    static std::string visual_studio_solution_family();
    static std::string visual_studio_project_family();
    static std::string msbuild_family();
    static std::string odb_family();
    /**@}*/

    struct cpp {
        /**
         * @brief Style of formatting.
         */
        static std::string formatting_style();

        /**
         * @brief External inputs for formatting.
         */
        static std::string formatting_input();

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
         * @brief File extension to use templates.
         */
        static std::string templates_file_extension();

        /**
         * @brief Name of the directory containing the include files.
         */
        static std::string include_directory_name();

        /**
         * @brief Name of the directory containing the source files.
         */
        static std::string source_directory_name();

        /**
         * @brief Name of the directory containing the test files.
         */
        static std::string tests_directory_name();

        /**
         * @brief Name of the directory containing the template files.
         */
        static std::string templates_directory_name();

        /**
         * @brief Name of the directory housing the backend.
         */
        static std::string backend_directory_name();

        /**
         * @brief If true, facet directories will be ignored.
         */
        static std::string disable_facet_directories();

        /**
         * @brief Which C++ standard to use.
         */
        static std::string standard();

        struct helper {
            /**
             * @brief Family of the helper methods.
             */
            static std::string family();
        };

        struct streaming {
            /**
             * @brief Method to convert object to a string, if any.
             */
            static std::string string_conversion_method();

            /**
             * @brief If true, the type must be quoted.
             */
            static std::string requires_quoting();

            /**
             * @brief If true, remove unprintable characters.
             */
            static std::string remove_unprintable_characters();

            /**
             * @brief If true, the type must be dereferenced.
             */
            static std::string requires_dereferencing();
        };

        struct aspect {
            /**
             * @brief Disables the generation of the complete constructor.
             */
            static std::string disable_complete_constructor();

            /**
             * @brief Disables XML support in boost serialisation.
             */
            static std::string disable_xml_serialization();

            /**
             * @brief If true, the type needs to be manually constructed.
             */
            static std::string requires_manual_default_constructor();

            /**
             * @brief If true, the type needs to be manually moved.
             */
            static std::string requires_manual_move_constructor();

            /**
             * @brief If true, the stream manipulators need to be setup for
             * this type.
             */
            static std::string requires_stream_manipulators();
        };
    };
};

}

#endif
