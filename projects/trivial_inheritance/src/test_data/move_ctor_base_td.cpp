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
#include "dogen/trivial_inheritance/test_data/move_ctor_base_td.hpp"
#include "dogen/trivial_inheritance/test_data/move_ctor_descendant_td.hpp"
#include "dogen/trivial_inheritance/test_data/move_ctor_empty_descendant_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace dogen {
namespace trivial_inheritance {


void move_ctor_base_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_boost_filesystem_path(position + 0));
}

move_ctor_base_generator::result_type*
move_ctor_base_generator::create_ptr(const unsigned int position) {
    if ((position % 1) == 0)
        return dogen::trivial_inheritance::move_ctor_empty_descendant_generator::create_ptr(position);
    return dogen::trivial_inheritance::move_ctor_descendant_generator::create_ptr(position);
}


} }
