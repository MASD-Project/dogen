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
#include "masd.dogen.templating/test_data/stitch/line_td.hpp"
#include "masd.dogen.templating/test_data/stitch/text_template_body_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::list<std::pair<std::string, std::string> > create_std_list_std_pair_std_string_std_string(unsigned int position) {
    std::list<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
    }
    return r;
}

masd::dogen::templating::stitch::line
create_masd_dogen_templating_stitch_line(const unsigned int position) {
    return masd::dogen::templating::stitch::line_generator::create(position);
}

std::list<masd::dogen::templating::stitch::line> create_std_list_masd_dogen_templating_stitch_line(unsigned int position) {
    std::list<masd::dogen::templating::stitch::line> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_templating_stitch_line(position + i));
    }
    return r;
}

}

namespace masd::dogen::templating::stitch {

text_template_body_generator::text_template_body_generator() : position_(0) { }

void text_template_body_generator::
populate(const unsigned int position, result_type& v) {
    v.tagged_values(create_std_list_std_pair_std_string_std_string(position + 0));
    v.lines(create_std_list_masd_dogen_templating_stitch_line(position + 1));
}

text_template_body_generator::result_type
text_template_body_generator::create(const unsigned int position) {
    text_template_body r;
    text_template_body_generator::populate(position, r);
    return r;
}

text_template_body_generator::result_type*
text_template_body_generator::create_ptr(const unsigned int position) {
    text_template_body* p = new text_template_body();
    text_template_body_generator::populate(position, *p);
    return p;
}

text_template_body_generator::result_type
text_template_body_generator::operator()() {
    return create(position_++);
}

}
