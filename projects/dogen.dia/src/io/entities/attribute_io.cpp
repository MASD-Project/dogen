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
#include "dogen.dia/io/entities/font_io.hpp"
#include "dogen.dia/io/entities/real_io.hpp"
#include "dogen.dia/io/entities/color_io.hpp"
#include "dogen.dia/io/entities/point_io.hpp"
#include "dogen.dia/io/entities/string_io.hpp"
#include "dogen.dia/io/entities/boolean_io.hpp"
#include "dogen.dia/io/entities/integer_io.hpp"
#include "dogen.dia/io/entities/attribute_io.hpp"
#include "dogen.dia/io/entities/composite_io.hpp"
#include "dogen.dia/io/entities/rectangle_io.hpp"
#include "dogen.dia/io/entities/enumeration_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace boost {

struct boost_variant_dogen_dia_entities_color_dogen_dia_entities_real_dogen_dia_entities_integer_dogen_dia_entities_font_dogen_dia_entities_boolean_dogen_dia_entities_point_dogen_dia_entities_string_dogen_dia_entities_enumeration_dogen_dia_entities_rectangle_dogen_dia_entities_composite_visitor : public boost::static_visitor<> {
    boost_variant_dogen_dia_entities_color_dogen_dia_entities_real_dogen_dia_entities_integer_dogen_dia_entities_font_dogen_dia_entities_boolean_dogen_dia_entities_point_dogen_dia_entities_string_dogen_dia_entities_enumeration_dogen_dia_entities_rectangle_dogen_dia_entities_composite_visitor(std::ostream& s) : stream_(s) {
        s << "{ " << "\"__type__\": " << "\"boost::variant\"" << ", ";
        s << "\"data\": ";
    }

    ~boost_variant_dogen_dia_entities_color_dogen_dia_entities_real_dogen_dia_entities_integer_dogen_dia_entities_font_dogen_dia_entities_boolean_dogen_dia_entities_point_dogen_dia_entities_string_dogen_dia_entities_enumeration_dogen_dia_entities_rectangle_dogen_dia_entities_composite_visitor() { stream_ << " }"; }

    void operator()(const dogen::dia::entities::color& v) const {
        stream_ << v;
    }

    void operator()(const dogen::dia::entities::real& v) const {
        stream_ << v;
    }

    void operator()(const dogen::dia::entities::integer& v) const {
        stream_ << v;
    }

    void operator()(const dogen::dia::entities::font& v) const {
        stream_ << v;
    }

    void operator()(const dogen::dia::entities::boolean& v) const {
        stream_ << v;
    }

    void operator()(const dogen::dia::entities::point& v) const {
        stream_ << v;
    }

    void operator()(const dogen::dia::entities::string& v) const {
        stream_ << v;
    }

    void operator()(const dogen::dia::entities::enumeration& v) const {
        stream_ << v;
    }

    void operator()(const dogen::dia::entities::rectangle& v) const {
        stream_ << v;
    }

    void operator()(const dogen::dia::entities::composite& v) const {
        stream_ << v;
    }

private:
    std::ostream& stream_;
};

inline std::ostream& operator<<(std::ostream& s, const boost::variant<dogen::dia::entities::color, dogen::dia::entities::real, dogen::dia::entities::integer, dogen::dia::entities::font, dogen::dia::entities::boolean, dogen::dia::entities::point, dogen::dia::entities::string, dogen::dia::entities::enumeration, dogen::dia::entities::rectangle, dogen::dia::entities::composite>& v) {
    boost::apply_visitor(boost_variant_dogen_dia_entities_color_dogen_dia_entities_real_dogen_dia_entities_integer_dogen_dia_entities_font_dogen_dia_entities_boolean_dogen_dia_entities_point_dogen_dia_entities_string_dogen_dia_entities_enumeration_dogen_dia_entities_rectangle_dogen_dia_entities_composite_visitor(s), v);
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<boost::variant<dogen::dia::entities::color, dogen::dia::entities::real, dogen::dia::entities::integer, dogen::dia::entities::font, dogen::dia::entities::boolean, dogen::dia::entities::point, dogen::dia::entities::string, dogen::dia::entities::enumeration, dogen::dia::entities::rectangle, dogen::dia::entities::composite> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::dia::entities {

std::ostream& operator<<(std::ostream& s, const attribute& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::dia::entities::attribute\"" << ", "
      << "\"name\": " << "\"" << tidy_up_string(v.name()) << "\"" << ", "
      << "\"values\": " << v.values()
      << " }";
    return(s);
}

}
