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
#ifndef DOGEN_MODELING_TYPES_HELPERS_ARTEFACT_WRITER_INTERFACE_HPP
#define DOGEN_MODELING_TYPES_HELPERS_ARTEFACT_WRITER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.modeling/types/meta_model/artefact.hpp"

namespace dogen {
namespace modeling {
namespace helpers {

/**
 * @brief Class with the ability to write artefacts into some storage
 * medium.
 */
class artefact_writer_interface {
public:
    virtual ~artefact_writer_interface() noexcept = 0;

public:
    /**
     * @brief Write the artefacts.
     */
    virtual void
    write(const std::list<meta_model::artefact>& artefacts) const = 0;
};

} } }

#endif
