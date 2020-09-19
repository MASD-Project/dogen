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
#ifndef DOGEN_ORCHESTRATION_TYPES_HELPERS_LOGICAL_TO_PHYSICAL_PROJECTOR_HPP
#define DOGEN_ORCHESTRATION_TYPES_HELPERS_LOGICAL_TO_PHYSICAL_PROJECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.text/types/entities/logical_physical_region.hpp"

namespace dogen::orchestration::helpers {

/*
 * Projects a set of logical elements into regions of physical space.
*/
class logical_to_physical_projector final {
public:
    static std::list<text::entities::logical_physical_region>
    project(const physical::entities::meta_model& pmm,
        const logical::entities::model& lm);
};

}

#endif
