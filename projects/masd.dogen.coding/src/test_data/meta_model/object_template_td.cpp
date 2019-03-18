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
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/attribute_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/object_template_td.hpp"

namespace {

masd::dogen::coding::meta_model::attribute
create_masd_dogen_coding_meta_model_attribute(const unsigned int position) {
    return masd::dogen::coding::meta_model::attribute_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::attribute> create_std_list_masd_dogen_coding_meta_model_attribute(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::attribute> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_attribute(position + i));
    }
    return r;
}

masd::dogen::coding::meta_model::name
create_masd_dogen_coding_meta_model_name(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_generator::create(position);
}

std::unordered_map<masd::dogen::coding::meta_model::name, std::list<masd::dogen::coding::meta_model::attribute> > create_std_unordered_map_masd_dogen_coding_meta_model_name_std_list_masd_dogen_coding_meta_model_attribute(unsigned int position) {
    std::unordered_map<masd::dogen::coding::meta_model::name, std::list<masd::dogen::coding::meta_model::attribute> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_masd_dogen_coding_meta_model_name(position + i), create_std_list_masd_dogen_coding_meta_model_attribute(position + i)));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::list<masd::dogen::coding::meta_model::name> create_std_list_masd_dogen_coding_meta_model_name(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_name(position + i));
    }
    return r;
}

}

namespace masd::dogen::coding::meta_model {

object_template_generator::object_template_generator() : position_(0) { }

void object_template_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
    v.all_attributes(create_std_list_masd_dogen_coding_meta_model_attribute(position + 0));
    v.local_attributes(create_std_list_masd_dogen_coding_meta_model_attribute(position + 1));
    v.inherited_attributes(create_std_unordered_map_masd_dogen_coding_meta_model_name_std_list_masd_dogen_coding_meta_model_attribute(position + 2));
    v.is_immutable(create_bool(position + 3));
    v.is_fluent(create_bool(position + 4));
    v.parents(create_std_list_masd_dogen_coding_meta_model_name(position + 5));
    v.is_child(create_bool(position + 6));
}

object_template_generator::result_type
object_template_generator::create(const unsigned int position) {
    object_template r;
    object_template_generator::populate(position, r);
    return r;
}

object_template_generator::result_type*
object_template_generator::create_ptr(const unsigned int position) {
    object_template* p = new object_template();
    object_template_generator::populate(position, *p);
    return p;
}

object_template_generator::result_type
object_template_generator::operator()() {
    return create(position_++);
}

}
