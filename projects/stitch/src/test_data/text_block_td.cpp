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
#include "dogen/stitch/test_data/block_td.hpp"
#include "dogen/stitch/test_data/text_line_td.hpp"
#include "dogen/stitch/test_data/text_block_td.hpp"

namespace {

dogen::stitch::text_line
create_dogen_stitch_text_line(const unsigned int position) {
    return dogen::stitch::text_line_generator::create(position);
}

std::list<dogen::stitch::text_line> create_std_list_dogen_stitch_text_line(unsigned int position) {
    std::list<dogen::stitch::text_line> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_stitch_text_line(position + i));
    }
    return r;
}

}

namespace dogen {
namespace stitch {

text_block_generator::text_block_generator() : position_(0) { }

void text_block_generator::
populate(const unsigned int position, result_type& v) {
    dogen::stitch::block_generator::populate(position, v);
    v.content(create_std_list_dogen_stitch_text_line(position + 0));
}

text_block_generator::result_type
text_block_generator::create(const unsigned int position) {
    text_block r;
    text_block_generator::populate(position, r);
    return r;
}
text_block_generator::result_type*
text_block_generator::create_ptr(const unsigned int position) {
    text_block* p = new text_block();
    text_block_generator::populate(position, *p);
    return p;
}

text_block_generator::result_type
text_block_generator::operator()() {
    return create(position_++);
}

} }
