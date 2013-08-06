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
#include "dogen/cpp/test_data/class_info_td.hpp"
#include "dogen/cpp/test_data/enum_info_td.hpp"
#include "dogen/cpp/test_data/exception_info_td.hpp"
#include "dogen/cpp/test_data/namespace_info_td.hpp"
#include "dogen/cpp/test_data/registrar_info_td.hpp"
#include "dogen/cpp/test_data/string_table_info_td.hpp"
#include "dogen/cpp/test_data/visitor_info_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml_to_cpp/test_data/context_td.hpp"
#include "dogen/sml_to_cpp/test_data/relationships_td.hpp"

namespace {

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

dogen::cpp::class_info
create_dogen_cpp_class_info(const unsigned int position) {
    return dogen::cpp::class_info_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::cpp::class_info> create_std_unordered_map_dogen_sml_qname_dogen_cpp_class_info(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::cpp::class_info> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_cpp_class_info(position + i)));
    }
    return r;
}

dogen::sml_to_cpp::relationships
create_dogen_sml_to_cpp_relationships(const unsigned int position) {
    return dogen::sml_to_cpp::relationships_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml_to_cpp::relationships> create_std_unordered_map_dogen_sml_qname_dogen_sml_to_cpp_relationships(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml_to_cpp::relationships> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_to_cpp_relationships(position + i)));
    }
    return r;
}

dogen::cpp::exception_info
create_dogen_cpp_exception_info(const unsigned int position) {
    return dogen::cpp::exception_info_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::cpp::exception_info> create_std_unordered_map_dogen_sml_qname_dogen_cpp_exception_info(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::cpp::exception_info> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_cpp_exception_info(position + i)));
    }
    return r;
}

dogen::cpp::enum_info
create_dogen_cpp_enum_info(const unsigned int position) {
    return dogen::cpp::enum_info_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::cpp::enum_info> create_std_unordered_map_dogen_sml_qname_dogen_cpp_enum_info(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::cpp::enum_info> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_cpp_enum_info(position + i)));
    }
    return r;
}

dogen::cpp::registrar_info
create_dogen_cpp_registrar_info(const unsigned int position) {
    return dogen::cpp::registrar_info_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::cpp::registrar_info> create_std_unordered_map_dogen_sml_qname_dogen_cpp_registrar_info(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::cpp::registrar_info> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_cpp_registrar_info(position + i)));
    }
    return r;
}

dogen::cpp::namespace_info
create_dogen_cpp_namespace_info(const unsigned int position) {
    return dogen::cpp::namespace_info_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::cpp::namespace_info> create_std_unordered_map_dogen_sml_qname_dogen_cpp_namespace_info(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::cpp::namespace_info> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_cpp_namespace_info(position + i)));
    }
    return r;
}

dogen::cpp::visitor_info
create_dogen_cpp_visitor_info(const unsigned int position) {
    return dogen::cpp::visitor_info_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::cpp::visitor_info> create_std_unordered_map_dogen_sml_qname_dogen_cpp_visitor_info(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::cpp::visitor_info> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_cpp_visitor_info(position + i)));
    }
    return r;
}

dogen::cpp::string_table_info
create_dogen_cpp_string_table_info(const unsigned int position) {
    return dogen::cpp::string_table_info_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::cpp::string_table_info> create_std_unordered_map_dogen_sml_qname_dogen_cpp_string_table_info(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::cpp::string_table_info> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_cpp_string_table_info(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace sml_to_cpp {

context_generator::context_generator() : position_(0) { }

void context_generator::
populate(const unsigned int position, result_type& v) {
    v.classes(create_std_unordered_map_dogen_sml_qname_dogen_cpp_class_info(position + 0));
    v.relationships(create_std_unordered_map_dogen_sml_qname_dogen_sml_to_cpp_relationships(position + 1));
    v.exceptions(create_std_unordered_map_dogen_sml_qname_dogen_cpp_exception_info(position + 2));
    v.enumerations(create_std_unordered_map_dogen_sml_qname_dogen_cpp_enum_info(position + 3));
    v.registrars(create_std_unordered_map_dogen_sml_qname_dogen_cpp_registrar_info(position + 4));
    v.namespaces(create_std_unordered_map_dogen_sml_qname_dogen_cpp_namespace_info(position + 5));
    v.visitors(create_std_unordered_map_dogen_sml_qname_dogen_cpp_visitor_info(position + 6));
    v.string_tables(create_std_unordered_map_dogen_sml_qname_dogen_cpp_string_table_info(position + 7));
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
