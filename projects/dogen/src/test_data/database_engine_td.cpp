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
#include "dogen/test_data/database_engine_td.hpp"

namespace dogen {

database_engine_generator::database_engine_generator() : position_(0) { }
void database_engine_generator::
populate(const unsigned int position, result_type& v) {
    v = static_cast<database_engine>(position % 3);
}

database_engine_generator::result_type
database_engine_generator::create(const unsigned int  position) {
    result_type r;
    database_engine_generator::populate(position, r);
    return r;
}

database_engine_generator::result_type
database_engine_generator::operator()() {
    return create(position_++);
}

}
