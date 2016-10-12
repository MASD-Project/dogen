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
#include "dogen/annotations/test_data/value_td.hpp"
#include "dogen/annotations/test_data/template_kinds_td.hpp"
#include "dogen/annotations/test_data/value_template_td.hpp"
#include "dogen/annotations/test_data/ownership_hierarchy_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::annotations::ownership_hierarchy
create_dogen_annotations_ownership_hierarchy(const unsigned int position) {
    return dogen::annotations::ownership_hierarchy_generator::create(position);
}

dogen::annotations::value*
create_dogen_annotations_value_ptr(const unsigned int position) {
    return dogen::annotations::value_generator::create_ptr(position);
}

boost::shared_ptr<dogen::annotations::value>
create_boost_shared_ptr_dogen_annotations_value(unsigned int position) {
    boost::shared_ptr<dogen::annotations::value> r(
        create_dogen_annotations_value_ptr(position));
    return r;
}

dogen::annotations::template_kinds
create_dogen_annotations_template_kinds(const unsigned int position) {
    return dogen::annotations::template_kinds_generator::create(position);
}

}

namespace dogen {
namespace annotations {

value_template_generator::value_template_generator() : position_(0) { }

void value_template_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.ownership_hierarchy(create_dogen_annotations_ownership_hierarchy(position + 1));
    v.value(create_boost_shared_ptr_dogen_annotations_value(position + 2));
    v.kind(create_dogen_annotations_template_kinds(position + 3));
}

value_template_generator::result_type
value_template_generator::create(const unsigned int position) {
    value_template r;
    value_template_generator::populate(position, r);
    return r;
}

value_template_generator::result_type*
value_template_generator::create_ptr(const unsigned int position) {
    value_template* p = new value_template();
    value_template_generator::populate(position, *p);
    return p;
}

value_template_generator::result_type
value_template_generator::operator()() {
    return create(position_++);
}

} }
