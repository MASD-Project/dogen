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
#ifndef DOGEN_SML_TYPES_META_TYPES_HPP
#define DOGEN_SML_TYPES_META_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml {

/**
 * @brief Type of the model element.
 */
enum class meta_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    model = 1, ///< Model element is a model.
    enumeration = 2, ///< Model element is an enumeration
    primitive = 3, ///< Model element is a primitive
    exception = 4, ///< Model element is an exception
    module = 5, ///< Model element is a module
    service = 6, ///< Model element is a service
    entity = 7, ///< Model element is an entity
    keyed_entity = 8, ///< Model element is a keyed entity
    value_object = 9, ///< Model element is a value object
    factory = 10, ///< Model element is a factory
    repository = 11, ///< Model element is a repository
    concept = 12 ///< Model element is a concept
};

} }

#endif
