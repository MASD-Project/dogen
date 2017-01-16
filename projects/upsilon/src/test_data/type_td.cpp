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
#include "dogen/upsilon/test_data/name_td.hpp"
#include "dogen/upsilon/test_data/type_td.hpp"
#include "dogen/upsilon/test_data/compound_td.hpp"
#include "dogen/upsilon/test_data/primitive_td.hpp"
#include "dogen/upsilon/test_data/collection_td.hpp"
#include "dogen/upsilon/test_data/enumeration_td.hpp"

namespace {

dogen::upsilon::name
create_dogen_upsilon_name(const unsigned int position) {
    return dogen::upsilon::name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::vector<std::string> create_std_vector_std_string(unsigned int position) {
    std::vector<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace upsilon {

void type_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_upsilon_name(position + 0));
    v.extends(create_dogen_upsilon_name(position + 1));
    v.comment(create_std_string(position + 2));
    v.tag_refs(create_std_vector_std_string(position + 3));
    v.pof_id(create_std_string(position + 4));
}

type_generator::result_type*
type_generator::create_ptr(const unsigned int position) {
    if ((position % 3) == 0)
        return dogen::upsilon::compound_generator::create_ptr(position);
    if ((position % 3) == 1)
        return dogen::upsilon::enumeration_generator::create_ptr(position);
    if ((position % 3) == 2)
        return dogen::upsilon::primitive_generator::create_ptr(position);
    return dogen::upsilon::collection_generator::create_ptr(position);
}

} }
