/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/test_data/node_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"

namespace {

dogen::sml::node*
create_dogen_sml_node_ptr(const unsigned int) {
    return nullptr;
}

boost::shared_ptr<dogen::sml::node>
create_boost_shared_ptr_dogen_sml_node(unsigned int position) {
    boost::shared_ptr<dogen::sml::node> r(
        create_dogen_sml_node_ptr(position));
    return r;
}

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

std::list<boost::shared_ptr<dogen::sml::node> > create_std_list_boost_shared_ptr_dogen_sml_node_(unsigned int position) {
    std::list<boost::shared_ptr<dogen::sml::node> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_sml_node(position + i));
    }
    return r;
}

}

namespace dogen {
namespace sml {

node_generator::node_generator() : position_(0) { }

void node_generator::
populate(const unsigned int position, result_type& v) {
    v.parent(create_boost_shared_ptr_dogen_sml_node(position + 0));
    v.data(create_dogen_sml_qname(position + 1));
    v.children(create_std_list_boost_shared_ptr_dogen_sml_node_(position + 2));
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

} }
