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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_DECODING_TRANSFORM_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_DECODING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/transforms/context_fwd.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Transform that converts extennal models into our codec
 * model representation.
 */
class decoding_transform {
public:
    decoding_transform() = default;
    decoding_transform(const decoding_transform&) = delete;
    virtual ~decoding_transform() noexcept = default;

public:
    /**
     * @brief Returns the identity of this transform.
     */
    virtual std::string id() const = 0;

    /**
     * @brief Returns a human readable description of this transform.
     */
    virtual std::string description() const = 0;

    /**
     * @brief Returns the extension of the files that this transform
     * can process.
     */
    virtual std::string extension() const = 0;

    /**
     * @brief Transforms the model at the supplied path into our
     * internal representation of an codec model. The extension is
     * used to find the appropriate decoding code.
     *
     * @param p Path to an external model.
     *
     * @pre Model must conform to the format supported by the
     * transform.
     *
     * @note Method is non-const by design at the moment as some
     * decoding transforms have mutable state.
     *
     * @note This function is receiving a path to the model, rather
     * than the file contents because at the moment the decoding
     * transform implementations cannot cope with string
     * processing. In the future this will change to a string.
     */
    virtual entities::model apply(const context& ctx,
        const boost::filesystem::path& p) = 0;
};

}

#endif
