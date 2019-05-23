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
#include "dogen.assets/test_data/meta_model/name_td.hpp"
#include "dogen.assets/test_data/meta_model/element_td.hpp"
#include "dogen.generation.cpp/test_data/fabric/master_header_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::assets::meta_model::name
create_dogen_assets_meta_model_name(const unsigned int position) {
    return dogen::assets::meta_model::name_generator::create(position);
}

std::list<dogen::assets::meta_model::name> create_std_list_dogen_assets_meta_model_name(unsigned int position) {
    std::list<dogen::assets::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_assets_meta_model_name(position + i));
    }
    return r;
}

std::unordered_map<std::string, std::list<dogen::assets::meta_model::name> > create_std_unordered_map_std_string_std_list_dogen_assets_meta_model_name(unsigned int position) {
    std::unordered_map<std::string, std::list<dogen::assets::meta_model::name> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_list_dogen_assets_meta_model_name(position + i)));
    }
    return r;
}

std::unordered_map<std::string, std::unordered_map<std::string, std::list<dogen::assets::meta_model::name> > > create_std_unordered_map_std_string_std_unordered_map_std_string_std_list_dogen_assets_meta_model_name(unsigned int position) {
    std::unordered_map<std::string, std::unordered_map<std::string, std::list<dogen::assets::meta_model::name> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_unordered_map_std_string_std_list_dogen_assets_meta_model_name(position + i)));
    }
    return r;
}

}

namespace dogen::generation::cpp::fabric {

master_header_generator::master_header_generator() : position_(0) { }

void master_header_generator::
populate(const unsigned int position, result_type& v) {
    dogen::assets::meta_model::element_generator::populate(position, v);
    v.inclusion_by_facet(create_std_unordered_map_std_string_std_unordered_map_std_string_std_list_dogen_assets_meta_model_name(position + 0));
}

master_header_generator::result_type
master_header_generator::create(const unsigned int position) {
    master_header r;
    master_header_generator::populate(position, r);
    return r;
}

master_header_generator::result_type*
master_header_generator::create_ptr(const unsigned int position) {
    master_header* p = new master_header();
    master_header_generator::populate(position, *p);
    return p;
}

master_header_generator::result_type
master_header_generator::operator()() {
    return create(position_++);
}

}
