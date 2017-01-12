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
#include "dogen/upsilon/test_data/output_td.hpp"
#include "dogen/upsilon/test_data/representation_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::upsilon::representation
create_dogen_upsilon_representation(const unsigned int position) {
    return dogen::upsilon::representation_generator::create(position);
}

std::vector<dogen::upsilon::representation> create_std_vector_dogen_upsilon_representation(unsigned int position) {
    std::vector<dogen::upsilon::representation> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_upsilon_representation(position + i));
    }
    return r;
}

}

namespace dogen {
namespace upsilon {

output_generator::output_generator() : position_(0) { }

void output_generator::
populate(const unsigned int position, result_type& v) {
    v.schema_name(create_std_string(position + 0));
    v.representations(create_std_vector_dogen_upsilon_representation(position + 1));
}

output_generator::result_type
output_generator::create(const unsigned int position) {
    output r;
    output_generator::populate(position, r);
    return r;
}

output_generator::result_type*
output_generator::create_ptr(const unsigned int position) {
    output* p = new output();
    output_generator::populate(position, *p);
    return p;
}

output_generator::result_type
output_generator::operator()() {
    return create(position_++);
}

} }
