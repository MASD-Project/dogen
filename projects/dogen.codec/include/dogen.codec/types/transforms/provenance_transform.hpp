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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_PROVENANCE_TRANSFORM_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_PROVENANCE_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/transforms/context_fwd.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Computes the SHA1 hash for a model content and updates the
 * model with this value.
 */
class provenance_transform final {
private:
    /**
     * @brief Computes the SHA1 hash for the supplied path.
     */
    static identification::entities::sha1_hash
    compute_shah1_hash(const boost::filesystem::path& p);

public:
    static void apply(const transforms::context& ctx,
        const boost::filesystem::path& p, entities::model& m);
};

}

#endif
