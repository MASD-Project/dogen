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
#ifndef DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_TEST_DATA_TRAITS_HPP
#define DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_TEST_DATA_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen::text::csharp::transforms::test_data {

struct traits final {
    /**
     * @brief Name of this facet.
     */
    static std::string facet_qn();
    static std::string facet_sn();

    /**
     * @brief Name of the class header archetype.
     */
    static std::string class_archetype_qn();
    static std::string class_archetype_sn();

    /**
     * @brief Name of the enum header archetype.
     */
    static std::string enum_archetype_qn();
    static std::string enum_archetype_sn();

    /**
     * @brief Name of the primitive header archetype.
     */
    static std::string primitive_archetype_qn();
    static std::string primitive_archetype_sn();

    /**
     * @brief Name of the assistant archetype.
     */
    static std::string assistant_archetype_qn();
    static std::string assistant_archetype_sn();
};

}

#endif
