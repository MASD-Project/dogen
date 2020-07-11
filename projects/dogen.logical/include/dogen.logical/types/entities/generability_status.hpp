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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_GENERABILITY_STATUS_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_GENERABILITY_STATUS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::logical::entities {

/**
 * @brief The status of this element with regards to generability.
 */
enum class generability_status : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    non_generatable_source = 1, ///< The element was sourced from a non-target model.
    generation_not_expected = 2, ///< The element is of a type that is expected to have support for generation.
    non_generatable_state = 3, ///< The element is normally generatable, but is in a state that precludes generation.
    generation_disabled = 4, ///< The user requested generation to be disabled.
    generation_ignored = 5, ///< User requested that any changes to this element are to be ignored.
    generatable = 6 ///< The element is generatable.
};

}

#endif
