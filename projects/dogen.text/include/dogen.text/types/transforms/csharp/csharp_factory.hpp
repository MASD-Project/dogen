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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_CSHARP_CSHARP_FACTORY_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_CSHARP_CSHARP_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.physical/types/entities/backend.hpp"

namespace dogen::text::transforms::csharp {

/**
 * @brief Creates a physical representation for the backend
 * csharp.
 *
 * Backend documentation: M2T transforms for the C# technical space.

Takes types in the logical model and creates text
representations of the these types according to the grammar
of the C# technical space.

 */
class csharp_factory final {
public:
    static physical::entities::backend make();
};

}

#endif
