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
#include "dogen/upsilon/test_data/type_td.hpp"
#include "dogen/upsilon/test_data/field_td.hpp"
#include "dogen/upsilon/test_data/compound_td.hpp"

namespace {

dogen::upsilon::field
create_dogen_upsilon_field(const unsigned int position) {
    return dogen::upsilon::field_generator::create(position);
}

std::list<dogen::upsilon::field> create_std_list_dogen_upsilon_field(unsigned int position) {
    std::list<dogen::upsilon::field> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_upsilon_field(position + i));
    }
    return r;
}

}

namespace dogen {
namespace upsilon {

compound_generator::compound_generator() : position_(0) { }

void compound_generator::
populate(const unsigned int position, result_type& v) {
    dogen::upsilon::type_generator::populate(position, v);
    v.fields(create_std_list_dogen_upsilon_field(position + 0));
}

compound_generator::result_type
compound_generator::create(const unsigned int position) {
    compound r;
    compound_generator::populate(position, r);
    return r;
}

compound_generator::result_type*
compound_generator::create_ptr(const unsigned int position) {
    compound* p = new compound();
    compound_generator::populate(position, *p);
    return p;
}

compound_generator::result_type
compound_generator::operator()() {
    return create(position_++);
}

} }
