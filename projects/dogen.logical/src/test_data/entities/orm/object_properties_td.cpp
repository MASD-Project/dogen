/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include <sstream>
#include "dogen.logical/test_data/entities/orm/letter_case_td.hpp"
#include "dogen.logical/test_data/entities/orm/odb_options_td.hpp"
#include "dogen.logical/test_data/entities/orm/type_mapping_td.hpp"
#include "dogen.logical/test_data/entities/orm/object_properties_td.hpp"

namespace {

dogen::logical::entities::orm::odb_options
create_dogen_logical_entities_orm_odb_options(const unsigned int position) {
    return dogen::logical::entities::orm::odb_options_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::logical::entities::orm::letter_case
create_dogen_logical_entities_orm_letter_case(const unsigned int position) {
    return dogen::logical::entities::orm::letter_case_generator::create(position);
}

boost::optional<dogen::logical::entities::orm::letter_case>
create_boost_optional_dogen_logical_entities_orm_letter_case(unsigned int position) {
    boost::optional<dogen::logical::entities::orm::letter_case> r(
        create_dogen_logical_entities_orm_letter_case(position));
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

dogen::logical::entities::orm::type_mapping
create_dogen_logical_entities_orm_type_mapping(const unsigned int position) {
    return dogen::logical::entities::orm::type_mapping_generator::create(position);
}

std::list<dogen::logical::entities::orm::type_mapping> create_std_list_dogen_logical_entities_orm_type_mapping(unsigned int position) {
    std::list<dogen::logical::entities::orm::type_mapping> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_logical_entities_orm_type_mapping(position + i));
    }
    return r;
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen::logical::entities::orm {

object_properties_generator::object_properties_generator() : position_(0) { }

void object_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.odb_options(create_dogen_logical_entities_orm_odb_options(position + 0));
    v.schema_name(create_std_string(position + 1));
    v.capitalised_schema_name(create_std_string(position + 2));
    v.letter_case(create_boost_optional_dogen_logical_entities_orm_letter_case(position + 3));
    v.generate_mapping(create_bool(position + 4));
    v.type_mappings(create_std_list_dogen_logical_entities_orm_type_mapping(position + 5));
    v.odb_pragmas(create_std_list_std_string(position + 6));
    v.table_name(create_std_string(position + 7));
    v.is_value(create_bool(position + 8));
    v.has_primary_key(create_bool(position + 9));
}

object_properties_generator::result_type
object_properties_generator::create(const unsigned int position) {
    object_properties r;
    object_properties_generator::populate(position, r);
    return r;
}

object_properties_generator::result_type*
object_properties_generator::create_ptr(const unsigned int position) {
    object_properties* p = new object_properties();
    object_properties_generator::populate(position, *p);
    return p;
}

object_properties_generator::result_type
object_properties_generator::operator()() {
    return create(position_++);
}

}
