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
#include "dogen/formatters/test_data/file_properties_td.hpp"
#include "dogen/quilt.cpp/test_data/properties/formattable_td.hpp"
#include "dogen/quilt.cpp/test_data/properties/cmakelists_info_td.hpp"

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

dogen::formatters::file_properties
create_dogen_formatters_file_properties(const unsigned int position) {
    return dogen::formatters::file_properties_generator::create(position);
}

boost::optional<dogen::formatters::file_properties>
create_boost_optional_dogen_formatters_file_properties(unsigned int position) {
    boost::optional<dogen::formatters::file_properties> r(
        create_dogen_formatters_file_properties(position));
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

cmakelists_info_generator::cmakelists_info_generator() : position_(0) { }

void cmakelists_info_generator::
populate(const unsigned int position, result_type& v) {
    dogen::quilt::cpp::properties::formattable_generator::populate(position, v);
    v.file_path(create_boost_filesystem_path(position + 0));
    v.model_name(create_std_string(position + 1));
    v.product_name(create_std_string(position + 2));
    v.file_name(create_std_string(position + 3));
    v.source_file_path(create_boost_filesystem_path(position + 4));
    v.include_file_path(create_boost_filesystem_path(position + 5));
    v.file_properties(create_boost_optional_dogen_formatters_file_properties(position + 6));
    v.odb_folder(create_std_string(position + 7));
    v.odb_enabled(create_bool(position + 8));
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

} } } }
