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
#include "dogen/cpp/test_data/class_info_td.hpp"
#include "dogen/cpp/test_data/content_descriptor_td.hpp"
#include "dogen/cpp/test_data/enum_info_td.hpp"
#include "dogen/cpp/test_data/exception_info_td.hpp"
#include "dogen/cpp/test_data/file_info_td.hpp"
#include "dogen/cpp/test_data/namespace_info_td.hpp"
#include "dogen/cpp/test_data/registrar_info_td.hpp"
#include "dogen/cpp/test_data/visitor_info_td.hpp"

namespace {

dogen::cpp::content_descriptor
create_dogen_cpp_content_descriptor(const unsigned int position) {
    return dogen::cpp::content_descriptor_generator::create(position);
}

dogen::cpp::class_info
create_dogen_cpp_class_info(const unsigned int position) {
    return dogen::cpp::class_info_generator::create(position);
}

boost::optional<dogen::cpp::class_info>
create_boost_optional_dogen_cpp_class_info(unsigned int position) {
    boost::optional<dogen::cpp::class_info> r(
        create_dogen_cpp_class_info(position));
    return r;
}

dogen::cpp::enum_info
create_dogen_cpp_enum_info(const unsigned int position) {
    return dogen::cpp::enum_info_generator::create(position);
}

boost::optional<dogen::cpp::enum_info>
create_boost_optional_dogen_cpp_enum_info(unsigned int position) {
    boost::optional<dogen::cpp::enum_info> r(
        create_dogen_cpp_enum_info(position));
    return r;
}

dogen::cpp::exception_info
create_dogen_cpp_exception_info(const unsigned int position) {
    return dogen::cpp::exception_info_generator::create(position);
}

boost::optional<dogen::cpp::exception_info>
create_boost_optional_dogen_cpp_exception_info(unsigned int position) {
    boost::optional<dogen::cpp::exception_info> r(
        create_dogen_cpp_exception_info(position));
    return r;
}

dogen::cpp::registrar_info
create_dogen_cpp_registrar_info(const unsigned int position) {
    return dogen::cpp::registrar_info_generator::create(position);
}

boost::optional<dogen::cpp::registrar_info>
create_boost_optional_dogen_cpp_registrar_info(unsigned int position) {
    boost::optional<dogen::cpp::registrar_info> r(
        create_dogen_cpp_registrar_info(position));
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::cpp::namespace_info
create_dogen_cpp_namespace_info(const unsigned int position) {
    return dogen::cpp::namespace_info_generator::create(position);
}

boost::optional<dogen::cpp::namespace_info>
create_boost_optional_dogen_cpp_namespace_info(unsigned int position) {
    boost::optional<dogen::cpp::namespace_info> r(
        create_dogen_cpp_namespace_info(position));
    return r;
}

dogen::cpp::visitor_info
create_dogen_cpp_visitor_info(const unsigned int position) {
    return dogen::cpp::visitor_info_generator::create(position);
}

boost::optional<dogen::cpp::visitor_info>
create_boost_optional_dogen_cpp_visitor_info(unsigned int position) {
    boost::optional<dogen::cpp::visitor_info> r(
        create_dogen_cpp_visitor_info(position));
    return r;
}

}

namespace dogen {
namespace cpp {

file_info_generator::file_info_generator() : position_(0) { }

void file_info_generator::
populate(const unsigned int position, result_type& v) {
    v.descriptor(create_dogen_cpp_content_descriptor(position + 0));
    v.class_info(create_boost_optional_dogen_cpp_class_info(position + 1));
    v.enum_info(create_boost_optional_dogen_cpp_enum_info(position + 2));
    v.exception_info(create_boost_optional_dogen_cpp_exception_info(position + 3));
    v.registrar_info(create_boost_optional_dogen_cpp_registrar_info(position + 4));
    v.header_guard(create_std_string(position + 5));
    v.system_includes(create_std_list_std_string(position + 6));
    v.user_includes(create_std_list_std_string(position + 7));
    v.file_path(create_boost_filesystem_path(position + 8));
    v.namespace_info(create_boost_optional_dogen_cpp_namespace_info(position + 9));
    v.visitor_info(create_boost_optional_dogen_cpp_visitor_info(position + 10));
    v.relative_path(create_boost_filesystem_path(position + 11));
}

file_info_generator::result_type
file_info_generator::create(const unsigned int position) {
    file_info r;
    file_info_generator::populate(position, r);
    return r;
}
file_info_generator::result_type*
file_info_generator::create_ptr(const unsigned int position) {
    file_info* p = new file_info();
    file_info_generator::populate(position, *p);
    return p;
}

file_info_generator::result_type
file_info_generator::operator()() {
    return create(position_++);
}

} }
