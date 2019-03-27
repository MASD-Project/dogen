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
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/location_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/languages_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::coding::meta_model::languages
create_masd_dogen_coding_meta_model_languages(const unsigned int position) {
    return masd::dogen::coding::meta_model::languages_generator::create(position);
}

std::map<masd::dogen::coding::meta_model::languages, std::string> create_std_map_masd_dogen_coding_meta_model_languages_std_string(unsigned int position) {
    std::map<masd::dogen::coding::meta_model::languages, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_masd_dogen_coding_meta_model_languages(position + i), create_std_string(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::location
create_masd_dogen_coding_meta_model_location(const unsigned int position) {
    return masd::dogen::coding::meta_model::location_generator::create(position);
}

}

namespace masd::dogen::coding::meta_model {

name_generator::name_generator() : position_(0) { }

void name_generator::
populate(const unsigned int position, result_type& v) {
    v.id(create_std_string(position + 0));
    v.simple(create_std_string(position + 1));
    v.qualified(create_std_map_masd_dogen_coding_meta_model_languages_std_string(position + 2));
    v.location(create_masd_dogen_coding_meta_model_location(position + 3));
    v.identifiable(create_std_string(position + 4));
    v.dot_qualified(create_std_string(position + 5));
    v.colon_qualified(create_std_string(position + 6));
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
