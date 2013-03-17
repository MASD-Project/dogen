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
#include "dogen/database/test_data/foreign_key_td.hpp"
#include "dogen/database/test_data/primary_key_2_td.hpp"

namespace {

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

dogen::database::primary_key_2*
create_dogen_database_primary_key_2_ptr(const unsigned int position) {
    return dogen::database::primary_key_2_generator::create_ptr(position);
}

boost::shared_ptr<dogen::database::primary_key_2>
create_boost_shared_ptr_dogen_database_primary_key_2(unsigned int position) {
    boost::shared_ptr<dogen::database::primary_key_2> r(
        create_dogen_database_primary_key_2_ptr(position));
    return r;
}

}

namespace dogen {
namespace database {

foreign_key_generator::foreign_key_generator() : position_(0) { }

void foreign_key_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_unsigned_int(position + 0));
    v.prop_1(create_boost_shared_ptr_dogen_database_primary_key_2(position + 1));
}

foreign_key_generator::result_type
foreign_key_generator::create(const unsigned int position) {
    foreign_key r;
    foreign_key_generator::populate(position, r);
    return r;
}
foreign_key_generator::result_type*
foreign_key_generator::create_ptr(const unsigned int position) {
    foreign_key* p = new foreign_key();
    foreign_key_generator::populate(position, *p);
    return p;
}

foreign_key_generator::result_type
foreign_key_generator::operator()() {
    return create(position_++);
}

} }
