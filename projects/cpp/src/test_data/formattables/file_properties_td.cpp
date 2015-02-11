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
#include "dogen/cpp/test_data/formattables/file_properties_td.hpp"
#include "dogen/cpp/test_data/formattables/inclusion_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::cpp::formattables::inclusion
create_dogen_cpp_formattables_inclusion(const unsigned int position) {
    return dogen::cpp::formattables::inclusion_generator::create(position);
}

boost::optional<dogen::cpp::formattables::inclusion>
create_boost_optional_dogen_cpp_formattables_inclusion(unsigned int position) {
    boost::optional<dogen::cpp::formattables::inclusion> r(
        create_dogen_cpp_formattables_inclusion(position));
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

file_properties_generator::file_properties_generator() : position_(0) { }

void file_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.file_path(create_boost_filesystem_path(position + 0));
    v.inclusion(create_boost_optional_dogen_cpp_formattables_inclusion(position + 1));
}

file_properties_generator::result_type
file_properties_generator::create(const unsigned int position) {
    file_properties r;
    file_properties_generator::populate(position, r);
    return r;
}
file_properties_generator::result_type*
file_properties_generator::create_ptr(const unsigned int position) {
    file_properties* p = new file_properties();
    file_properties_generator::populate(position, *p);
    return p;
}

file_properties_generator::result_type
file_properties_generator::operator()() {
    return create(position_++);
}

} } }
