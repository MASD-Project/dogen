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
#ifndef MASD_DOGEN_FORMATTNG_TYPES_TRAITS_HPP
#define MASD_DOGEN_FORMATTNG_TYPES_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace masd::dogen::extraction {

struct traits {
    struct extraction {
        static std::string force_write();
        static std::string delete_extra_files();
        static std::string ignore_files_matching_regex();
        static std::string delete_empty_directories();
    };

    struct decoration {
        /**
         * @brief Whether to generate the decoration or not.
         */
        static std::string generate_decoration();

        /**
         * @brief Key used to denote copyright notices.
         *
         * It is expected to be repeated in a model; order is kept as
         * provided by user.
         */
        static std::string copyright_notices();

        /**
         * @brief Name of the legal licence to use.
         *
         * Must match licences available in library.
         */
        static std::string licence_name();

        /**
         * @brief Name of the modeline group to use.
         *
         * Must match licences available in library.
         */
        static std::string modeline_group_name();

        /**
         * @brief Tags related to the code generation marker.
         */
        struct code_generation_marker {
            /**
             * @brief Whether to add the generation date and time to the
             * marker or not.
             */
            static std::string add_date_time();

            /**
             * @brief Whether to add a warning not to modify code-generated
             * files or not.
             */
            static std::string add_warning();

            /**
             * @brief Message to place on all code-generated files.
             */
            static std::string message();
        };
    };
};

}

#endif
