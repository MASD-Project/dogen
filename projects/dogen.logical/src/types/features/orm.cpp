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
#include "dogen.logical/types/features/orm.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::logical::features {

namespace {

dogen::variability::entities::feature
make_masd_orm_database_system() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("database_system");
    r.name().qualified("masd.orm.database_system");
    r.description(R"(Database system to target for ORM support.)");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_table_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("table_name");
    r.name().qualified("masd.orm.table_name");
    r.description(R"(Name of the database table for this element.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_schema_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("schema_name");
    r.name().qualified("masd.orm.schema_name");
    r.description(R"(Name of the database schema for this modeling element.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_is_primary_key() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("is_primary_key");
    r.name().qualified("masd.orm.is_primary_key");
    r.description(R"(If true, this property will be used for the primary key.)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_column_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("column_name");
    r.name().qualified("masd.orm.column_name");
    r.description(R"(Overrides the name of the column name for the database table.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_is_nullable() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("is_nullable");
    r.name().qualified("masd.orm.is_nullable");
    r.description(R"(If true, the column can be null.)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_is_composite() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("is_composite");
    r.name().qualified("masd.orm.is_composite");
    r.description(R"(If true, the primary key is a composite key.)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::property);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_letter_case() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("letter_case");
    r.name().qualified("masd.orm.letter_case");
    r.description(R"(Determines the casing to use for identifiers.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_type_override() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("type_override");
    r.name().qualified("masd.orm.type_override");
    r.description(R"(Overrides to use for the relational type, for a given database system.

Note: we've set the binding point to "any" as a hack to allow for primitive support.
Should really be "property".)");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_type_mapping() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("type_mapping");
    r.name().qualified("masd.orm.type_mapping");
    r.description(R"(Type maps to create for the relational type, possibly for a given database system.

Note: we've set the binding point to "any" as a hack to allow for primitive support.
Should really be "property".)");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

dogen::variability::entities::feature
make_masd_orm_odb_pragma() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("odb_pragma");
    r.name().qualified("masd.orm.odb_pragma");
    r.description(R"(Raw ODB pragmas that are applied as-is by the system.

Use these when you need some functionality which is not natively supported by
ORM in Dogen.)");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    return r;
}

}

orm::feature_group
orm::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.database_system = s.get_by_name("masd.orm.database_system");
    r.table_name = s.get_by_name("masd.orm.table_name");
    r.schema_name = s.get_by_name("masd.orm.schema_name");
    r.is_primary_key = s.get_by_name("masd.orm.is_primary_key");
    r.column_name = s.get_by_name("masd.orm.column_name");
    r.is_nullable = s.get_by_name("masd.orm.is_nullable");
    r.is_composite = s.get_by_name("masd.orm.is_composite");
    r.letter_case = s.get_by_name("masd.orm.letter_case");
    r.type_override = s.get_by_name("masd.orm.type_override");
    r.type_mapping = s.get_by_name("masd.orm.type_mapping");
    r.odb_pragma = s.get_by_name("masd.orm.odb_pragma");

    return r;
}

orm::static_configuration orm::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.database_system))
        r.database_system = s.get_text_collection_content(fg.database_system);
    if (s.has_configuration_point(fg.table_name))
        r.table_name = s.get_text_content(fg.table_name);
    if (s.has_configuration_point(fg.schema_name))
        r.schema_name = s.get_text_content(fg.schema_name);
    if (s.has_configuration_point(fg.is_primary_key))
        r.is_primary_key = s.get_boolean_content(fg.is_primary_key);
    if (s.has_configuration_point(fg.column_name))
        r.column_name = s.get_text_content(fg.column_name);
    if (s.has_configuration_point(fg.is_nullable))
        r.is_nullable = s.get_boolean_content(fg.is_nullable);
    if (s.has_configuration_point(fg.is_composite))
        r.is_composite = s.get_boolean_content(fg.is_composite);
    if (s.has_configuration_point(fg.letter_case))
        r.letter_case = s.get_text_content(fg.letter_case);
    if (s.has_configuration_point(fg.type_override))
        r.type_override = s.get_text_collection_content(fg.type_override);
    if (s.has_configuration_point(fg.type_mapping))
        r.type_mapping = s.get_text_collection_content(fg.type_mapping);
    if (s.has_configuration_point(fg.odb_pragma))
        r.odb_pragma = s.get_text_collection_content(fg.odb_pragma);
    return r;
}

std::list<dogen::variability::entities::feature>
orm::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_orm_database_system());
    r.push_back(make_masd_orm_table_name());
    r.push_back(make_masd_orm_schema_name());
    r.push_back(make_masd_orm_is_primary_key());
    r.push_back(make_masd_orm_column_name());
    r.push_back(make_masd_orm_is_nullable());
    r.push_back(make_masd_orm_is_composite());
    r.push_back(make_masd_orm_letter_case());
    r.push_back(make_masd_orm_type_override());
    r.push_back(make_masd_orm_type_mapping());
    r.push_back(make_masd_orm_odb_pragma());
    return r;
}

}
