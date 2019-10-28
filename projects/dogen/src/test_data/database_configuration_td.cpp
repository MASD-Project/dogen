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
#include "dogen/test_data/relational_database_td.hpp"
#include "dogen/test_data/database_configuration_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

dogen::relational_database
create_dogen_relational_database(const unsigned int position) {
    return dogen::relational_database_generator::create(position);
}

}

namespace dogen {

database_configuration_generator::database_configuration_generator() : position_(0) { }

void database_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.host(create_std_string(position + 0));
    v.port(create_unsigned_int(position + 1));
    v.name(create_std_string(position + 2));
    v.user(create_std_string(position + 3));
    v.password(create_std_string(position + 4));
    v.relational_database(create_dogen_relational_database(position + 5));
}

database_configuration_generator::result_type
database_configuration_generator::create(const unsigned int position) {
    database_configuration r;
    database_configuration_generator::populate(position, r);
    return r;
}

database_configuration_generator::result_type*
database_configuration_generator::create_ptr(const unsigned int position) {
    database_configuration* p = new database_configuration();
    database_configuration_generator::populate(position, *p);
    return p;
}

database_configuration_generator::result_type
database_configuration_generator::operator()() {
    return create(position_++);
}

}
