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
#ifndef DOGEN_CPP_TYPES_CONTENT_TYPES_HPP
#define DOGEN_CPP_TYPES_CONTENT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace cpp {

/**
 * @brief Supported types of content.
 */
enum class content_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    exception = 1,
    enumeration = 2,
    primitive = 3,
    value_object = 4,
    user_defined_service = 5,
    visitor = 6,
    key_extractor = 7,
    factory = 8,
    repository = 9,
    keyed_entity = 10,
    entity = 11,
    registrar = 12,
    namespace_doc = 13,
    includer = 14,
    versioned_key = 15,
    unversioned_key = 16
};

} }

#endif
