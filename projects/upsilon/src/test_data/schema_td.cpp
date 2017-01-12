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
#include "dogen/upsilon/test_data/tag_td.hpp"
#include "dogen/upsilon/test_data/type_td.hpp"
#include "dogen/upsilon/test_data/schema_td.hpp"
#include "dogen/upsilon/test_data/dependency_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::upsilon::dependency
create_dogen_upsilon_dependency(const unsigned int position) {
    return dogen::upsilon::dependency_generator::create(position);
}

std::vector<dogen::upsilon::dependency> create_std_vector_dogen_upsilon_dependency(unsigned int position) {
    std::vector<dogen::upsilon::dependency> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_upsilon_dependency(position + i));
    }
    return r;
}

dogen::upsilon::tag
create_dogen_upsilon_tag(const unsigned int position) {
    return dogen::upsilon::tag_generator::create(position);
}

std::vector<dogen::upsilon::tag> create_std_vector_dogen_upsilon_tag(unsigned int position) {
    std::vector<dogen::upsilon::tag> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_upsilon_tag(position + i));
    }
    return r;
}

dogen::upsilon::type*
create_dogen_upsilon_type_ptr(const unsigned int position) {
    return dogen::upsilon::type_generator::create_ptr(position);
}

boost::shared_ptr<dogen::upsilon::type>
create_boost_shared_ptr_dogen_upsilon_type(unsigned int position) {
    boost::shared_ptr<dogen::upsilon::type> r(
        create_dogen_upsilon_type_ptr(position));
    return r;
}

std::vector<boost::shared_ptr<dogen::upsilon::type> > create_std_vector_boost_shared_ptr_dogen_upsilon_type(unsigned int position) {
    std::vector<boost::shared_ptr<dogen::upsilon::type> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_upsilon_type(position + i));
    }
    return r;
}

}

namespace dogen {
namespace upsilon {

schema_generator::schema_generator() : position_(0) { }

void schema_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.id_min(create_std_string(position + 1));
    v.id_max(create_std_string(position + 2));
    v.base_guid(create_std_string(position + 3));
    v.dependencies(create_std_vector_dogen_upsilon_dependency(position + 4));
    v.tags(create_std_vector_dogen_upsilon_tag(position + 5));
    v.types(create_std_vector_boost_shared_ptr_dogen_upsilon_type(position + 6));
}

schema_generator::result_type
schema_generator::create(const unsigned int position) {
    schema r;
    schema_generator::populate(position, r);
    return r;
}

schema_generator::result_type*
schema_generator::create_ptr(const unsigned int position) {
    schema* p = new schema();
    schema_generator::populate(position, *p);
    return p;
}

schema_generator::result_type
schema_generator::operator()() {
    return create(position_++);
}

} }
