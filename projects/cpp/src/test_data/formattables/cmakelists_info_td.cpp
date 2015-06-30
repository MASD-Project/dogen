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
#include "dogen/formatters/test_data/general_settings_td.hpp"
#include "dogen/cpp/test_data/formattables/formattable_td.hpp"
#include "dogen/cpp/test_data/formattables/cmakelists_info_td.hpp"

namespace {

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

dogen::formatters::general_settings
create_dogen_formatters_general_settings(const unsigned int position) {
    return dogen::formatters::general_settings_generator::create(position);
}

boost::optional<dogen::formatters::general_settings>
create_boost_optional_dogen_formatters_general_settings(unsigned int position) {
    boost::optional<dogen::formatters::general_settings> r(
        create_dogen_formatters_general_settings(position));
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

cmakelists_info_generator::cmakelists_info_generator() : position_(0) { }

void cmakelists_info_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cpp::formattables::formattable_generator::populate(position, v);
    v.file_path(create_boost_filesystem_path(position + 0));
    v.model_name(create_std_string(position + 1));
    v.product_name(create_std_string(position + 2));
    v.file_name(create_std_string(position + 3));
    v.source_file_path(create_boost_filesystem_path(position + 4));
    v.include_file_path(create_boost_filesystem_path(position + 5));
    v.general_settings(create_boost_optional_dogen_formatters_general_settings(position + 6));
}

cmakelists_info_generator::result_type
cmakelists_info_generator::create(const unsigned int position) {
    cmakelists_info r;
    cmakelists_info_generator::populate(position, r);
    return r;
}

cmakelists_info_generator::result_type*
cmakelists_info_generator::create_ptr(const unsigned int position) {
    cmakelists_info* p = new cmakelists_info();
    cmakelists_info_generator::populate(position, *p);
    return p;
}

cmakelists_info_generator::result_type
cmakelists_info_generator::operator()() {
    return create(position_++);
}

} } }
