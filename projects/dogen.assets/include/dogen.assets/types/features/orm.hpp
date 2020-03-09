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
#ifndef DOGEN_ASSETS_TYPES_FEATURES_ORM_HPP
#define DOGEN_ASSETS_TYPES_FEATURES_ORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/optional.hpp>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"

namespace dogen::assets::features {

/**
 * @brief Features related to ORM support.
 */
class orm final {
public:
    struct feature_group {
        variability::meta_model::feature database_system;
        variability::meta_model::feature table_name;
        variability::meta_model::feature schema_name;
        variability::meta_model::feature is_primary_key;
        variability::meta_model::feature column_name;
        variability::meta_model::feature is_nullable;
        variability::meta_model::feature is_composite;
        variability::meta_model::feature letter_case;
        variability::meta_model::feature type_override;
        variability::meta_model::feature type_mapping;
        variability::meta_model::feature odb_pragma;
    };

    static feature_group
    make_feature_group(const variability::meta_model::feature_model& fm);

public:
    struct static_configuration {
        std::list<std::string> database_system;
        std::string table_name;
        std::string schema_name;
        boost::optional<bool> is_primary_key;
        std::string column_name;
        boost::optional<bool> is_nullable;
        boost::optional<bool> is_composite;
        std::string letter_case;
        std::list<std::string> type_override;
        std::list<std::string> type_mapping;
        std::list<std::string> odb_pragma;
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
