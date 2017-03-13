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
#include "dogen/test_models/northwind/test_data/region_id_td.hpp"
#include "dogen/test_models/northwind/test_data/territory_td.hpp"
#include "dogen/test_models/northwind/test_data/territory_id_td.hpp"

namespace {

dogen::test_models::northwind::territory_id
create_dogen_test_models_northwind_territory_id(const unsigned int position) {
    return dogen::test_models::northwind::territory_id_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::test_models::northwind::region_id
create_dogen_test_models_northwind_region_id(const unsigned int position) {
    return dogen::test_models::northwind::region_id_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace northwind {

territory_generator::territory_generator() : position_(0) { }

void territory_generator::
populate(const unsigned int position, result_type& v) {
    v.territory_id(create_dogen_test_models_northwind_territory_id(position + 0));
    v.territory_description(create_std_string(position + 1));
    v.region_id(create_dogen_test_models_northwind_region_id(position + 2));
}

territory_generator::result_type
territory_generator::create(const unsigned int position) {
    territory r;
    territory_generator::populate(position, r);
    return r;
}

territory_generator::result_type*
territory_generator::create_ptr(const unsigned int position) {
    territory* p = new territory();
    territory_generator::populate(position, *p);
    return p;
}

territory_generator::result_type
territory_generator::operator()() {
    return create(position_++);
}

} } }
