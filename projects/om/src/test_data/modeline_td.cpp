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
#include "dogen/om/test_data/editors_td.hpp"
#include "dogen/om/test_data/modeline_field_td.hpp"
#include "dogen/om/test_data/modeline_locations_td.hpp"
#include "dogen/om/test_data/modeline_td.hpp"

namespace {

dogen::om::editors
create_dogen_om_editors(const unsigned int position) {
    return dogen::om::editors_generator::create(position);
}

dogen::om::modeline_locations
create_dogen_om_modeline_locations(const unsigned int position) {
    return dogen::om::modeline_locations_generator::create(position);
}

dogen::om::modeline_field
create_dogen_om_modeline_field(const unsigned int position) {
    return dogen::om::modeline_field_generator::create(position);
}

std::list<dogen::om::modeline_field> create_std_list_dogen_om_modeline_field(unsigned int position) {
    std::list<dogen::om::modeline_field> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_om_modeline_field(position + i));
    }
    return r;
}

}

namespace dogen {
namespace om {

modeline_generator::modeline_generator() : position_(0) { }

void modeline_generator::
populate(const unsigned int position, result_type& v) {
    v.editor(create_dogen_om_editors(position + 0));
    v.location(create_dogen_om_modeline_locations(position + 1));
    v.fields(create_std_list_dogen_om_modeline_field(position + 2));
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

} }
