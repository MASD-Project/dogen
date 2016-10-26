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
#include "dogen/quilt.cpp/test_data/formattables/formatting_styles_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/artefact_properties_td.hpp"

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

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

dogen::quilt::cpp::formattables::formatting_styles
create_dogen_quilt_cpp_formattables_formatting_styles(const unsigned int position) {
    return dogen::quilt::cpp::formattables::formatting_styles_generator::create(position);
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

artefact_properties_generator::artefact_properties_generator() : position_(0) { }

void artefact_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.enabled(create_bool(position + 0));
    v.overwrite(create_bool(position + 1));
    v.file_path(create_boost_filesystem_path(position + 2));
    v.header_guard(create_std_string(position + 3));
    v.inclusion_dependencies(create_std_list_std_string(position + 4));
    v.formatting_style(create_dogen_quilt_cpp_formattables_formatting_styles(position + 5));
    v.formatting_input(create_std_string(position + 6));
}

artefact_properties_generator::result_type
artefact_properties_generator::create(const unsigned int position) {
    artefact_properties r;
    artefact_properties_generator::populate(position, r);
    return r;
}

artefact_properties_generator::result_type*
artefact_properties_generator::create_ptr(const unsigned int position) {
    artefact_properties* p = new artefact_properties();
    artefact_properties_generator::populate(position, *p);
    return p;
}

artefact_properties_generator::result_type
artefact_properties_generator::operator()() {
    return create(position_++);
}

} } } }
