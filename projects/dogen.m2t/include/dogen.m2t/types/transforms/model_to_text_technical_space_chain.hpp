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
#ifndef DOGEN_M2T_TYPES_TRANSFORMS_PHYSICAL_MODEL_TRANSFORM_INTERFACE_HPP
#define DOGEN_M2T_TYPES_TRANSFORMS_PHYSICAL_MODEL_TRANSFORM_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen.physical/types/entities/meta_name_group.hpp"
#include "dogen.physical/types/entities/name_repository_parts.hpp"
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.m2t/types/transforms/context.hpp"
#include "dogen.m2t/types/entities/model.hpp"
#include "dogen.physical/types/entities/model.hpp"

namespace dogen::m2t::transforms {

/**
 * @brief Performs a model to text transformation of a meta-model,
 * into its supported technical space.
 */
class model_to_text_technical_space_chain {
public:
    model_to_text_technical_space_chain() = default;
    model_to_text_technical_space_chain(
        const model_to_text_technical_space_chain&) = delete;
    model_to_text_technical_space_chain(
        model_to_text_technical_space_chain&&) = default;
    virtual ~model_to_text_technical_space_chain() noexcept = default;

public:
    /**
     * @brief Returns the identity of this transform.
     */
    virtual std::string id() const = 0;

    /**
     * @brief All physical names for the archetypes owned by this
     * transform, listing all available backends, facets and
     * archetypes.
     */
    virtual const std::forward_list<physical::entities::meta_name>&
    physical_names() const = 0;

    /**
     * @brief Returns a human readable description of this transform.
     */
    virtual std::string description() const = 0;

    /**
     * @brief Returns the physical names for each meta name.
     */
    virtual const std::unordered_map<std::string,
                                     physical::entities::meta_name_group>&
    physical_names_by_meta_name() const = 0;

    /**
     * @brief Returns the archetype locations for each family.
     */
    virtual const std::unordered_map<std::string,
                                     std::list<physical::entities::meta_name>
                                     >&
    physical_names_by_family() const = 0;

    /**
     * @brief Returns this backend's part of the repository of
     * archetype locations.
     */
    virtual const physical::entities::name_repository_parts&
    physical_name_repository_parts() const = 0;

    /**
     * @brief Technical space supported by this transform.
     */
    virtual logical::entities::technical_space technical_space() const = 0;

    /**
     * @brief Generates the text model representation for this
     * transform.
     */
    virtual physical::entities::model
    apply(const m2t::transforms::context& ctx,
        const bool requires_backend_directory,
        const m2t::entities::model& m) const = 0;
};

}

#endif
