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
#include <sstream>
#include "dogen/config/test_data/sql_settings_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace config {

sql_settings_generator::sql_settings_generator() : position_(0) { }

void sql_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.verbose(create_bool(position + 0));
    v.disable_backend(create_bool(position + 1));
    v.create_schema(create_bool(position + 2));
    v.schema_name(create_std_string(position + 3));
}

sql_settings_generator::result_type
sql_settings_generator::create(const unsigned int position) {
    sql_settings r;
    sql_settings_generator::populate(position, r);
    return r;
}
sql_settings_generator::result_type*
sql_settings_generator::create_ptr(const unsigned int position) {
    sql_settings* p = new sql_settings();
    sql_settings_generator::populate(position, *p);
    return p;
}

sql_settings_generator::result_type
sql_settings_generator::operator()() {
    return create(position_++);
}

} }
