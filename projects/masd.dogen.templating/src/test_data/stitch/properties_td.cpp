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
#include "masd.dogen.templating/test_data/stitch/properties_td.hpp"
#include "masd.dogen.extraction/test_data/decoration_properties_td.hpp"
#include "masd.dogen.templating/test_data/stitch/stitching_properties_td.hpp"

namespace {

masd::dogen::extraction::decoration_properties
create_masd_dogen_extraction_decoration_properties(const unsigned int position) {
    return masd::dogen::extraction::decoration_properties_generator::create(position);
}

boost::optional<masd::dogen::extraction::decoration_properties>
create_boost_optional_masd_dogen_extraction_decoration_properties(unsigned int position) {
    boost::optional<masd::dogen::extraction::decoration_properties> r(
        create_masd_dogen_extraction_decoration_properties(position));
    return r;
}

masd::dogen::templating::stitch::stitching_properties
create_masd_dogen_templating_stitch_stitching_properties(const unsigned int position) {
    return masd::dogen::templating::stitch::stitching_properties_generator::create(position);
}

}

namespace masd::dogen::templating::stitch {

properties_generator::properties_generator() : position_(0) { }

void properties_generator::
populate(const unsigned int position, result_type& v) {
    v.decoration_properties(create_boost_optional_masd_dogen_extraction_decoration_properties(position + 0));
    v.stitching_properties(create_masd_dogen_templating_stitch_stitching_properties(position + 1));
}

properties_generator::result_type
properties_generator::create(const unsigned int position) {
    properties r;
    properties_generator::populate(position, r);
    return r;
}

properties_generator::result_type*
properties_generator::create_ptr(const unsigned int position) {
    properties* p = new properties();
    properties_generator::populate(position, *p);
    return p;
}

properties_generator::result_type
properties_generator::operator()() {
    return create(position_++);
}

}
