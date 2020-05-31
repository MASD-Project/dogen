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
#ifndef DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_IO_IO_HPP
#define DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_IO_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.physical/types/entities/facet.hpp"
#include "dogen.text.csharp/types/transforms/registrar.hpp"

namespace dogen::text::csharp::transforms::io {

/**
 * @brief M2T transforms for the io facet of
 * the C# Technical Space.
 */
class io_facet_chain final {
public:
    static const physical::entities::facet& static_facet();
    const physical::entities::facet& facet() const;

public:
    static void initialise(registrar& r);
};
}

#endif
