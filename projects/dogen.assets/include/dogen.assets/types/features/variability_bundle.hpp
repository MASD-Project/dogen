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
#ifndef DOGEN_ASSETS_TYPES_FEATURES_VARIABILITY_BUNDLE_HPP
#define DOGEN_ASSETS_TYPES_FEATURES_VARIABILITY_BUNDLE_HPP

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
 * @brief Features related to the processing of variability for feature bundles.
 */
class variability_bundle final {
public:
    struct feature_group {
        variability::meta_model::feature generate_registration;
        variability::meta_model::feature generate_static_configuration;
        variability::meta_model::feature kernel;
        variability::meta_model::feature backend;
        variability::meta_model::feature facet;
        variability::meta_model::feature archetype;
        variability::meta_model::feature template_kind;
        variability::meta_model::feature default_binding_point;
        variability::meta_model::feature instantiation_domain_name;
    };

    static feature_group
    make_feature_group(const variability::meta_model::feature_model& fm);

public:
    struct static_configuration {
        bool generate_registration;
        bool generate_static_configuration;
        std::string kernel;
        std::string backend;
        std::string facet;
        std::string archetype;
        std::string template_kind;
        std::string default_binding_point;
        std::string instantiation_domain_name;

        static_configuration() :
            generate_registration(),
            generate_static_configuration() {}
    };

    static static_configuration make_static_configuration(
        const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    template<typename Configurable>
    static static_configuration make_static_configuration(
        const feature_group& fg, const Configurable& c) {
        return make_static_configuration(fg, *c.configuration());
    }

public:
    static std::list<dogen::variability::meta_model::feature>
    make_features();
};

}

#endif
