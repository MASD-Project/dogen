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

entities::document parser::parse(const std::string& s) {
    BOOST_LOG_SEV(lg, trace) << "Parsing org document: '" << s << "'";
    entities::document r;
    unsigned int line_number(0);
    std::string line;
    std::istringstream is(s);
    std::ostringstream os;

    while (std::getline(is, line)) {
        ++line_number;
        BOOST_LOG_SEV(lg, debug) << "Parsing line: " << line;

        if (std::regex_match(line, headline_regex)) {
            // is headline
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
