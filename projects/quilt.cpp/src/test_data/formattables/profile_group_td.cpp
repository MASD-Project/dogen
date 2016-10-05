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
#include "dogen/quilt.cpp/test_data/formattables/facet_profile_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/profile_group_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/profile_types_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/formatter_profile_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/decoration_profile_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

dogen::quilt::cpp::formattables::profile_types
create_dogen_quilt_cpp_formattables_profile_types(const unsigned int position) {
    return dogen::quilt::cpp::formattables::profile_types_generator::create(position);
}

dogen::quilt::cpp::formattables::decoration_profile
create_dogen_quilt_cpp_formattables_decoration_profile(const unsigned int position) {
    return dogen::quilt::cpp::formattables::decoration_profile_generator::create(position);
}

boost::optional<dogen::quilt::cpp::formattables::decoration_profile>
create_boost_optional_dogen_quilt_cpp_formattables_decoration_profile(unsigned int position) {
    boost::optional<dogen::quilt::cpp::formattables::decoration_profile> r(
        create_dogen_quilt_cpp_formattables_decoration_profile(position));
    return r;
}

dogen::quilt::cpp::formattables::facet_profile
create_dogen_quilt_cpp_formattables_facet_profile(const unsigned int position) {
    return dogen::quilt::cpp::formattables::facet_profile_generator::create(position);
}

boost::optional<dogen::quilt::cpp::formattables::facet_profile>
create_boost_optional_dogen_quilt_cpp_formattables_facet_profile(unsigned int position) {
    boost::optional<dogen::quilt::cpp::formattables::facet_profile> r(
        create_dogen_quilt_cpp_formattables_facet_profile(position));
    return r;
}

dogen::quilt::cpp::formattables::formatter_profile
create_dogen_quilt_cpp_formattables_formatter_profile(const unsigned int position) {
    return dogen::quilt::cpp::formattables::formatter_profile_generator::create(position);
}

boost::optional<dogen::quilt::cpp::formattables::formatter_profile>
create_boost_optional_dogen_quilt_cpp_formattables_formatter_profile(unsigned int position) {
    boost::optional<dogen::quilt::cpp::formattables::formatter_profile> r(
        create_dogen_quilt_cpp_formattables_formatter_profile(position));
    return r;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile> create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_profile(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_profile> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_formattables_facet_profile(position + i)));
    }
    return r;
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile> create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formatter_profile(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_profile> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_formattables_formatter_profile(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

profile_group_generator::profile_group_generator() : position_(0) { }

void profile_group_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.parents(create_std_list_std_string(position + 1));
    v.profile_type(create_dogen_quilt_cpp_formattables_profile_types(position + 2));
    v.bind_to_stereotype(create_std_string(position + 3));
    v.decoration_profile(create_boost_optional_dogen_quilt_cpp_formattables_decoration_profile(position + 4));
    v.default_facet_profile(create_boost_optional_dogen_quilt_cpp_formattables_facet_profile(position + 5));
    v.default_formatter_profile(create_boost_optional_dogen_quilt_cpp_formattables_formatter_profile(position + 6));
    v.facet_profiles(create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_profile(position + 7));
    v.formatter_profiles(create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formatter_profile(position + 8));
}

profile_group_generator::result_type
profile_group_generator::create(const unsigned int position) {
    profile_group r;
    profile_group_generator::populate(position, r);
    return r;
}

profile_group_generator::result_type*
profile_group_generator::create_ptr(const unsigned int position) {
    profile_group* p = new profile_group();
    profile_group_generator::populate(position, *p);
    return p;
}

profile_group_generator::result_type
profile_group_generator::operator()() {
    return create(position_++);
}

} } } }
