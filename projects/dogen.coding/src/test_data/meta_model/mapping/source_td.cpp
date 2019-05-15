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
#include "dogen.coding/test_data/meta_model/name_td.hpp"
#include "dogen.coding/test_data/meta_model/element_td.hpp"
#include "dogen.coding/test_data/meta_model/name_tree_td.hpp"
#include "dogen.coding/test_data/meta_model/mapping/source_td.hpp"
#include "dogen.coding/test_data/meta_model/technical_space_td.hpp"
#include "dogen.coding/test_data/meta_model/mapping/destination_td.hpp"

namespace {

dogen::coding::meta_model::mapping::destination
create_dogen_coding_meta_model_mapping_destination(const unsigned int position) {
    return dogen::coding::meta_model::mapping::destination_generator::create(position);
}

std::list<dogen::coding::meta_model::mapping::destination> create_std_list_dogen_coding_meta_model_mapping_destination(unsigned int position) {
    std::list<dogen::coding::meta_model::mapping::destination> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_coding_meta_model_mapping_destination(position + i));
    }
    return r;
}

dogen::coding::meta_model::technical_space
create_dogen_coding_meta_model_technical_space(const unsigned int position) {
    return dogen::coding::meta_model::technical_space_generator::create(position);
}

dogen::coding::meta_model::name
create_dogen_coding_meta_model_name(const unsigned int position) {
    return dogen::coding::meta_model::name_generator::create(position);
}

std::list<dogen::coding::meta_model::name> create_std_list_dogen_coding_meta_model_name(unsigned int position) {
    std::list<dogen::coding::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_coding_meta_model_name(position + i));
    }
    return r;
}

std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> > create_std_unordered_map_dogen_coding_meta_model_technical_space_std_list_dogen_coding_meta_model_name(unsigned int position) {
    std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_coding_meta_model_technical_space(position + i), create_std_list_dogen_coding_meta_model_name(position + i)));
    }
    return r;
}

dogen::coding::meta_model::name_tree
create_dogen_coding_meta_model_name_tree(const unsigned int position) {
    return dogen::coding::meta_model::name_tree_generator::create(position);
}

std::list<dogen::coding::meta_model::name_tree> create_std_list_dogen_coding_meta_model_name_tree(unsigned int position) {
    std::list<dogen::coding::meta_model::name_tree> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_coding_meta_model_name_tree(position + i));
    }
    return r;
}

std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> > create_std_unordered_map_dogen_coding_meta_model_technical_space_std_list_dogen_coding_meta_model_name_tree(unsigned int position) {
    std::unordered_map<dogen::coding::meta_model::technical_space, std::list<dogen::coding::meta_model::name_tree> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_coding_meta_model_technical_space(position + i), create_std_list_dogen_coding_meta_model_name_tree(position + i)));
    }
    return r;
}

}

namespace dogen::coding::meta_model::mapping {

source_generator::source_generator() : position_(0) { }

void source_generator::
populate(const unsigned int position, result_type& v) {
    dogen::coding::meta_model::element_generator::populate(position, v);
    v.destinations(create_std_list_dogen_coding_meta_model_mapping_destination(position + 0));
    v.names_by_technical_space(create_std_unordered_map_dogen_coding_meta_model_technical_space_std_list_dogen_coding_meta_model_name(position + 1));
    v.name_trees_by_technical_space(create_std_unordered_map_dogen_coding_meta_model_technical_space_std_list_dogen_coding_meta_model_name_tree(position + 2));
}

source_generator::result_type
source_generator::create(const unsigned int position) {
    source r;
    source_generator::populate(position, r);
    return r;
}

source_generator::result_type*
source_generator::create_ptr(const unsigned int position) {
    source* p = new source();
    source_generator::populate(position, *p);
    return p;
}

source_generator::result_type
source_generator::operator()() {
    return create(position_++);
}

}
