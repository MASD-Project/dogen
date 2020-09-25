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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_PATHS_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_PATHS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/entities/backend_properties.hpp"
#include "dogen.physical/types/transforms/context.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Computes all file-system related paths within physical
 * space.
 */
class paths_transform final {
private:
    /**
     * @brief Computes the top-level path to the component.
     */
    static boost::filesystem::path
    compute_project_path(const boost::filesystem::path& output_directory,
        const identification::entities::logical_name& ln);

    /**
     * @brief Computes the path to the backend.
     */
    static void
    compute_backend_paths(const boost::filesystem::path& project_path,
        std::unordered_map<identification::entities::physical_meta_id,
        physical::entities::backend_properties>& bps);

public:
    /**
     * @brief Apply the transform to the supplied model.
     */
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
