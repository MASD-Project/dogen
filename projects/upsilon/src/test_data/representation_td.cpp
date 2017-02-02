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
#include "dogen/upsilon/test_data/exclusion_td.hpp"
#include "dogen/upsilon/test_data/target_types_td.hpp"
#include "dogen/upsilon/test_data/representation_td.hpp"

namespace {

dogen::upsilon::target_types
create_dogen_upsilon_target_types(const unsigned int position) {
    return dogen::upsilon::target_types_generator::create(position);
}

bool create_bool(const unsigned int position) {
    if (position == 0)
        return true;
    else if (position == 1)
        return false;
    else
        return (position % 2) == 0;
}

dogen::upsilon::exclusion
create_dogen_upsilon_exclusion(const unsigned int position) {
    return dogen::upsilon::exclusion_generator::create(position);
}

std::vector<dogen::upsilon::exclusion> create_std_vector_dogen_upsilon_exclusion(unsigned int position) {
    std::vector<dogen::upsilon::exclusion> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_upsilon_exclusion(position + i));
    }
    return r;
}

}

namespace dogen {
namespace upsilon {

representation_generator::representation_generator() : position_(0) { }

void representation_generator::
populate(const unsigned int position, result_type& v) {
    v.target(create_dogen_upsilon_target_types(position + 0));
    v.pof(create_bool(position + 1));
    v.exclusions(create_std_vector_dogen_upsilon_exclusion(position + 2));
}

representation_generator::result_type
representation_generator::create(const unsigned int position) {
    representation r;
    representation_generator::populate(position, r);
    return r;
}

representation_generator::result_type*
representation_generator::create_ptr(const unsigned int position) {
    representation* p = new representation();
    representation_generator::populate(position, *p);
    return p;
}

representation_generator::result_type
representation_generator::operator()() {
    return create(position_++);
}

} }
