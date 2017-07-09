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
#include "dogen/yarn/test_data/helpers/node_td.hpp"

namespace {

dogen::yarn::helpers::node*
create_dogen_yarn_helpers_node_ptr(const unsigned int) {
    return nullptr;
}

boost::shared_ptr<dogen::yarn::helpers::node>
create_boost_shared_ptr_dogen_yarn_helpers_node(unsigned int position) {
    boost::shared_ptr<dogen::yarn::helpers::node> r(
        create_dogen_yarn_helpers_node_ptr(position));
    return r;
}

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

std::list<boost::shared_ptr<dogen::yarn::helpers::node> > create_std_list_boost_shared_ptr_dogen_yarn_helpers_node(unsigned int position) {
    std::list<boost::shared_ptr<dogen::yarn::helpers::node> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_yarn_helpers_node(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {
namespace helpers {

node_generator::node_generator() : position_(0) { }

void node_generator::
populate(const unsigned int position, result_type& v) {
    v.parent(create_boost_shared_ptr_dogen_yarn_helpers_node(position + 0));
    v.data(create_dogen_yarn_name(position + 1));
    v.children(create_std_list_boost_shared_ptr_dogen_yarn_helpers_node(position + 2));
}

node_generator::result_type
node_generator::create(const unsigned int position) {
    node r;
    node_generator::populate(position, r);
    return r;
}

node_generator::result_type*
node_generator::create_ptr(const unsigned int position) {
    node* p = new node();
    node_generator::populate(position, *p);
    return p;
}

node_generator::result_type
node_generator::operator()() {
    return create(position_++);
}

} } }
