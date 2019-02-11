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
#include <string>
#include <istream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include "masd.dogen.utility/types/test/json_validator.hpp"

namespace {

using namespace boost::spirit;

/**
 * @brief JSON validator from "The Boost Libraries" book.
 */
template<typename Iterator, typename Skipper>
struct json_grammar : qi::grammar<Iterator, Skipper> {
    qi::rule<Iterator, Skipper> object, member, string, value, number, array;

    json_grammar() : json_grammar::base_type(object) {
        object = "{" >> member >> *("," >> member) >> "}";
        member = string >> ":" >> value;
        string = qi::lexeme['"' >> *~qi::lit('"') >> '"'];
        value = string | number | object | array | "true" | "false" | "null";
        number = qi::double_;
        array = (qi::lexeme["["] >> "]") |
            ("[" >> value >> *("," >> value) >> "]");
    }
};

}

namespace masd::dogen::utility::test {

bool json_validator::validate(std::istream& s) {
    boost::spirit::istream_iterator it(s);
    boost::spirit::istream_iterator end;

    json_grammar<boost::spirit::istream_iterator,
                 boost::spirit::ascii::space_type> g;
    const bool ok(boost::spirit::qi::phrase_parse(it, end, g,
            boost::spirit::ascii::space));

    return ok && it == end;
}

}
