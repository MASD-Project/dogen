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
#include "dogen.modeling/test_data/meta_model/letter_cases_td.hpp"
#include "dogen.modeling/test_data/meta_model/orm_database_systems_td.hpp"
#include "dogen.modeling/test_data/meta_model/orm_model_properties_td.hpp"

namespace {

dogen::modeling::meta_model::orm_database_systems
create_dogen_modeling_meta_model_orm_database_systems(const unsigned int position) {
    return dogen::modeling::meta_model::orm_database_systems_generator::create(position);
}

std::vector<dogen::modeling::meta_model::orm_database_systems> create_std_vector_dogen_modeling_meta_model_orm_database_systems(unsigned int position) {
    std::vector<dogen::modeling::meta_model::orm_database_systems> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_modeling_meta_model_orm_database_systems(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::modeling::meta_model::letter_cases
create_dogen_modeling_meta_model_letter_cases(const unsigned int position) {
    return dogen::modeling::meta_model::letter_cases_generator::create(position);
}

boost::optional<dogen::modeling::meta_model::letter_cases>
create_boost_optional_dogen_modeling_meta_model_letter_cases(unsigned int position) {
    boost::optional<dogen::modeling::meta_model::letter_cases> r(
        create_dogen_modeling_meta_model_letter_cases(position));
    return r;
}

}

namespace dogen {
namespace modeling {
namespace meta_model {

orm_model_properties_generator::orm_model_properties_generator() : position_(0) { }

void orm_model_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.database_systems(create_std_vector_dogen_modeling_meta_model_orm_database_systems(position + 0));
    v.schema_name(create_std_string(position + 1));
    v.letter_case(create_boost_optional_dogen_modeling_meta_model_letter_cases(position + 2));
}

orm_model_properties_generator::result_type
orm_model_properties_generator::create(const unsigned int position) {
    orm_model_properties r;
    orm_model_properties_generator::populate(position, r);
    return r;
}

orm_model_properties_generator::result_type*
orm_model_properties_generator::create_ptr(const unsigned int position) {
    orm_model_properties* p = new orm_model_properties();
    orm_model_properties_generator::populate(position, *p);
    return p;
}

orm_model_properties_generator::result_type
orm_model_properties_generator::operator()() {
    return create(position_++);
}

} } }
