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
#ifndef DOGEN_ASSETS_TYPES_HELPERS_VISUAL_STUDIO_PROJECT_TYPE_MAPPER_HPP
#define DOGEN_ASSETS_TYPES_HELPERS_VISUAL_STUDIO_PROJECT_TYPE_MAPPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iostream>
#include "dogen.assets/types/meta_model/technical_space.hpp"

namespace dogen::assets::helpers {

/**
 * @brief Maps asset meta-model concepts to visual studio project
 * types.
 */
class visual_studio_project_type_mapper final {
public:
    /**
     * @brief Maps a technical space to the associated Visual Studio
     * project type, if any such mapping exists.
     */
    static std::string
    from_technical_space(const meta_model::technical_space ts);
};

}

#endif
