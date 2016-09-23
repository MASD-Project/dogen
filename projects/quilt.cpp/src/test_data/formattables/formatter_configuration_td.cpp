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
#include "dogen/quilt.cpp/test_data/formattables/formatter_configuration_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::optional<std::string>
create_boost_optional_std_string(unsigned int position) {
    boost::optional<std::string> r(
        create_std_string(position));
    return r;
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

std::unordered_set<std::string> create_std_unordered_set_std_string(unsigned int position) {
    std::unordered_set<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

formatter_configuration_generator::formatter_configuration_generator() : position_(0) { }

void formatter_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.enabled(create_bool(position + 0));
    v.file_path(create_boost_filesystem_path(position + 1));
    v.header_guard(create_boost_optional_std_string(position + 2));
    v.inclusion_dependencies(create_std_list_std_string(position + 3));
    v.enabled_formatters(create_std_unordered_set_std_string(position + 4));
    v.facet_directory_for_facet(create_std_unordered_map_std_string_std_string(position + 5));
}

formatter_configuration_generator::result_type
formatter_configuration_generator::create(const unsigned int position) {
    formatter_configuration r;
    formatter_configuration_generator::populate(position, r);
    return r;
}

formatter_configuration_generator::result_type*
formatter_configuration_generator::create_ptr(const unsigned int position) {
    formatter_configuration* p = new formatter_configuration();
    formatter_configuration_generator::populate(position, *p);
    return p;
}

formatter_configuration_generator::result_type
formatter_configuration_generator::operator()() {
    return create(position_++);
}

} } } }
