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
#ifndef DOGEN_ASSETS_TYPES_TRANSFORMS_ORM_TRANSFORM_HPP
#define DOGEN_ASSETS_TYPES_TRANSFORMS_ORM_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <vector>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/types/features/orm.hpp"
#include "dogen.assets/types/meta_model/orm/database_system.hpp"
#include "dogen.assets/types/meta_model/orm/model_properties.hpp"
#include "dogen.assets/types/meta_model/orm/object_properties.hpp"
#include "dogen.assets/types/meta_model/orm/module_properties.hpp"
#include "dogen.assets/types/meta_model/orm/attribute_properties.hpp"
#include "dogen.assets/types/meta_model/orm/primitive_properties.hpp"
#include "dogen.assets/types/transforms/context_fwd.hpp"

namespace dogen::assets::transforms {

class orm_transform final {
private:
    std::vector<meta_model::orm::database_system>
    static to_orm_database_system(const std::list<std::string>& vs);

    std::unordered_map<meta_model::orm::database_system, std::string>
    static make_type_overrides(const std::list<std::string> ls);

private:
    static boost::optional<meta_model::orm::model_properties>
    make_model_properties(const features::orm::feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static void update_object_properties(
        const features::orm::feature_group& fg,
        const variability::meta_model::configuration& cfg,
        meta_model::orm::object_properties& oop);

    static boost::optional<meta_model::orm::attribute_properties>
    make_attribute_properties(
        const features::orm::feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static void update_primitive_properties(
        const features::orm::feature_group& fg,
        const variability::meta_model::configuration& cfg,
        meta_model::orm::primitive_properties& opp);

    static boost::optional<meta_model::orm::module_properties>
    make_module_properties(const features::orm::feature_group& fg,
        const variability::meta_model::configuration& cfg);

private:
    static void transform_objects(const features::orm::feature_group& fg,
        meta_model::model& m);
    static void transform_object_templates(
        const features::orm::feature_group& fg, meta_model::model& m);
    static void transform_primitives(const features::orm::feature_group& fg,
        meta_model::model& m);
    static void transform_modules(const features::orm::feature_group& fg,
        meta_model::model& m);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
