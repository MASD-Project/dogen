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
#include "masd.dogen.coding/test_data/meta_model/editor_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/modeline_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/modeline_field_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/modeline_location_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::coding::meta_model::editor
create_masd_dogen_coding_meta_model_editor(const unsigned int position) {
    return masd::dogen::coding::meta_model::editor_generator::create(position);
}

masd::dogen::coding::meta_model::modeline_location
create_masd_dogen_coding_meta_model_modeline_location(const unsigned int position) {
    return masd::dogen::coding::meta_model::modeline_location_generator::create(position);
}

masd::dogen::coding::meta_model::modeline_field
create_masd_dogen_coding_meta_model_modeline_field(const unsigned int position) {
    return masd::dogen::coding::meta_model::modeline_field_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::modeline_field> create_std_list_masd_dogen_coding_meta_model_modeline_field(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::modeline_field> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_modeline_field(position + i));
    }
    return r;
}

}

namespace masd::dogen::coding::meta_model {

modeline_generator::modeline_generator() : position_(0) { }

void modeline_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.editor(create_masd_dogen_coding_meta_model_editor(position + 1));
    v.location(create_masd_dogen_coding_meta_model_modeline_location(position + 2));
    v.fields(create_std_list_masd_dogen_coding_meta_model_modeline_field(position + 3));
}

modeline_generator::result_type
modeline_generator::create(const unsigned int position) {
    modeline r;
    modeline_generator::populate(position, r);
    return r;
}

modeline_generator::result_type*
modeline_generator::create_ptr(const unsigned int position) {
    modeline* p = new modeline();
    modeline_generator::populate(position, *p);
    return p;
}

modeline_generator::result_type
modeline_generator::operator()() {
    return create(position_++);
}

}
