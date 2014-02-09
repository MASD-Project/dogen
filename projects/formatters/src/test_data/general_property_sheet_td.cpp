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
#include "dogen/formatters/test_data/code_generation_marker_property_sheet_td.hpp"
#include "dogen/formatters/test_data/general_property_sheet_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
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

dogen::formatters::code_generation_marker_property_sheet
create_dogen_formatters_code_generation_marker_property_sheet(const unsigned int position) {
    return dogen::formatters::code_generation_marker_property_sheet_generator::create(position);
}

}

namespace dogen {
namespace formatters {

general_property_sheet_generator::general_property_sheet_generator() : position_(0) { }

void general_property_sheet_generator::
populate(const unsigned int position, result_type& v) {
    v.enabled(create_bool(position + 0));
    v.generate_preamble(create_bool(position + 1));
    v.copyright(create_std_list_std_string(position + 2));
    v.licence_name(create_std_string(position + 3));
    v.modeline_group_name(create_std_string(position + 4));
    v.code_generation_marker(create_dogen_formatters_code_generation_marker_property_sheet(position + 5));
    v.feature_directory_name(create_std_string(position + 6));
    v.enable_facet_directories(create_bool(position + 7));
    v.facet_directory_name(create_std_string(position + 8));
    v.facet_postfix(create_std_string(position + 9));
    v.overwrite(create_bool(position + 10));
    v.file_name(create_std_string(position + 11));
    v.file_postfix(create_std_string(position + 12));
    v.extension(create_std_string(position + 13));
    v.enable_unique_file_names(create_bool(position + 14));
}

general_property_sheet_generator::result_type
general_property_sheet_generator::create(const unsigned int position) {
    general_property_sheet r;
    general_property_sheet_generator::populate(position, r);
    return r;
}
general_property_sheet_generator::result_type*
general_property_sheet_generator::create_ptr(const unsigned int position) {
    general_property_sheet* p = new general_property_sheet();
    general_property_sheet_generator::populate(position, *p);
    return p;
}

general_property_sheet_generator::result_type
general_property_sheet_generator::operator()() {
    return create(position_++);
}

} }
