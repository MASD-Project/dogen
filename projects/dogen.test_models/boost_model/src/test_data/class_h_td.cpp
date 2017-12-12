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
#include "dogen/test_models/boost_model/test_data/class_h_td.hpp"

namespace {

boost::property_tree::ptree
create_boost_property_tree_ptree(const unsigned int position) {
    using boost::property_tree::ptree;
    ptree c;
    c.put("key_2", position);
    ptree r;
    r.push_back(ptree::value_type("key_1", c));
    return r;
}

}

namespace dogen {
namespace test_models {
namespace boost_model {

class_h_generator::class_h_generator() : position_(0) { }

void class_h_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_boost_property_tree_ptree(position + 0));
}

class_h_generator::result_type
class_h_generator::create(const unsigned int position) {
    class_h r;
    class_h_generator::populate(position, r);
    return r;
}

class_h_generator::result_type*
class_h_generator::create_ptr(const unsigned int position) {
    class_h* p = new class_h();
    class_h_generator::populate(position, *p);
    return p;
}

class_h_generator::result_type
class_h_generator::operator()() {
    return create(position_++);
}

} } }
