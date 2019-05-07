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
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/attribute_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/primitive_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/orm/primitive_properties_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

masd::dogen::coding::meta_model::attribute
create_masd_dogen_coding_meta_model_attribute(const unsigned int position) {
    return masd::dogen::coding::meta_model::attribute_generator::create(position);
}

masd::dogen::coding::meta_model::orm::primitive_properties
create_masd_dogen_coding_meta_model_orm_primitive_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::orm::primitive_properties_generator::create(position);
}

boost::optional<masd::dogen::coding::meta_model::orm::primitive_properties>
create_boost_optional_masd_dogen_coding_meta_model_orm_primitive_properties(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::orm::primitive_properties> r(
        create_masd_dogen_coding_meta_model_orm_primitive_properties(position));
    return r;
}

}

namespace masd::dogen::coding::meta_model {

primitive_generator::primitive_generator() : position_(0) { }

void primitive_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
    v.is_nullable(create_bool(position + 0));
    v.value_attribute(create_masd_dogen_coding_meta_model_attribute(position + 1));
    v.use_type_aliasing(create_bool(position + 2));
    v.is_immutable(create_bool(position + 3));
    v.orm_properties(create_boost_optional_masd_dogen_coding_meta_model_orm_primitive_properties(position + 4));
}

primitive_generator::result_type
primitive_generator::create(const unsigned int position) {
    primitive r;
    primitive_generator::populate(position, r);
    return r;
}

primitive_generator::result_type*
primitive_generator::create_ptr(const unsigned int position) {
    primitive* p = new primitive();
    primitive_generator::populate(position, *p);
    return p;
}

primitive_generator::result_type
primitive_generator::operator()() {
    return create(position_++);
}

}
