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
#include "dogen/om/test_data/cmake_file_td.hpp"
#include "dogen/om/test_data/cpp_file_td.hpp"
#include "dogen/om/test_data/licence_td.hpp"
#include "dogen/om/test_data/odb_options_file_td.hpp"
#include "dogen/om/test_data/preamble_td.hpp"
#include "dogen/om/test_data/text_file_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::om::preamble
create_dogen_om_preamble(const unsigned int position) {
    return dogen::om::preamble_generator::create(position);
}

dogen::om::licence
create_dogen_om_licence(const unsigned int position) {
    return dogen::om::licence_generator::create(position);
}

}

namespace dogen {
namespace om {


void text_file_generator::
populate(const unsigned int position, result_type& v) {
    v.full_path(create_boost_filesystem_path(position + 0));
    v.relative_path(create_boost_filesystem_path(position + 1));
    v.preamble(create_dogen_om_preamble(position + 2));
    v.licence(create_dogen_om_licence(position + 3));
}

text_file_generator::result_type*
text_file_generator::create_ptr(const unsigned int position) {
    if ((position % 2) == 0)
        return dogen::om::cpp_file_generator::create_ptr(position);
    if ((position % 2) == 1)
        return dogen::om::odb_options_file_generator::create_ptr(position);
    return dogen::om::cmake_file_generator::create_ptr(position);
}


} }
