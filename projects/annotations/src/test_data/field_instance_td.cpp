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
#include "dogen/annotations/test_data/value_td.hpp"
#include "dogen/annotations/test_data/field_instance_td.hpp"

namespace {

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

}

namespace dogen {
namespace annotations {

field_instance_generator::field_instance_generator() : position_(0) { }

void field_instance_generator::
populate(const unsigned int position, result_type& v) {
    v.value(create_boost_shared_ptr_dogen_annotations_value(position + 0));
}

field_instance_generator::result_type
field_instance_generator::create(const unsigned int position) {
    field_instance r;
    field_instance_generator::populate(position, r);
    return r;
}

field_instance_generator::result_type*
field_instance_generator::create_ptr(const unsigned int position) {
    field_instance* p = new field_instance();
    field_instance_generator::populate(position, *p);
    return p;
}

field_instance_generator::result_type
field_instance_generator::operator()() {
    return create(position_++);
}

} }
