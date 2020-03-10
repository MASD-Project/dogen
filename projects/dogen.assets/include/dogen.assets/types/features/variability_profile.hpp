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
#ifndef DOGEN_ASSETS_TYPES_FEATURES_VARIABILITY_PROFILE_HPP
#define DOGEN_ASSETS_TYPES_FEATURES_VARIABILITY_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"

namespace dogen::assets::features {

/**
 * @brief Features related to the processing of variability for profiles and profile templates.
 *
 * Notes on why we need to disable feature registration:
 *
 * In general, we always declare (register) the features and create the static
 * configuration in the same place. This works for almost all cases because we tend
 * to declare the features where we consume them. Profiles are different: a profile is
 * making use of a feature declared for a feature. That is, a profile is the instantiation
 * of a feature defined elsewhere; remember that features are nothing more than a
 * type system designed to give a "strongly typed" feel to the meta-data. Profiles are
 * just an instantiation of those strong types. In theory, profile meta-data should
 * already exist and match exactly what was defined for features. In practice there is a
 * mismatch, and this is due to how we modeled features and feature bundles: to
 * avoid repetition, we placed some features at the top-level and others in the
 * features themselves. This approach does not match the shape required for
 * profiles, so we need to redefine the bundle. However, of course, we do not want to
 * register the features this time around (after all, they already exist) so we need
 * to disable feature registration.
 */
class variability_profile final {
public:
    struct feature_group {
        variability::meta_model::feature binding_point;
        variability::meta_model::feature labels;
        variability::meta_model::feature kernel;
        variability::meta_model::feature backend;
        variability::meta_model::feature facet;
        variability::meta_model::feature archetype;
        variability::meta_model::feature template_kind;
        variability::meta_model::feature value;
    };

    static feature_group
    make_feature_group(const variability::meta_model::feature_model& fm);

public:
    struct static_configuration {
        std::string binding_point;
        std::list<std::string> labels;
        std::string kernel;
        std::string backend;
        std::string facet;
        std::string archetype;
        std::string template_kind;
        std::list<std::string> value;
    };

    static static_configuration make_static_configuration(
        const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    template<typename Configurable>
    static static_configuration make_static_configuration(
        const feature_group& fg, const Configurable& c) {
        return make_static_configuration(fg, *c.configuration());
    }

};

}

#endif
