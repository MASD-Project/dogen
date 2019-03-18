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
#include "masd.dogen.templating/test_data/stitch/line_td.hpp"
#include "masd.dogen.templating/test_data/stitch/block_td.hpp"

namespace {

masd::dogen::templating::stitch::block
create_masd_dogen_templating_stitch_block(const unsigned int position) {
    return masd::dogen::templating::stitch::block_generator::create(position);
}

std::list<masd::dogen::templating::stitch::block> create_std_list_masd_dogen_templating_stitch_block(unsigned int position) {
    std::list<masd::dogen::templating::stitch::block> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_templating_stitch_block(position + i));
    }
    return r;
}

}

namespace masd::dogen::templating::stitch {

line_generator::line_generator() : position_(0) { }

void line_generator::
populate(const unsigned int position, result_type& v) {
    v.blocks(create_std_list_masd_dogen_templating_stitch_block(position + 0));
}

line_generator::result_type
line_generator::create(const unsigned int position) {
    line r;
    line_generator::populate(position, r);
    return r;
}

line_generator::result_type*
line_generator::create_ptr(const unsigned int position) {
    line* p = new line();
    line_generator::populate(position, *p);
    return p;
}

line_generator::result_type
line_generator::operator()() {
    return create(position_++);
}

}
