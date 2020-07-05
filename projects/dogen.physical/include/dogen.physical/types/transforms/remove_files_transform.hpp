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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_REMOVE_FILES_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_REMOVE_FILES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/types/entities/model.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Removes all files that are associated with artefacts marked
 * with an operation of "remove".
 */
class remove_files_transform final {
private:
    static std::list<boost::shared_ptr<entities::artefact>>
    gather_artefacts(const entities::model& m);

    static void delete_extra_files(
        const std::list<boost::shared_ptr<entities::artefact>>& artefacts);

    static void delete_empty_directories(const entities::model& m);

public:
    static void apply(const context& ctx, const entities::model& m);
};

}

#endif
