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
#ifndef DOGEN_SML_TYPES_POD_TYPES_HPP
#define DOGEN_SML_TYPES_POD_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml {

/**
 * @brief Types of pods.
 *
 * We need to classify pods with regards to distinguishing properties
 * which make code generation different.
 */
enum class pod_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    sequence_container = 1, ///< Pod is a sequence container
    associative_container = 2, ///< Pod is an associative container
    smart_pointer = 3, ///< Pod is a smart pointer
    entity = 4, ///< Pod is a domain entity
    value = 5, ///< Pod is a domain value
    service = 6 ///< Pod is a domain service
};

} }

#endif
