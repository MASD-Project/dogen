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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_MODEL_TYPE_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_MODEL_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::identification::entities {

/**
 * @brief Types of models with regards to the current generation taking place.
 */
enum class model_type : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    target = 1, ///< The element is part of the target model.
    pdm_reference = 2, ///< The element was part of a reference model which is a PDM.
    non_pdm_reference = 3, ///< The element was part of a reference model which is regular dogen model.
    not_yet_determined = 4 ///< The origin of the element is not yet known.
};

}

#endif
