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
#include <regex>
#include <sstream>
#include <boost/throw_exception.hpp>
#include <boost/range/algorithm.hpp>
#include  <boost/algorithm/string/replace.hpp>
#include "dogen.org/types/entities/block_type.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.org/io/entities/document_io.hpp"
#include "dogen.org/types/helpers/parsing_error.hpp"
#include "dogen.org/types/helpers/parser.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("org.helpers.parser"));

const std::regex headline_regex("^\\*+\\s");

}

namespace dogen::org::helpers {

std::istream& parser::getline(std::istream& is, std::string& s) {
    std::ostringstream os;
    std::getline(is, s);
    os << s;

    /*
     * Try to detect if there was a newline on this line or not. There
     * is no easy way to preserve the original input in getline, so we
     * resort to this hack. The logic is that if we have not reached
     * the EOF, then there must have been a newline.
     */
    if(!is.eof() && !is.fail())
        os << std::endl;

    s = os.str();
    return is;
}

// std::list<entities::headline>
// parser::parse_headline(std::istream& is, const std::string& heading_line) {
//     std::list<entities::headline> r;

//     std::string line;
//     std::ostringstream os;
//     while(getline(is, line)) {
//         BOOST_LOG_SEV(lg, debug) << "Processing line: " << line;

//         if (std::regex_match(line, headline_regex)) {
//             entities::headline
//             r.headlines(parse_headline(is, line));
//         } else {
//             os << line;
//         }
//     }






//     return r;
// }

entities::document parser::parse(const std::string& s) {
    BOOST_LOG_SEV(lg, trace) << "Parsing org document: '" << s << "'";

    /*
     * If there is no content, return an empty document.
     */
    entities::document r;
    if (s.empty())
        return r;

    std::string line;
    std::ostringstream os;
    std::istringstream is(s);
    while(getline(is, line)) {
        BOOST_LOG_SEV(lg, debug) << "Processing line: " << line;

        if (std::regex_match(line, headline_regex)) {
            const std::string content(os.str());
            if (!content.empty()) {
                entities::block tb;
                tb.type(entities::block_type::text_block);
                tb.contents(content);
                r.section().blocks().push_back(tb);
            }


            // r.headlines(parse_headline(is, line));
        } else {
            os << line;
        }
    }

    const std::string remainder(os.str());
    if (!remainder.empty()) {
        entities::block tb;
        tb.type(entities::block_type::text_block);
        tb.contents(remainder);
        r.section().blocks().push_back(tb);
    }

    BOOST_LOG_SEV(lg, debug) << "Document: " << r;
    return r;
}

}
