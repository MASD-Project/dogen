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
#include "dogen/sml/test_data/concept_td.hpp"
#include "dogen/sml/test_data/model_td.hpp"
#include "dogen/sml/test_data/module_td.hpp"
#include "dogen/sml/test_data/pod_td.hpp"
#include "dogen/sml/test_data/primitive_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/reference_td.hpp"
#include "dogen/sml/test_data/service_td.hpp"
#include "dogen/sml/test_data/value_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

dogen::sml::pod
create_dogen_sml_pod(const unsigned int position) {
    return dogen::sml::pod_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::pod> create_std_unordered_map_dogen_sml_qname_dogen_sml_pod(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::pod> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_pod(position + i)));
    }
    return r;
}

dogen::sml::primitive
create_dogen_sml_primitive(const unsigned int position) {
    return dogen::sml::primitive_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::primitive> create_std_unordered_map_dogen_sml_qname_dogen_sml_primitive(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::primitive> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_primitive(position + i)));
    }
    return r;
}

dogen::sml::value
create_dogen_sml_value(const unsigned int position) {
    return dogen::sml::value_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::value> create_std_unordered_map_dogen_sml_qname_dogen_sml_value(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::value> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_value(position + i)));
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

std::unordered_set<dogen::sml::qname> create_std_unordered_set_dogen_sml_qname(unsigned int position) {
    std::unordered_set<dogen::sml::qname> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(create_dogen_sml_qname(position + i));
    }
    return r;
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::vector<std::pair<std::string, std::string> > create_std_vector_std_pair_std_string_std_string_(unsigned int position) {
    std::vector<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
    }
    return r;
}

dogen::sml::service
create_dogen_sml_service(const unsigned int position) {
    return dogen::sml::service_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::service> create_std_unordered_map_dogen_sml_qname_dogen_sml_service(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::service> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_service(position + i)));
    }
    return r;
}

dogen::sml::module
create_dogen_sml_module(const unsigned int position) {
    return dogen::sml::module_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::module> create_std_unordered_map_dogen_sml_qname_dogen_sml_module(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::module> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_module(position + i)));
    }
    return r;
}

dogen::sml::concept
create_dogen_sml_concept(const unsigned int position) {
    return dogen::sml::concept_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::concept> create_std_unordered_map_dogen_sml_qname_dogen_sml_concept(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::concept> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_concept(position + i)));
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
    v.pods(create_std_unordered_map_dogen_sml_qname_dogen_sml_pod(position + 1));
    v.primitives(create_std_unordered_map_dogen_sml_qname_dogen_sml_primitive(position + 2));
    v.enumerations(create_std_unordered_map_dogen_sml_qname_dogen_sml_value(position + 3));
    v.exceptions(create_std_unordered_map_dogen_sml_qname_dogen_sml_value(position + 4));
    v.external_module_path(create_std_list_std_string(position + 5));
    v.is_system(create_bool(position + 6));
    v.dependencies(create_std_unordered_map_std_string_dogen_sml_reference(position + 7));
    v.leaves(create_std_unordered_set_dogen_sml_qname(position + 8));
    v.documentation(create_std_string(position + 9));
    v.implementation_specific_parameters(create_std_vector_std_pair_std_string_std_string_(position + 10));
    v.services(create_std_unordered_map_dogen_sml_qname_dogen_sml_service(position + 11));
    v.modules(create_std_unordered_map_dogen_sml_qname_dogen_sml_module(position + 12));
    v.concepts(create_std_unordered_map_dogen_sml_qname_dogen_sml_concept(position + 13));
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
