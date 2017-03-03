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
#include "dogen/yarn/test_data/letter_cases_td.hpp"
#include "dogen/yarn/test_data/orm_object_configuration_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::letter_cases
create_dogen_yarn_letter_cases(const unsigned int position) {
    return dogen::yarn::letter_cases_generator::create(position);
}

boost::optional<dogen::yarn::letter_cases>
create_boost_optional_dogen_yarn_letter_cases(unsigned int position) {
    boost::optional<dogen::yarn::letter_cases> r(
        create_dogen_yarn_letter_cases(position));
    return r;
}

}

namespace dogen {
namespace yarn {

orm_object_configuration_generator::orm_object_configuration_generator() : position_(0) { }

void orm_object_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.generate_mapping(create_bool(position + 0));
    v.schema_name(create_std_string(position + 1));
    v.table_name(create_std_string(position + 2));
    v.is_value(create_bool(position + 3));
    v.has_primary_key(create_bool(position + 4));
    v.letter_case(create_boost_optional_dogen_yarn_letter_cases(position + 5));
}

orm_object_configuration_generator::result_type
orm_object_configuration_generator::create(const unsigned int position) {
    orm_object_configuration r;
    orm_object_configuration_generator::populate(position, r);
    return r;
}

orm_object_configuration_generator::result_type*
orm_object_configuration_generator::create_ptr(const unsigned int position) {
    orm_object_configuration* p = new orm_object_configuration();
    orm_object_configuration_generator::populate(position, *p);
    return p;
}

orm_object_configuration_generator::result_type
orm_object_configuration_generator::operator()() {
    return create(position_++);
}

} }
