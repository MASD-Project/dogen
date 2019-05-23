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
#include "dogen.assets/test_data/meta_model/model_td.hpp"
#include "dogen.assets/test_data/meta_model/model_set_td.hpp"

namespace {

dogen::assets::meta_model::model
create_dogen_assets_meta_model_model(const unsigned int position) {
    return dogen::assets::meta_model::model_generator::create(position);
}

std::list<dogen::assets::meta_model::model> create_std_list_dogen_assets_meta_model_model(unsigned int position) {
    std::list<dogen::assets::meta_model::model> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_assets_meta_model_model(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

}

namespace dogen::assets::meta_model {

model_set_generator::model_set_generator() : position_(0) { }

void model_set_generator::
populate(const unsigned int position, result_type& v) {
    v.target(create_dogen_assets_meta_model_model(position + 0));
    v.references(create_std_list_dogen_assets_meta_model_model(position + 1));
    v.fixed_mappings(create_std_unordered_map_std_string_std_string(position + 2));
}

model_set_generator::result_type
model_set_generator::create(const unsigned int position) {
    model_set r;
    model_set_generator::populate(position, r);
    return r;
}

model_set_generator::result_type*
model_set_generator::create_ptr(const unsigned int position) {
    model_set* p = new model_set();
    model_set_generator::populate(position, *p);
    return p;
}

model_set_generator::result_type
model_set_generator::operator()() {
    return create(position_++);
}

}
