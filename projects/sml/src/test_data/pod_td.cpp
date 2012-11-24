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
#include "dogen/sml/test_data/category_types_td.hpp"
#include "dogen/sml/test_data/generation_types_td.hpp"
#include "dogen/sml/test_data/pod_td.hpp"
#include "dogen/sml/test_data/pod_types_td.hpp"
#include "dogen/sml/test_data/property_td.hpp"
#include "dogen/sml/test_data/qualified_name_td.hpp"

namespace {

dogen::sml::qualified_name
create_dogen_sml_qualified_name(const unsigned int position) {
    return dogen::sml::qualified_name_generator::create(position);
}

dogen::sml::property
create_dogen_sml_property(const unsigned int position) {
    return dogen::sml::property_generator::create(position);
}

std::vector<dogen::sml::property> create_std_vector_dogen_sml_property(unsigned int position) {
    std::vector<dogen::sml::property> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_sml_property(position + i));
    }
    return r;
}

boost::optional<dogen::sml::qualified_name>
create_boost_optional_dogen_sml_qualified_name(unsigned int position) {
    boost::optional<dogen::sml::qualified_name> r(        create_dogen_sml_qualified_name(position));
    return r;
}

std::list<dogen::sml::qualified_name> create_std_list_dogen_sml_qualified_name(unsigned int position) {
    std::list<dogen::sml::qualified_name> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_sml_qualified_name(position + i));
    }
    return r;
}

dogen::sml::generation_types
create_dogen_sml_generation_types(const unsigned int position) {
    return dogen::sml::generation_types_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::sml::category_types
create_dogen_sml_category_types(const unsigned int position) {
    return dogen::sml::category_types_generator::create(position);
}

dogen::sml::pod_types
create_dogen_sml_pod_types(const unsigned int position) {
    return dogen::sml::pod_types_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

}

namespace dogen {
namespace sml {

pod_generator::pod_generator() : position_(0) { }

void pod_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_sml_qualified_name(position + 0));
    v.properties(create_std_vector_dogen_sml_property(position + 1));
    v.parent_name(create_boost_optional_dogen_sml_qualified_name(position + 2));
    v.original_parent_name(create_boost_optional_dogen_sml_qualified_name(position + 3));
    v.leaves(create_std_list_dogen_sml_qualified_name(position + 4));
    v.generation_type(create_dogen_sml_generation_types(position + 5));
    v.is_parent(create_bool(position + 6));
    v.category_type(create_dogen_sml_category_types(position + 7));
    v.pod_type(create_dogen_sml_pod_types(position + 8));
    v.documentation(create_std_string(position + 9));
    v.number_of_type_arguments(create_unsigned_int(position + 10));
}

pod_generator::result_type
pod_generator::create(const unsigned int position) {
    pod r;
    pod_generator::populate(position, r);
    return r;
}
pod_generator::result_type*
pod_generator::create_ptr(const unsigned int position) {
    pod* p = new pod();
    pod_generator::populate(position, *p);
    return p;
}

pod_generator::result_type
pod_generator::operator()() {
    return create(position_++);
}

} }
