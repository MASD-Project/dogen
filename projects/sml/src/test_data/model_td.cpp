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
#include "dogen/sml/test_data/enumeration_td.hpp"
#include "dogen/sml/test_data/exception_td.hpp"
#include "dogen/sml/test_data/model_td.hpp"
#include "dogen/sml/test_data/package_td.hpp"
#include "dogen/sml/test_data/pod_td.hpp"
#include "dogen/sml/test_data/primitive_td.hpp"
#include "dogen/sml/test_data/qualified_name_td.hpp"
#include "dogen/sml/test_data/reference_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::sml::qualified_name
create_dogen_sml_qualified_name(const unsigned int position) {
    return dogen::sml::qualified_name_generator::create(position);
}

dogen::sml::package
create_dogen_sml_package(const unsigned int position) {
    return dogen::sml::package_generator::create(position);
}

std::unordered_map<dogen::sml::qualified_name, dogen::sml::package> create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_package(unsigned int position) {
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::package> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qualified_name(position + i), create_dogen_sml_package(position + i)));
    }
    return r;
}

dogen::sml::pod
create_dogen_sml_pod(const unsigned int position) {
    return dogen::sml::pod_generator::create(position);
}

std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_pod(unsigned int position) {
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qualified_name(position + i), create_dogen_sml_pod(position + i)));
    }
    return r;
}

dogen::sml::primitive
create_dogen_sml_primitive(const unsigned int position) {
    return dogen::sml::primitive_generator::create(position);
}

std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive> create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_primitive(unsigned int position) {
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qualified_name(position + i), create_dogen_sml_primitive(position + i)));
    }
    return r;
}

dogen::sml::enumeration
create_dogen_sml_enumeration(const unsigned int position) {
    return dogen::sml::enumeration_generator::create(position);
}

std::unordered_map<dogen::sml::qualified_name, dogen::sml::enumeration> create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_enumeration(unsigned int position) {
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::enumeration> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qualified_name(position + i), create_dogen_sml_enumeration(position + i)));
    }
    return r;
}

dogen::sml::exception
create_dogen_sml_exception(const unsigned int position) {
    return dogen::sml::exception_generator::create(position);
}

std::unordered_map<dogen::sml::qualified_name, dogen::sml::exception> create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_exception(unsigned int position) {
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::exception> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qualified_name(position + i), create_dogen_sml_exception(position + i)));
    }
    return r;
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::sml::reference
create_dogen_sml_reference(const unsigned int position) {
    return dogen::sml::reference_generator::create(position);
}

std::unordered_map<std::string, dogen::sml::reference> create_std_unordered_map_std_string_dogen_sml_reference(unsigned int position) {
    std::unordered_map<std::string, dogen::sml::reference> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_sml_reference(position + i)));
    }
    return r;
}

std::unordered_set<dogen::sml::qualified_name> create_std_unordered_set_dogen_sml_qualified_name(unsigned int position) {
    std::unordered_set<dogen::sml::qualified_name> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(create_dogen_sml_qualified_name(position + i));
    }
    return r;
}

}

namespace dogen {
namespace sml {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.packages(create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_package(position + 1));
    v.pods(create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_pod(position + 2));
    v.primitives(create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_primitive(position + 3));
    v.enumerations(create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_enumeration(position + 4));
    v.exceptions(create_std_unordered_map_dogen_sml_qualified_name_dogen_sml_exception(position + 5));
    v.external_package_path(create_std_list_std_string(position + 6));
    v.schema_name(create_std_string(position + 7));
    v.is_system(create_bool(position + 8));
    v.dependencies(create_std_unordered_map_std_string_dogen_sml_reference(position + 9));
    v.leaves(create_std_unordered_set_dogen_sml_qualified_name(position + 10));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}
model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

} }
