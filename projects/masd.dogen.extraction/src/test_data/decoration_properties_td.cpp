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
#include "masd.dogen.extraction/test_data/licence_td.hpp"
#include "masd.dogen.extraction/test_data/modeline_td.hpp"
#include "masd.dogen.extraction/test_data/decoration_properties_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

masd::dogen::extraction::modeline
create_masd_dogen_extraction_modeline(const unsigned int position) {
    return masd::dogen::extraction::modeline_generator::create(position);
}

boost::optional<masd::dogen::extraction::modeline>
create_boost_optional_masd_dogen_extraction_modeline(unsigned int position) {
    boost::optional<masd::dogen::extraction::modeline> r(
        create_masd_dogen_extraction_modeline(position));
    return r;
}

masd::dogen::extraction::licence
create_masd_dogen_extraction_licence(const unsigned int position) {
    return masd::dogen::extraction::licence_generator::create(position);
}

boost::optional<masd::dogen::extraction::licence>
create_boost_optional_masd_dogen_extraction_licence(unsigned int position) {
    boost::optional<masd::dogen::extraction::licence> r(
        create_masd_dogen_extraction_licence(position));
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace masd::dogen::extraction {

decoration_properties_generator::decoration_properties_generator() : position_(0) { }

void decoration_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.generate_decoration(create_bool(position + 0));
    v.modeline(create_boost_optional_masd_dogen_extraction_modeline(position + 1));
    v.licence(create_boost_optional_masd_dogen_extraction_licence(position + 2));
    v.code_generation_marker(create_std_string(position + 3));
    v.preamble(create_std_string(position + 4));
    v.postamble(create_std_string(position + 5));
}

decoration_properties_generator::result_type
decoration_properties_generator::create(const unsigned int position) {
    decoration_properties r;
    decoration_properties_generator::populate(position, r);
    return r;
}

decoration_properties_generator::result_type*
decoration_properties_generator::create_ptr(const unsigned int position) {
    decoration_properties* p = new decoration_properties();
    decoration_properties_generator::populate(position, *p);
    return p;
}

decoration_properties_generator::result_type
decoration_properties_generator::operator()() {
    return create(position_++);
}

}
