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
#ifndef DOGEN_CODEC_TYPES_FEATURES_META_DATA_HPP
#define DOGEN_CODEC_TYPES_FEATURES_META_DATA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/optional.hpp>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"

namespace dogen::codec::features {

/**
 * @brief Assorted meta-data.
 */
class meta_data final {
public:
    struct feature_group {
        variability::entities::feature stereotypes;
        variability::entities::feature type;
        variability::entities::feature value;
        variability::entities::feature parent;
        variability::entities::feature can_be_primitive_underlier;
        variability::entities::feature in_global_module;
        variability::entities::feature can_be_enumeration_underlier;
        variability::entities::feature is_default_enumeration_type;
        variability::entities::feature is_associative_container;
        variability::entities::feature is_floating_point;
    };

    static feature_group
    make_feature_group(const variability::entities::feature_model& fm);

public:
    struct static_configuration {
        std::list<std::string> stereotypes;
        std::string type;
        std::string value;
        std::list<std::string> parent;
        boost::optional<bool> can_be_primitive_underlier;
        boost::optional<bool> in_global_module;
        boost::optional<bool> can_be_enumeration_underlier;
        boost::optional<bool> is_default_enumeration_type;
        boost::optional<bool> is_associative_container;
        boost::optional<bool> is_floating_point;
    };

    static static_configuration make_static_configuration(
        const feature_group& fg,
        const variability::entities::configuration& cfg);

    template<typename Configurable>
    static static_configuration make_static_configuration(
        const feature_group& fg, const Configurable& c) {
        return make_static_configuration(fg, *c.configuration());
    }

public:
    static std::list<dogen::variability::entities::feature>
    make_features();
};

}

#endif
