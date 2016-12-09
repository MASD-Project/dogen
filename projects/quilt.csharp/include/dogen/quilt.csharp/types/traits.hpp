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
#ifndef DOGEN_QUILT_CSHARP_TYPES_TRAITS_HPP
#define DOGEN_QUILT_CSHARP_TYPES_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace quilt {
namespace csharp {

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
     * @brief Name of this family.
     */
    static std::string family();

    /**
     * @brief Name of this kernel.
     */
    static std::string kernel();

    /**
     * @brief Name of the directory housing the kernel.
     */
    static std::string kernel_directory_name();

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
};

} } }

#endif
