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
#include "dogen.assets/test_data/meta_model/name_td.hpp"
#include "dogen.assets/test_data/meta_model/location_td.hpp"
#include "dogen.assets/test_data/meta_model/fully_qualified_representation_td.hpp"

namespace {

dogen::assets::meta_model::fully_qualified_representation
create_dogen_assets_meta_model_fully_qualified_representation(const unsigned int position) {
    return dogen::assets::meta_model::fully_qualified_representation_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::assets::meta_model::location
create_dogen_assets_meta_model_location(const unsigned int position) {
    return dogen::assets::meta_model::location_generator::create(position);
}

}

namespace dogen::assets::meta_model {

name_generator::name_generator() : position_(0) { }

void name_generator::
populate(const unsigned int position, result_type& v) {
    v.qualified(create_dogen_assets_meta_model_fully_qualified_representation(position + 0));
    v.simple(create_std_string(position + 1));
    v.location(create_dogen_assets_meta_model_location(position + 2));
}

name_generator::result_type
name_generator::create(const unsigned int position) {
    name r;
    name_generator::populate(position, r);
    return r;
}

name_generator::result_type*
name_generator::create_ptr(const unsigned int position) {
    name* p = new name();
    name_generator::populate(position, *p);
    return p;
}

name_generator::result_type
name_generator::operator()() {
    return create(position_++);
}

}
