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
#ifndef DOGEN_DIA_TO_SML_TYPES_TRANSFORMER_INTERFACE_HPP
#define DOGEN_DIA_TO_SML_TYPES_TRANSFORMER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dia_to_sml/types/processed_object_fwd.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Transforms dia objects
 */
class transformer_interface {
public:
    transformer_interface() = default;
    transformer_interface(const transformer_interface&) = delete;
    transformer_interface(transformer_interface&&) = default;
    virtual ~transformer_interface() noexcept = 0;

public:
    /**
     * @brief Transform a dia object.
     */
    virtual void transform(const processed_object& o) = 0;
};

} }

#endif
