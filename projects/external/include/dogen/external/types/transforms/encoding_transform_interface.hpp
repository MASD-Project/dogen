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
#ifndef DOGEN_EXTERNAL_TYPES_TRANSFORMS_ENCODING_TRANSFORM_INTERFACE_HPP
#define DOGEN_EXTERNAL_TYPES_TRANSFORMS_ENCODING_TRANSFORM_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/external/types/meta_model/model.hpp"
#include "dogen/external/types/transforms/context_fwd.hpp"

namespace dogen {
namespace external {
namespace transforms {

/**
 * @brief Transform that converts models in third-party formats into
 * our external model representation.
 */
class encoding_transform_interface {
public:
    encoding_transform_interface() = default;
    encoding_transform_interface(const encoding_transform_interface&) = delete;
    virtual ~encoding_transform_interface() noexcept = 0;

public:
    /**
     * @brief Returns the extension of the files that this transform
     * can process.
     */
    virtual std::string extension() const = 0;

    /**
     * @brief Transforms the model at the supplied path into our
     * internal representation of an external model.
     *
     * @param p Path to an external model.
     *
     * @pre Model must conform to the format supported by the
     * transform.
     *
     * @note Method is non-const by design at the moment as some
     * encoding transforms have mutable state.
     *
     * @note This function is receiving a path to the model, rather
     * than the file contents because at the moment the encoding
     * transform implementations cannot cope with string
     * processing. In the future this will change to a string.
     */
    virtual meta_model::model transform(const context& ctx,
        const boost::filesystem::path& p) = 0;
};

} } }

#endif
