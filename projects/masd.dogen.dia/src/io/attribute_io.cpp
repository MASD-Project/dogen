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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include <boost/variant/apply_visitor.hpp>
#include "masd.dogen.dia/io/font_io.hpp"
#include "masd.dogen.dia/io/real_io.hpp"
#include "masd.dogen.dia/io/color_io.hpp"
#include "masd.dogen.dia/io/point_io.hpp"
#include "masd.dogen.dia/io/string_io.hpp"
#include "masd.dogen.dia/io/boolean_io.hpp"
#include "masd.dogen.dia/io/integer_io.hpp"
#include "masd.dogen.dia/io/attribute_io.hpp"
#include "masd.dogen.dia/io/composite_io.hpp"
#include "masd.dogen.dia/io/rectangle_io.hpp"
#include "masd.dogen.dia/io/enumeration_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace boost {

struct boost_variant_masd_dogen_dia_color_masd_dogen_dia_real_masd_dogen_dia_integer_masd_dogen_dia_font_masd_dogen_dia_boolean_masd_dogen_dia_point_masd_dogen_dia_string_masd_dogen_dia_enumeration_masd_dogen_dia_rectangle_masd_dogen_dia_composite_visitor : public boost::static_visitor<> {
    boost_variant_masd_dogen_dia_color_masd_dogen_dia_real_masd_dogen_dia_integer_masd_dogen_dia_font_masd_dogen_dia_boolean_masd_dogen_dia_point_masd_dogen_dia_string_masd_dogen_dia_enumeration_masd_dogen_dia_rectangle_masd_dogen_dia_composite_visitor(std::ostream& s) : stream_(s) {
        s << "{ " << "\"__type__\": " << "\"boost::variant\"" << ", ";
        s << "\"data\": ";
    }

    ~boost_variant_masd_dogen_dia_color_masd_dogen_dia_real_masd_dogen_dia_integer_masd_dogen_dia_font_masd_dogen_dia_boolean_masd_dogen_dia_point_masd_dogen_dia_string_masd_dogen_dia_enumeration_masd_dogen_dia_rectangle_masd_dogen_dia_composite_visitor() { stream_ << " }"; }

    void operator()(const masd::dogen::dia::color& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::dia::real& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::dia::integer& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::dia::font& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::dia::boolean& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::dia::point& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::dia::string& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::dia::enumeration& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::dia::rectangle& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::dia::composite& v) const {
        stream_ << v;
    }

private:
    std::ostream& stream_;
};

inline std::ostream& operator<<(std::ostream& s, const boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite>& v) {
    boost::apply_visitor(boost_variant_masd_dogen_dia_color_masd_dogen_dia_real_masd_dogen_dia_integer_masd_dogen_dia_font_masd_dogen_dia_boolean_masd_dogen_dia_point_masd_dogen_dia_string_masd_dogen_dia_enumeration_masd_dogen_dia_rectangle_masd_dogen_dia_composite_visitor(s), v);
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<boost::variant<masd::dogen::dia::color, masd::dogen::dia::real, masd::dogen::dia::integer, masd::dogen::dia::font, masd::dogen::dia::boolean, masd::dogen::dia::point, masd::dogen::dia::string, masd::dogen::dia::enumeration, masd::dogen::dia::rectangle, masd::dogen::dia::composite> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace masd::dogen::dia {

std::ostream& operator<<(std::ostream& s, const attribute& v) {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::dia::attribute\"" << ", "
      << "\"name\": " << "\"" << tidy_up_string(v.name()) << "\"" << ", "
      << "\"values\": " << v.values()
      << " }";
    return(s);
}

}
