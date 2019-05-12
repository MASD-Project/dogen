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
#include "masd.dogen.coding/types/features/orm.hpp"
#include "masd.dogen.variability/types/helpers/value_factory.hpp"

namespace masd::dogen::coding::features {

namespace {

masd::dogen::variability::meta_model::feature_template
make_masd_orm_database_system() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("database_system");
    r.name().qualified("masd.orm.database_system");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_orm_table_name() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("table_name");
    r.name().qualified("masd.orm.table_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_orm_schema_name() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("schema_name");
    r.name().qualified("masd.orm.schema_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_orm_is_primary_key() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("is_primary_key");
    r.name().qualified("masd.orm.is_primary_key");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_orm_column_name() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("column_name");
    r.name().qualified("masd.orm.column_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_orm_is_nullable() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("is_nullable");
    r.name().qualified("masd.orm.is_nullable");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_orm_is_composite() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("is_composite");
    r.name().qualified("masd.orm.is_composite");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_orm_letter_case() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("letter_case");
    r.name().qualified("masd.orm.letter_case");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_orm_type_override() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("type_override");
    r.name().qualified("masd.orm.type_override");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

}

std::list<masd::dogen::variability::meta_model::feature_template>
orm::make_templates() {
    using namespace masd::dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_masd_orm_database_system());
    r.push_back(make_masd_orm_table_name());
    r.push_back(make_masd_orm_schema_name());
    r.push_back(make_masd_orm_is_primary_key());
    r.push_back(make_masd_orm_column_name());
    r.push_back(make_masd_orm_is_nullable());
    r.push_back(make_masd_orm_is_composite());
    r.push_back(make_masd_orm_letter_case());
    r.push_back(make_masd_orm_type_override());
    return r;
}

}
