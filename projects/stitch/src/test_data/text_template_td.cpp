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
#include "dogen/stitch/test_data/line_td.hpp"
#include "dogen/stitch/test_data/properties_td.hpp"
#include "dogen/stitch/test_data/text_template_td.hpp"
#include "dogen/annotations/test_data/scribble_group_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::annotations::scribble_group
create_dogen_annotations_scribble_group(const unsigned int position) {
    return dogen::annotations::scribble_group_generator::create(position);
}

dogen::stitch::properties
create_dogen_stitch_properties(const unsigned int position) {
    return dogen::stitch::properties_generator::create(position);
}

dogen::stitch::line
create_dogen_stitch_line(const unsigned int position) {
    return dogen::stitch::line_generator::create(position);
}

std::list<dogen::stitch::line> create_std_list_dogen_stitch_line(unsigned int position) {
    std::list<dogen::stitch::line> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_stitch_line(position + i));
    }
    return r;
}

}

namespace dogen {
namespace stitch {

text_template_generator::text_template_generator() : position_(0) { }

void text_template_generator::
populate(const unsigned int position, result_type& v) {
    v.template_path(create_boost_filesystem_path(position + 0));
    v.output_path(create_boost_filesystem_path(position + 1));
    v.scribble_group(create_dogen_annotations_scribble_group(position + 2));
    v.properties(create_dogen_stitch_properties(position + 3));
    v.lines(create_std_list_dogen_stitch_line(position + 4));
}

text_template_generator::result_type
text_template_generator::create(const unsigned int position) {
    text_template r;
    text_template_generator::populate(position, r);
    return r;
}

text_template_generator::result_type*
text_template_generator::create_ptr(const unsigned int position) {
    text_template* p = new text_template();
    text_template_generator::populate(position, *p);
    return p;
}

text_template_generator::result_type
text_template_generator::operator()() {
    return create(position_++);
}

} }
