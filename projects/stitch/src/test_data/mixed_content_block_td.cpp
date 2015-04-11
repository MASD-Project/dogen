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
#include <sstream>
#include "dogen/stitch/test_data/mixed_content_line_td.hpp"
#include "dogen/stitch/test_data/mixed_content_block_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::stitch::mixed_content_line
create_dogen_stitch_mixed_content_line(const unsigned int position) {
    return dogen::stitch::mixed_content_line_generator::create(position);
}


boost::variant<std::string, dogen::stitch::mixed_content_line>
create_boost_variant_std_string_dogen_stitch_mixed_content_line(unsigned int position) {
    boost::variant<std::string, dogen::stitch::mixed_content_line> r;

    if (position == 0 || ((position % 2) == 0))
        r = create_std_string(position);
    else if (position == 1 || ((position %3) == 0))
        r = create_dogen_stitch_mixed_content_line(position);

    return r;
}

std::list<boost::variant<std::string, dogen::stitch::mixed_content_line> > create_std_list_boost_variant_std_string_dogen_stitch_mixed_content_line_(unsigned int position) {
    std::list<boost::variant<std::string, dogen::stitch::mixed_content_line> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_variant_std_string_dogen_stitch_mixed_content_line(position + i));
    }
    return r;
}

}

namespace dogen {
namespace stitch {

mixed_content_block_generator::mixed_content_block_generator() : position_(0) { }

void mixed_content_block_generator::
populate(const unsigned int position, result_type& v) {
    v.content(create_std_list_boost_variant_std_string_dogen_stitch_mixed_content_line_(position + 0));
}

mixed_content_block_generator::result_type
mixed_content_block_generator::create(const unsigned int position) {
    mixed_content_block r;
    mixed_content_block_generator::populate(position, r);
    return r;
}
mixed_content_block_generator::result_type*
mixed_content_block_generator::create_ptr(const unsigned int position) {
    mixed_content_block* p = new mixed_content_block();
    mixed_content_block_generator::populate(position, *p);
    return p;
}

mixed_content_block_generator::result_type
mixed_content_block_generator::operator()() {
    return create(position_++);
}

} }
