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
#ifndef DOGEN_MODELING_TYPES_TRANSFORMS_MODEL_TO_TEXT_MODEL_TRANSFORM_INTERFACE_HPP
#define DOGEN_MODELING_TYPES_TRANSFORMS_MODEL_TO_TEXT_MODEL_TRANSFORM_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen.annotations/types/archetype_locations_group.hpp"
#include "dogen.annotations/types/archetype_location_repository_parts.hpp"
#include "dogen.modeling/types/meta_model/model.hpp"
#include "dogen.modeling/types/meta_model/languages.hpp"
#include "dogen.modeling/types/meta_model/text_model.hpp"
#include "dogen.modeling/types/meta_model/intra_backend_segment_properties.hpp"
#include "dogen.modeling/types/transforms/options.hpp"
#include "dogen.modeling/types/transforms/context.hpp"


namespace dogen::modeling::transforms {

/**
 * @brief Performs a model to text transformation of a meta-model,
 * into its supported language.
 */
class model_to_text_model_transform_interface {
public:
    model_to_text_model_transform_interface() = default;
    model_to_text_model_transform_interface(
        const model_to_text_model_transform_interface&) = delete;
    model_to_text_model_transform_interface(
        model_to_text_model_transform_interface&&) = default;
    virtual ~model_to_text_model_transform_interface() noexcept = 0;

public:
    /**
     * @brief Returns the identity of this transform.
     */
    virtual std::string id() const = 0;

    /**
     * @brief All archetype locations for the archetypes owned by this
     * transform, listing all available backends, facets and
     * archetypes.
     */
    virtual const std::forward_list<annotations::archetype_location>&
    archetype_locations() const = 0;

    /**
     * @brief Returns the archetype locations for each meta name.
     */
    virtual const std::unordered_map<std::string,
                                     annotations::archetype_locations_group>&
    archetype_locations_by_meta_name() const = 0;

    /**
     * @brief Returns the archetype locations for each family.
     */
    virtual const std::unordered_map<std::string,
                                     std::list<annotations::archetype_location>
                                     >&
    archetype_locations_by_family() const = 0;

    /**
     * @brief Returns this backend's part of the repository of
     * archetype locations.
     */
    virtual const annotations::archetype_location_repository_parts&
    archetype_location_repository_parts() const = 0;

    /**
     * @brief Language supported by this transform.
     */
    virtual modeling::meta_model::languages language() const = 0;

    /**
     * @brief Returns all intra-backend segment properties.
     */
    virtual std::unordered_map<std::string,
                               meta_model::intra_backend_segment_properties>
    intra_backend_segment_properties(const options& o) const = 0;

    /**
     * @brief Generates the text model representation for this
     * transform.
     */
    virtual meta_model::text_model
    transform(const context& ctx, const bool requires_backend_directory,
        const meta_model::model& m) const = 0;
};

}

#endif
