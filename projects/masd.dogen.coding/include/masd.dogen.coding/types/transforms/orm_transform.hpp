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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_ORM_TRANSFORM_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_ORM_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <vector>
#include <unordered_map>
#include <boost/optional.hpp>
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/orm/letter_case.hpp"
#include "masd.dogen.coding/types/meta_model/orm/database_system.hpp"
#include "masd.dogen.coding/types/meta_model/orm/model_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm/object_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm/module_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm/attribute_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm/primitive_properties.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"

namespace masd::dogen::coding::transforms {

class orm_transform final {
private:
    static meta_model::orm::database_system
    to_orm_database_system(const std::string& s);

    std::vector<meta_model::orm::database_system>
    static to_orm_database_system(const std::list<std::string>& vs);

    static meta_model::orm::letter_case to_letter_case(const std::string& s);

    std::unordered_map<meta_model::orm::database_system, std::string>
    static make_type_overrides(const std::list<std::string> ls);

private:
    struct feature_group {
        variability::meta_model::feature database_system;
        variability::meta_model::feature table_name;
        variability::meta_model::feature schema_name;
        variability::meta_model::feature is_primary_key;
        variability::meta_model::feature column_name;
        variability::meta_model::feature is_nullable;
        variability::meta_model::feature letter_case;
        variability::meta_model::feature type_override;
        variability::meta_model::feature is_composite;
    };

    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm);

    static boost::optional<meta_model::orm::model_properties>
    make_model_properties(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static void update_object_properties(const feature_group& fg,
        const variability::meta_model::configuration& cfg,
        meta_model::orm::object_properties& oop);

    static boost::optional<meta_model::orm::attribute_properties>
    make_attribute_properties(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static void update_primitive_properties(const feature_group& fg,
        const variability::meta_model::configuration& cfg,
        meta_model::orm::primitive_properties& opp);

    static boost::optional<meta_model::orm::module_properties>
    make_module_properties(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

private:
    static void transform_objects(const feature_group& fg,
        meta_model::model& m);
    static void transform_object_templates(const feature_group& fg,
        meta_model::model& m);
    static void transform_primitives(const feature_group& fg,
        meta_model::model& m);
    static void transform_modules(const feature_group& fg,
        meta_model::model& m);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
