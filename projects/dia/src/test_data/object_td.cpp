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
#include "dogen/dia/test_data/object_td.hpp"
#include "dogen/dia/test_data/attribute_td.hpp"
#include "dogen/dia/test_data/child_node_td.hpp"
#include "dogen/dia/test_data/connection_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

dogen::dia::connection
create_dogen_dia_connection(const unsigned int position) {
    return dogen::dia::connection_generator::create(position);
}

std::vector<dogen::dia::connection> create_std_vector_dogen_dia_connection(unsigned int position) {
    std::vector<dogen::dia::connection> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_dia_connection(position + i));
    }
    return r;
}

dogen::dia::child_node
create_dogen_dia_child_node(const unsigned int position) {
    return dogen::dia::child_node_generator::create(position);
}

boost::optional<dogen::dia::child_node>
create_boost_optional_dogen_dia_child_node(unsigned int position) {
    boost::optional<dogen::dia::child_node> r(
        create_dogen_dia_child_node(position));
    return r;
}

dogen::dia::attribute
create_dogen_dia_attribute(const unsigned int position) {
    return dogen::dia::attribute_generator::create(position);
}

std::vector<dogen::dia::attribute> create_std_vector_dogen_dia_attribute(unsigned int position) {
    std::vector<dogen::dia::attribute> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_dia_attribute(position + i));
    }
    return r;
}

}

namespace dogen {
namespace dia {

object_generator::object_generator() : position_(0) { }

void object_generator::
populate(const unsigned int position, result_type& v) {
    v.type(create_std_string(position + 0));
    v.version(create_int(position + 1));
    v.id(create_std_string(position + 2));
    v.connections(create_std_vector_dogen_dia_connection(position + 3));
    v.child_node(create_boost_optional_dogen_dia_child_node(position + 4));
    v.attributes(create_std_vector_dogen_dia_attribute(position + 5));
}

object_generator::result_type
object_generator::create(const unsigned int position) {
    object r;
    object_generator::populate(position, r);
    return r;
}

object_generator::result_type*
object_generator::create_ptr(const unsigned int position) {
    object* p = new object();
    object_generator::populate(position, *p);
    return p;
}

object_generator::result_type
object_generator::operator()() {
    return create(position_++);
}

} }
