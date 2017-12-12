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
#ifndef DOGEN_ANNOTATIONS_TYPES_SCOPE_TYPES_HPP
#define DOGEN_ANNOTATIONS_TYPES_SCOPE_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace annotations {

/**
 * @brief Where can a field appear.
 */
enum class scope_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    any = 1, ///< Field can appear anywhere.
    not_applicable = 2, ///< The notion of scopes does not apply to field.
    root_module = 3, ///< Field can only appear in the root module.
    any_module = 4, ///< Field can appear in any module.
    entity = 5, ///< Field can only appear on an entity.
    property = 6, ///< Field can only appear on a property of an entity.
    operation = 7 ///< Field can only appear on an operation in an entity.
};

} }

#endif
