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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_DYNAMIC_TRANSFORM_REGISTRAR_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_DYNAMIC_TRANSFORM_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include "masd.dogen.coding/types/transforms/dynamic_transform_interface.hpp"

namespace masd::dogen::coding::transforms {

class dynamic_transform_registrar final {
public:
    /*
     * @brief Registers a given external transform.
     *
     * @pre Pointer must not be null.
     */
    void register_dynamic_transform(
        std::shared_ptr<const dynamic_transform_interface> t);

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Returns all of the registered external transforms.
     */
    std::list<std::shared_ptr<const dynamic_transform_interface>>
    dynamic_transforms() const;

private:
    std::list<std::shared_ptr<const dynamic_transform_interface>> transforms_;
};

}

#endif
