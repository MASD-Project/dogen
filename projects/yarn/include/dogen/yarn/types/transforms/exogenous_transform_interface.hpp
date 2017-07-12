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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_EXOGENOUS_TRANSFORM_INTERFACE_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_EXOGENOUS_TRANSFORM_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"
#include "dogen/yarn/types/transforms/exogenous_transform_types.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

/**
 * @brief Provides a possibly bi-directional transform of intermediate
 * models from and to an external source.
 */
class exogenous_transform_interface {
public:
    exogenous_transform_interface() = default;
    exogenous_transform_interface(
        const exogenous_transform_interface&) = delete;
    virtual ~exogenous_transform_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for the frontend, used for logging
     * purposes.
     */
    virtual std::string id() const = 0;

    /**
     * @brief Returns the exogenous transformations supported by this
     * transformer.
     */
    virtual exogenous_transform_types supported_transforms() const = 0;

    /**
     * @brief Returns true if the exogenous transformer supports
     * this kind of models.
     *
     * @param model_identifier Identifier for the model one wishes to
     * transform - usually its file name.
     */
    virtual bool can_transform(const std::string& model_identifier) const = 0;

    /**
     * @brief Transforms the exogenous model supplied into an
     * intermediate model.
     *
     * @param s Path to an exogenous model.
     *
     * @pre Model must conform to the format supported by the
     * transformer, as validated by @e can_transform.
     *
     * @note Method is non-const by design at the moment as some
     * exogenous transformers have state.
     *
     * @note This function is receiving a path to the model, rather
     * than the file contents because at the moment the exogenous
     * transformers cannot cope with string processing. In the future
     * this will change to a string.
     */
    virtual meta_model::intermediate_model
    transform(const boost::filesystem::path& p) = 0;

    /**
     * @brief Transforms the intermediate model into a representation
     * of the native format supported by the exogneous transformer.
     *
     * @param im Intermediate model to transform.
     *
     * @note Method is non-const by design at the moment as some
     * exogenous transformers have state.
     *
     * @note This function is receiving a path to the model, rather
     * than return the file contents because at the moment the
     * exogenous transformers cannot cope with string processing. In
     * the future this will change to returning a string.
     */
    virtual void transform(const meta_model::intermediate_model& im,
        const boost::filesystem::path& p) = 0;
};

} } }

#endif
