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
#include "dogen/upsilon/test_data/model_td.hpp"
#include "dogen/upsilon/test_data/config_td.hpp"
#include "dogen/upsilon/test_data/schema_td.hpp"
#include "dogen/upsilon/test_data/type_information_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::upsilon::schema
create_dogen_upsilon_schema(const unsigned int position) {
    return dogen::upsilon::schema_generator::create(position);
}

std::unordered_map<std::string, dogen::upsilon::schema> create_std_unordered_map_std_string_dogen_upsilon_schema(unsigned int position) {
    std::unordered_map<std::string, dogen::upsilon::schema> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_upsilon_schema(position + i)));
    }
    return r;
}

dogen::upsilon::type_information
create_dogen_upsilon_type_information(const unsigned int position) {
    return dogen::upsilon::type_information_generator::create(position);
}

std::vector<dogen::upsilon::type_information> create_std_vector_dogen_upsilon_type_information(unsigned int position) {
    std::vector<dogen::upsilon::type_information> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_upsilon_type_information(position + i));
    }
    return r;
}

dogen::upsilon::config
create_dogen_upsilon_config(const unsigned int position) {
    return dogen::upsilon::config_generator::create(position);
}

}

namespace dogen {
namespace upsilon {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.schemas(create_std_unordered_map_std_string_dogen_upsilon_schema(position + 0));
    v.type_information(create_std_vector_dogen_upsilon_type_information(position + 1));
    v.config(create_dogen_upsilon_config(position + 2));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}

model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

} }
