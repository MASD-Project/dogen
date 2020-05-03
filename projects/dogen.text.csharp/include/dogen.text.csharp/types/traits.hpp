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
#ifndef DOGEN_TEXT_CSHARP_TYPES_TRAITS_HPP
#define DOGEN_TEXT_CSHARP_TYPES_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen::text::csharp {

/**
 * @brief Constants for all the top-level meta-data keys for the C#
 * backend.
 */
struct traits {
    /**
     * @brief If set to false, no generation will occur.
     */
    static std::string enabled();

    /**
     * @brief Name of the masd kernel.
     */
    static std::string kernel();

    /**
     * @brief Name of this backend.
     */
    static std::string backend_qn();
    static std::string backend_sn();

    /**
     * @brief Name of the directory housing the backend.
     */
    static std::string backend_directory_name();

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
     * @brief Parts available in this backend.
     */
    /**@{*/
    static std::string empty_part();
    /**@}*/

    struct csharp {
        struct helper {
            /**
             * @brief Family of the helper methods.
             */
            static std::string family();
        };

        struct aspect {
            /**
             * @brief If true, the type requires a static method for reference
             * equals.
             */
            static std::string requires_static_reference_equals();

        };

        struct assistant {
            /**
             * @brief If true, the element needs help from an assistant.
             */
            static std::string requires_assistance();

            /**
             * @brief The postfix to use when calling the assistant method, if
             * any.
             */
            static std::string method_postfix();
        };
    };
};

}

#endif
