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
#include "masd.dogen.coding/test_data/meta_model/orm/letter_case_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/orm/object_properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::coding::meta_model::orm::letter_case
create_masd_dogen_coding_meta_model_orm_letter_case(const unsigned int position) {
    return masd::dogen::coding::meta_model::orm::letter_case_generator::create(position);
}

boost::optional<masd::dogen::coding::meta_model::orm::letter_case>
create_boost_optional_masd_dogen_coding_meta_model_orm_letter_case(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::orm::letter_case> r(
        create_masd_dogen_coding_meta_model_orm_letter_case(position));
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace masd::dogen::coding::meta_model::orm {

object_properties_generator::object_properties_generator() : position_(0) { }

void object_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.schema_name(create_std_string(position + 0));
    v.letter_case(create_boost_optional_masd_dogen_coding_meta_model_orm_letter_case(position + 1));
    v.generate_mapping(create_bool(position + 2));
    v.table_name(create_std_string(position + 3));
    v.is_value(create_bool(position + 4));
    v.has_primary_key(create_bool(position + 5));
}

object_properties_generator::result_type
object_properties_generator::create(const unsigned int position) {
    object_properties r;
    object_properties_generator::populate(position, r);
    return r;
}

object_properties_generator::result_type*
object_properties_generator::create_ptr(const unsigned int position) {
    object_properties* p = new object_properties();
    object_properties_generator::populate(position, *p);
    return p;
}

object_properties_generator::result_type
object_properties_generator::operator()() {
    return create(position_++);
}

}
