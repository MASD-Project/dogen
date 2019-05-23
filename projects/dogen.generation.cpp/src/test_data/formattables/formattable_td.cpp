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
#include "dogen.assets/test_data/meta_model/element_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/formattable_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/element_properties_td.hpp"

namespace {

dogen::assets::meta_model::element*
create_dogen_assets_meta_model_element_ptr(const unsigned int position) {
    return dogen::assets::meta_model::element_generator::create_ptr(position);
}

boost::shared_ptr<dogen::assets::meta_model::element>
create_boost_shared_ptr_dogen_assets_meta_model_element(unsigned int position) {
    boost::shared_ptr<dogen::assets::meta_model::element> r(
        create_dogen_assets_meta_model_element_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::assets::meta_model::element> > create_std_list_boost_shared_ptr_dogen_assets_meta_model_element(unsigned int position) {
    std::list<boost::shared_ptr<dogen::assets::meta_model::element> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_assets_meta_model_element(position + i));
    }
    return r;
}

dogen::generation::cpp::formattables::element_properties
create_dogen_generation_cpp_formattables_element_properties(const unsigned int position) {
    return dogen::generation::cpp::formattables::element_properties_generator::create(position);
}

}

namespace dogen::generation::cpp::formattables {

formattable_generator::formattable_generator() : position_(0) { }

void formattable_generator::
populate(const unsigned int position, result_type& v) {
    v.master_segment(create_boost_shared_ptr_dogen_assets_meta_model_element(position + 0));
    v.all_segments(create_std_list_boost_shared_ptr_dogen_assets_meta_model_element(position + 1));
    v.element_properties(create_dogen_generation_cpp_formattables_element_properties(position + 2));
}

formattable_generator::result_type
formattable_generator::create(const unsigned int position) {
    formattable r;
    formattable_generator::populate(position, r);
    return r;
}

formattable_generator::result_type*
formattable_generator::create_ptr(const unsigned int position) {
    formattable* p = new formattable();
    formattable_generator::populate(position, *p);
    return p;
}

formattable_generator::result_type
formattable_generator::operator()() {
    return create(position_++);
}

}
