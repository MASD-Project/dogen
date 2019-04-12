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
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/orm_model_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_object_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_module_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_attribute_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_primitive_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_database_systems.hpp"
#include "masd.dogen.coding/types/meta_model/letter_cases.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"

namespace masd::dogen::coding::transforms {

class orm_transform final {
private:
    static meta_model::orm_database_systems
    to_orm_database_system(const std::string& s);

    std::vector<meta_model::orm_database_systems>
    static to_orm_database_system(const std::list<std::string>& vs);

    static meta_model::letter_cases to_letter_case(const std::string& s);

    std::unordered_map<meta_model::orm_database_systems, std::string>
    static make_type_overrides(const std::list<std::string> ls);

private:
    struct type_group {
        variability::type database_system;
        variability::type table_name;
        variability::type schema_name;
        variability::type is_primary_key;
        variability::type column_name;
        variability::type is_nullable;
        variability::type letter_case;
        variability::type type_override;
        variability::type is_composite;
    };

    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    static type_group make_type_group(const variability::type_repository& atrp);

    static boost::optional<meta_model::orm_model_properties>
    make_model_properties(const type_group& tg,
        const variability::annotation& a);

    static void update_object_properties(const type_group& tg,
        const variability::annotation& a,
        meta_model::orm_object_properties& cfg);

    static boost::optional<meta_model::orm_attribute_properties>
    make_attribute_properties(
        const type_group& tg, const variability::annotation& a);

    static void update_primitive_properties(const type_group& tg,
        const variability::annotation& a,
        meta_model::orm_primitive_properties& cfg);

    static boost::optional<meta_model::orm_module_properties>
    make_module_properties(const type_group& tg,
        const variability::annotation& a);

private:
    static void transform_objects(const type_group& tg,
        meta_model::model& m);
    static void transform_object_templates(const type_group& tg,
        meta_model::model& m);
    static void transform_primitives(const type_group& tg,
        meta_model::model& m);
    static void transform_modules(const type_group& tg,
        meta_model::model& m);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
