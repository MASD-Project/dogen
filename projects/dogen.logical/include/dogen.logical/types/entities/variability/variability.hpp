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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_VARIABILITY_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_VARIABILITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Houses all of the meta-modeling elements related to variability.
 *
 * There are two "kinds" of entities in this namespace:
 *
 * - those that are used to model the data required to code-generate dogen's
 *   implementation of variability. That is to say, none of these elements are
 *   directly involved in the processing of variability model data (i.e. the
 *   current user model we are processing), but instead they generate code that
 *   injects variability data once compiled and integrated into dogen. These types
 *   setup the geometry of variability space: feature bundle and feature bundle
 *   templates and related types.
 *
 * - those that inject variability data as part of the processing of the current
 *   user model. These types are responsible for instantiating configurations,
 *   within the prevailing geometry of variability space. Example: profile and
 *   profile templates.
 *
 * Now, it is a bit confusing how variability interacts with the variability
 * meta-model elements, and it may appear that we repat ourselves quite a bit when
 * declaring the variability feature bundles. This is a consequence of the two
 * types of uses for variability types described above. Lets explore this in more
 * detail.
 *
 * In general, we tend to declare (register) features and create the static
 * configuration in the same place. This works for almost all cases because we
 * normally declare the features where we consume them. Profiles are /different/: a
 * profile is making use of a feature declared for a feature (simplifying
 * somewhat). That is, at run time, a profile is the instantiation of a feature
 * defined elsewhere. Remember that features are nothing more than a type system
 * designed to give a "strongly typed" feel to the meta-data. Profiles are just an
 * instantiation of those strong types.
 *
 * In theory, profile meta-data should already exist and match exactly what was
 * defined for features; in practice there is a mismatch, and this is due to how we
 * modeled features and feature bundles: to avoid repetition, we placed some
 * features at the top-level and others in the features themselves. This approach
 * does not match the shape required for profiles, so we need to redefine the
 * bundle. However, of course, we do not want to register the features this time
 * around (after all, they already exist) so we need to disable feature
 * registration. In the future we hope to simplify this by making the shapes
 * align - though perhaps it will have the underisable side-effect of hiding all of
 * this complexity.
 */
namespace dogen::logical::entities::variability {
}

#endif
