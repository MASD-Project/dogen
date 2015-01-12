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
#ifndef DOGEN_DIA_TO_SML_TYPES_FIELD_DEFINITIONS_HPP
#define DOGEN_DIA_TO_SML_TYPES_FIELD_DEFINITIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/types/field_definition.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Fields supported by the Dia to SML translator.
 */
class field_definitions {
public:
    /**
     * @brief Comment provided by user when dia does not allow for it.
     *
     * For meta-types where comments are available in Dia (e.g. class,
     * properties, etc), this parameter is ignored. For types where
     * they are not (e.g. model, package), it will be used to populate
     * the meta-type's documentation.
     */
    static const dynamic::field_definition& comment();

    /**
     * @brief Attribute that provides this entity its identity.
     */
    static const dynamic::field_definition&  identity_attribute();
};

} }

#endif
