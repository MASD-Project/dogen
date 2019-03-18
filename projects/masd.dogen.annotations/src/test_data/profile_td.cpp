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
#include "masd.dogen.annotations/test_data/profile_td.hpp"
#include "masd.dogen.annotations/test_data/entry_template_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

std::unordered_set<std::string> create_std_unordered_set_std_string(unsigned int position) {
    std::unordered_set<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

masd::dogen::annotations::entry_template
create_masd_dogen_annotations_entry_template(const unsigned int position) {
    return masd::dogen::annotations::entry_template_generator::create(position);
}

std::list<masd::dogen::annotations::entry_template> create_std_list_masd_dogen_annotations_entry_template(unsigned int position) {
    std::list<masd::dogen::annotations::entry_template> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_annotations_entry_template(position + i));
    }
    return r;
}

}

namespace masd::dogen::annotations {

profile_generator::profile_generator() : position_(0) { }

void profile_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.parents(create_std_list_std_string(position + 1));
    v.labels(create_std_unordered_set_std_string(position + 2));
    v.templates(create_std_list_masd_dogen_annotations_entry_template(position + 3));
}

profile_generator::result_type
profile_generator::create(const unsigned int position) {
    profile r;
    profile_generator::populate(position, r);
    return r;
}

profile_generator::result_type*
profile_generator::create_ptr(const unsigned int position) {
    profile* p = new profile();
    profile_generator::populate(position, *p);
    return p;
}

profile_generator::result_type
profile_generator::operator()() {
    return create(position_++);
}

}
