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
#ifndef DOGEN_M2T_TYPES_TRANSFORMS_PHYSICAL_MODEL_TRANSFORM_REGISTRAR_HPP
#define DOGEN_M2T_TYPES_TRANSFORMS_PHYSICAL_MODEL_TRANSFORM_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_map>
#include "dogen.physical/types/entities/location.hpp"
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.logical/hash/entities/technical_space_hash.hpp"
#include "dogen.m2t/types/transforms/physical_model_transform_interface.hpp"

namespace dogen::m2t::transforms {

/**
 * @brief Keeps track of all the available model to text model
 * transforms. These are implemented by technical space-specific
 * backends.
 */
class physical_model_transform_registrar {
public:
    /**
     * @brief Registers a model to text transform.
     */
    void register_transform(
        std::shared_ptr<physical_model_transform_interface> t);

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Returns the transform for the supplied technical space,
     * if any exists. Otherwise returns a null shared pointer.
     */
    std::shared_ptr<physical_model_transform_interface>
    transform_for_technical_space(
        const logical::entities::technical_space ts) const;

    /**
     * @brief Returns all available transforms, by technical space.
     */
    const std::unordered_map<
        logical::entities::technical_space,
        std::shared_ptr<physical_model_transform_interface>>&
    transforms_by_technical_space() const;

private:
    std::unordered_map<logical::entities::technical_space,
    std::shared_ptr<physical_model_transform_interface>>
    transforms_by_technical_space_;
};

}

#endif
