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
#include "dogen/upsilon/test_data/config_td.hpp"
#include "dogen/upsilon/test_data/output_td.hpp"
#include "dogen/upsilon/test_data/directory_td.hpp"
#include "dogen/upsilon/test_data/schema_ref_td.hpp"

namespace {

dogen::upsilon::directory
create_dogen_upsilon_directory(const unsigned int position) {
    return dogen::upsilon::directory_generator::create(position);
}

dogen::upsilon::schema_ref
create_dogen_upsilon_schema_ref(const unsigned int position) {
    return dogen::upsilon::schema_ref_generator::create(position);
}

std::vector<dogen::upsilon::schema_ref> create_std_vector_dogen_upsilon_schema_ref(unsigned int position) {
    std::vector<dogen::upsilon::schema_ref> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_upsilon_schema_ref(position + i));
    }
    return r;
}

dogen::upsilon::output
create_dogen_upsilon_output(const unsigned int position) {
    return dogen::upsilon::output_generator::create(position);
}

std::vector<dogen::upsilon::output> create_std_vector_dogen_upsilon_output(unsigned int position) {
    std::vector<dogen::upsilon::output> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_upsilon_output(position + i));
    }
    return r;
}

}

namespace dogen {
namespace upsilon {

config_generator::config_generator() : position_(0) { }

void config_generator::
populate(const unsigned int position, result_type& v) {
    v.directory(create_dogen_upsilon_directory(position + 0));
    v.schema_refs(create_std_vector_dogen_upsilon_schema_ref(position + 1));
    v.outputs(create_std_vector_dogen_upsilon_output(position + 2));
}

config_generator::result_type
config_generator::create(const unsigned int position) {
    config r;
    config_generator::populate(position, r);
    return r;
}

config_generator::result_type*
config_generator::create_ptr(const unsigned int position) {
    config* p = new config();
    config_generator::populate(position, *p);
    return p;
}

config_generator::result_type
config_generator::operator()() {
    return create(position_++);
}

} }
