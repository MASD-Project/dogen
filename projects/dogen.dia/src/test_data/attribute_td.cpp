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
#include "dogen.dia/test_data/font_td.hpp"
#include "dogen.dia/test_data/real_td.hpp"
#include "dogen.dia/test_data/color_td.hpp"
#include "dogen.dia/test_data/point_td.hpp"
#include "dogen.dia/test_data/string_td.hpp"
#include "dogen.dia/test_data/boolean_td.hpp"
#include "dogen.dia/test_data/integer_td.hpp"
#include "dogen.dia/test_data/attribute_td.hpp"
#include "dogen.dia/test_data/composite_td.hpp"
#include "dogen.dia/test_data/rectangle_td.hpp"
#include "dogen.dia/test_data/enumeration_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::dia::color
create_dogen_dia_color(const unsigned int position) {
    return dogen::dia::color_generator::create(position);
}

dogen::dia::real
create_dogen_dia_real(const unsigned int position) {
    return dogen::dia::real_generator::create(position);
}

dogen::dia::integer
create_dogen_dia_integer(const unsigned int position) {
    return dogen::dia::integer_generator::create(position);
}

dogen::dia::font
create_dogen_dia_font(const unsigned int position) {
    return dogen::dia::font_generator::create(position);
}

dogen::dia::boolean
create_dogen_dia_boolean(const unsigned int position) {
    return dogen::dia::boolean_generator::create(position);
}

dogen::dia::point
create_dogen_dia_point(const unsigned int position) {
    return dogen::dia::point_generator::create(position);
}

dogen::dia::string
create_dogen_dia_string(const unsigned int position) {
    return dogen::dia::string_generator::create(position);
}

dogen::dia::enumeration
create_dogen_dia_enumeration(const unsigned int position) {
    return dogen::dia::enumeration_generator::create(position);
}

dogen::dia::rectangle
create_dogen_dia_rectangle(const unsigned int position) {
    return dogen::dia::rectangle_generator::create(position);
}

dogen::dia::composite
create_dogen_dia_composite(const unsigned int position) {
    return dogen::dia::composite_generator::create(position);
}

boost::variant<dogen::dia::color, dogen::dia::real, dogen::dia::integer, dogen::dia::font, dogen::dia::boolean, dogen::dia::point, dogen::dia::string, dogen::dia::enumeration, dogen::dia::rectangle, dogen::dia::composite>
create_boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite(unsigned int position) {
    boost::variant<dogen::dia::color, dogen::dia::real, dogen::dia::integer, dogen::dia::font, dogen::dia::boolean, dogen::dia::point, dogen::dia::string, dogen::dia::enumeration, dogen::dia::rectangle, dogen::dia::composite> r;

    if (position == 0 || ((position % 10) == 0))
        r = create_dogen_dia_color(position);
    else if (position == 1 || ((position % 11) == 0))
        r = create_dogen_dia_real(position);
    else if ((position % 2) == 0)
        r = create_dogen_dia_integer(position);
    else if ((position % 3) == 0)
        r = create_dogen_dia_font(position);
    else if ((position % 4) == 0)
        r = create_dogen_dia_boolean(position);
    else if ((position % 5) == 0)
        r = create_dogen_dia_point(position);
    else if ((position % 6) == 0)
        r = create_dogen_dia_string(position);
    else if ((position % 7) == 0)
        r = create_dogen_dia_enumeration(position);
    else if ((position % 8) == 0)
        r = create_dogen_dia_rectangle(position);
    else if ((position % 9) == 0)
        r = create_dogen_dia_composite(position);

    return r;
}

std::vector<boost::variant<dogen::dia::color, dogen::dia::real, dogen::dia::integer, dogen::dia::font, dogen::dia::boolean, dogen::dia::point, dogen::dia::string, dogen::dia::enumeration, dogen::dia::rectangle, dogen::dia::composite> > create_std_vector_boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite(unsigned int position) {
    std::vector<boost::variant<dogen::dia::color, dogen::dia::real, dogen::dia::integer, dogen::dia::font, dogen::dia::boolean, dogen::dia::point, dogen::dia::string, dogen::dia::enumeration, dogen::dia::rectangle, dogen::dia::composite> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite(position + i));
    }
    return r;
}

}

namespace dogen::dia {

attribute_generator::attribute_generator() : position_(0) { }

void attribute_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.values(create_std_vector_boost_variant_dogen_dia_color_dogen_dia_real_dogen_dia_integer_dogen_dia_font_dogen_dia_boolean_dogen_dia_point_dogen_dia_string_dogen_dia_enumeration_dogen_dia_rectangle_dogen_dia_composite(position + 1));
}

attribute_generator::result_type
attribute_generator::create(const unsigned int position) {
    attribute r;
    attribute_generator::populate(position, r);
    return r;
}

attribute_generator::result_type*
attribute_generator::create_ptr(const unsigned int position) {
    attribute* p = new attribute();
    attribute_generator::populate(position, *p);
    return p;
}

attribute_generator::result_type
attribute_generator::operator()() {
    return create(position_++);
}

}
