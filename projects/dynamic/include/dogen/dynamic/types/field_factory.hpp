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
#ifndef DOGEN_DYNAMIC_TYPES_FIELD_FACTORY_HPP
#define DOGEN_DYNAMIC_TYPES_FIELD_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <utility>
#include <forward_list>
#include "dogen/dynamic/types/field.hpp"
#include "dogen/dynamic/types/field_definition.hpp"

namespace dogen {
namespace dynamic {

/**
 * @brief Builds a field from its constituent parts.
 */
class field_factory {
public:
    /**
     * @brief Builds a field given a definition, the original key and
     * zero or more values.
     *
     * @pre If values has more than one element, the field's value
     * type must be a collection.
     *
     * @pre Values must be valid according to the type in the field
     * definition.
     */
    field build(const field_definition& fd,
        const std::forward_list<std::string>& values) const;
};

} }

#endif
