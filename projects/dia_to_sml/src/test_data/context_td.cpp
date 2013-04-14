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
#include "dogen/dia_to_sml/test_data/context_td.hpp"
#include "dogen/sml/test_data/enumeration_td.hpp"
#include "dogen/sml/test_data/exception_td.hpp"
#include "dogen/sml/test_data/package_td.hpp"
#include "dogen/sml/test_data/pod_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"

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

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

std::unordered_set<std::string> create_std_unordered_set_std_string(unsigned int position) {
    std::unordered_set<std::string> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

dogen::sml::package
create_dogen_sml_package(const unsigned int position) {
    return dogen::sml::package_generator::create(position);
}

std::unordered_map<std::string, dogen::sml::package> create_std_unordered_map_std_string_dogen_sml_package(unsigned int position) {
    std::unordered_map<std::string, dogen::sml::package> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_sml_package(position + i)));
    }
    return r;
}

std::unordered_map<std::string, dogen::sml::qname> create_std_unordered_map_std_string_dogen_sml_qname(unsigned int position) {
    std::unordered_map<std::string, dogen::sml::qname> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_sml_qname(position + i)));
    }
    return r;
}

std::unordered_map<dogen::sml::qname, dogen::sml::qname> create_std_unordered_map_dogen_sml_qname_dogen_sml_qname(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::qname> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_qname(position + i)));
    }
    return r;
}

std::list<dogen::sml::qname> create_std_list_dogen_sml_qname(unsigned int position) {
    std::list<dogen::sml::qname> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_sml_qname(position + i));
    }
    return r;
}

std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> > create_std_unordered_map_dogen_sml_qname_std_list_dogen_sml_qname_(unsigned int position) {
    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::qname> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_std_list_dogen_sml_qname(position + i)));
    }
    return r;
}

dogen::sml::enumeration
create_dogen_sml_enumeration(const unsigned int position) {
    return dogen::sml::enumeration_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::enumeration> create_std_unordered_map_dogen_sml_qname_dogen_sml_enumeration(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::enumeration> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_enumeration(position + i)));
    }
    return r;
}

std::unordered_map<dogen::sml::qname, dogen::sml::package> create_std_unordered_map_dogen_sml_qname_dogen_sml_package(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::package> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_package(position + i)));
    }
    return r;
}

dogen::sml::exception
create_dogen_sml_exception(const unsigned int position) {
    return dogen::sml::exception_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::exception> create_std_unordered_map_dogen_sml_qname_dogen_sml_exception(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::exception> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_exception(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace dia_to_sml {

context_generator::context_generator() : position_(0) { }

void context_generator::
populate(const unsigned int position, result_type& v) {
    v.model_name(create_std_string(position + 0));
    v.pods(create_std_unordered_map_dogen_sml_qname_dogen_sml_pod(position + 1));
    v.external_package_path(create_std_list_std_string(position + 2));
    v.verbose(create_bool(position + 3));
    v.is_target(create_bool(position + 4));
    v.child_to_parent(create_std_unordered_map_std_string_std_string(position + 5));
    v.parent_ids(create_std_unordered_set_std_string(position + 6));
    v.packages_by_id(create_std_unordered_map_std_string_dogen_sml_package(position + 7));
    v.dia_id_to_qname(create_std_unordered_map_std_string_dogen_sml_qname(position + 8));
    v.original_parent(create_std_unordered_map_dogen_sml_qname_dogen_sml_qname(position + 9));
    v.leaves(create_std_unordered_map_dogen_sml_qname_std_list_dogen_sml_qname_(position + 10));
    v.dependencies(create_std_unordered_set_std_string(position + 11));
    v.top_level_package_names(create_std_unordered_set_std_string(position + 12));
    v.enumerations(create_std_unordered_map_dogen_sml_qname_dogen_sml_enumeration(position + 13));
    v.packages(create_std_unordered_map_dogen_sml_qname_dogen_sml_package(position + 14));
    v.exceptions(create_std_unordered_map_dogen_sml_qname_dogen_sml_exception(position + 15));
}

context_generator::result_type
context_generator::create(const unsigned int position) {
    context r;
    context_generator::populate(position, r);
    return r;
}
context_generator::result_type*
context_generator::create_ptr(const unsigned int position) {
    context* p = new context();
    context_generator::populate(position, *p);
    return p;
}

context_generator::result_type
context_generator::operator()() {
    return create(position_++);
}

} }
