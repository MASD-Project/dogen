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
#include <sstream>
#include "dogen.coding/test_data/meta_model/orm/letter_case_td.hpp"
#include "dogen.coding/test_data/meta_model/orm/database_system_td.hpp"
#include "dogen.coding/test_data/meta_model/orm/model_properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::coding::meta_model::orm::letter_case
create_dogen_coding_meta_model_orm_letter_case(const unsigned int position) {
    return dogen::coding::meta_model::orm::letter_case_generator::create(position);
}

boost::optional<dogen::coding::meta_model::orm::letter_case>
create_boost_optional_dogen_coding_meta_model_orm_letter_case(unsigned int position) {
    boost::optional<dogen::coding::meta_model::orm::letter_case> r(
        create_dogen_coding_meta_model_orm_letter_case(position));
    return r;
}

dogen::coding::meta_model::orm::database_system
create_dogen_coding_meta_model_orm_database_system(const unsigned int position) {
    return dogen::coding::meta_model::orm::database_system_generator::create(position);
}

std::vector<dogen::coding::meta_model::orm::database_system> create_std_vector_dogen_coding_meta_model_orm_database_system(unsigned int position) {
    std::vector<dogen::coding::meta_model::orm::database_system> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_coding_meta_model_orm_database_system(position + i));
    }
    return r;
}

}

namespace dogen::coding::meta_model::orm {

model_properties_generator::model_properties_generator() : position_(0) { }

void model_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.schema_name(create_std_string(position + 0));
    v.letter_case(create_boost_optional_dogen_coding_meta_model_orm_letter_case(position + 1));
    v.database_systems(create_std_vector_dogen_coding_meta_model_orm_database_system(position + 2));
}

model_properties_generator::result_type
model_properties_generator::create(const unsigned int position) {
    model_properties r;
    model_properties_generator::populate(position, r);
    return r;
}

model_properties_generator::result_type*
model_properties_generator::create_ptr(const unsigned int position) {
    model_properties* p = new model_properties();
    model_properties_generator::populate(position, *p);
    return p;
}

model_properties_generator::result_type
model_properties_generator::operator()() {
    return create(position_++);
}

}
