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
#include "dogen/yarn/test_data/name_td.hpp"
#include "dogen/yarn/test_data/name_tree_td.hpp"

namespace {

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

dogen::yarn::name_tree
create_dogen_yarn_name_tree(const unsigned int) {
    return dogen::yarn::name_tree();
}

std::list<dogen::yarn::name_tree> create_std_list_dogen_yarn_name_tree(unsigned int position) {
    std::list<dogen::yarn::name_tree> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_name_tree(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace yarn {

name_tree_generator::name_tree_generator() : position_(0) { }

void name_tree_generator::
populate(const unsigned int position, result_type& v) {
    v.parent(create_dogen_yarn_name(position + 0));
    v.children(create_std_list_dogen_yarn_name_tree(position + 1));
    v.are_children_opaque(create_bool(position + 2));
    v.is_circular_dependency(create_bool(position + 3));
}

name_tree_generator::result_type
name_tree_generator::create(const unsigned int position) {
    name_tree r;
    name_tree_generator::populate(position, r);
    return r;
}

name_tree_generator::result_type*
name_tree_generator::create_ptr(const unsigned int position) {
    name_tree* p = new name_tree();
    name_tree_generator::populate(position, *p);
    return p;
}

name_tree_generator::result_type
name_tree_generator::operator()() {
    return create(position_++);
}

} }
