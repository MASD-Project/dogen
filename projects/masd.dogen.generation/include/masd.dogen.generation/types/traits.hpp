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
#ifndef MASD_DOGEN_GENERATION_TYPES_TRAITS_HPP
#define MASD_DOGEN_GENERATION_TYPES_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace masd::dogen::generation {

struct traits {
    static std::string enabled();
    static std::string directory();
    static std::string postfix();
    static std::string supported();
    static std::string overwrite();
    static std::string enable_backend_directories();
    static std::string force_backend_directory();

    struct decoration {
        static std::string enabled();
        static std::string copyright_notice();
        static std::string licence_name();
        static std::string  modeline_group_name();
        static std::string marker_name();
    };
};

}

#endif
