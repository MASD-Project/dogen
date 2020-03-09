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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_VARIABILITY_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_VARIABILITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Houses all of the meta-modeling elements related to variability.
 *
 * There are two "kinds" of entities in this namespace:
 *
 * @li those that are used to model the data required to code-
 * generate dogen's implementation of variability. That is to say,
 * none of these elements are directly involved in the processing
 *  of variability model data, but instead they generate code
 * that then injects variability data once compiled and integrated
 * into dogen. These are the feature bundle and feature bundle
 * templates and related types.
 *
 * @li those that inject variability data as part of the processing
 * of the current model. These types are responsible for
 * instantiating configurations. Example: profile and profile
 * templates.
 */
namespace dogen::assets::meta_model {
}

#endif
