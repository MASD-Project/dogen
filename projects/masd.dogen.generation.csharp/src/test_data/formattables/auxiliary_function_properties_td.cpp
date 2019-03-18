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
#include "masd.dogen.generation.csharp/test_data/formattables/auxiliary_function_types_td.hpp"
#include "masd.dogen.generation.csharp/test_data/formattables/auxiliary_function_properties_td.hpp"

namespace {

masd::dogen::generation::csharp::formattables::auxiliary_function_types
create_masd_dogen_generation_csharp_formattables_auxiliary_function_types(const unsigned int position) {
    return masd::dogen::generation::csharp::formattables::auxiliary_function_types_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace masd::dogen::generation::csharp::formattables {

auxiliary_function_properties_generator::auxiliary_function_properties_generator() : position_(0) { }

void auxiliary_function_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.type(create_masd_dogen_generation_csharp_formattables_auxiliary_function_types(position + 0));
    v.name(create_std_string(position + 1));
}

auxiliary_function_properties_generator::result_type
auxiliary_function_properties_generator::create(const unsigned int position) {
    auxiliary_function_properties r;
    auxiliary_function_properties_generator::populate(position, r);
    return r;
}

auxiliary_function_properties_generator::result_type*
auxiliary_function_properties_generator::create_ptr(const unsigned int position) {
    auxiliary_function_properties* p = new auxiliary_function_properties();
    auxiliary_function_properties_generator::populate(position, *p);
    return p;
}

auxiliary_function_properties_generator::result_type
auxiliary_function_properties_generator::operator()() {
    return create(position_++);
}

}
