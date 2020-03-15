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
#ifndef DOGEN_INJECTION_TYPES_TRANSFORMS_ENCODING_TRANSFORM_HPP
#define DOGEN_INJECTION_TYPES_TRANSFORMS_ENCODING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen.injection/types/meta_model/model.hpp"
#include "dogen.injection/types/transforms/context_fwd.hpp"

namespace dogen::injection::transforms {

/**
 * @brief Transform that converts models in our injection model
 * representation to an external format.
 */
class encoding_transform {
public:
    encoding_transform() = default;
    encoding_transform(const encoding_transform&) = delete;
    virtual ~encoding_transform() noexcept = default;

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
     * @brief Transforms our internal model representation into a
     * third-party representation
     *
     * @param ctx context in which the transformation is taking place.
     * @param m model to transform.
     *
     * @note Method is non-const by design at the moment as some
     * encoding transforms have state.
     *
     * @note This function is receiving a path to the model, rather
     * than return the file contents because at the moment the codecs
     * cannot cope with string processing. In the future this will
     * change to returning a string.
     */
    virtual void apply(const context& ctx, const meta_model::model& m,
        const boost::filesystem::path& p) = 0;
};

}

#endif
