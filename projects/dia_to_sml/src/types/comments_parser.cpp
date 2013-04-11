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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/parsing_error.hpp"
#include "dogen/dia_to_sml/types/comments_parser.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.comments_parser"));

const std::string empty;
const std::string prefix("#DOGEN ");
const std::string equals("=");
const std::string separator_not_found("Expected separator on KVP.");

}

namespace dogen {
namespace dia_to_sml {

std::pair<std::string, comments_parser::kvp_vector_type>
comments_parser::parse(const std::string& c) const {
    std::pair<std::string, kvp_vector_type> r;
    if (c.empty())
        return r;

    std::istringstream comments_stream(c);
    std::ostringstream documentation_stream;
    std::string line;
    while (std::getline(comments_stream, line)) {
        if (boost::starts_with(line, prefix)) {
            boost::replace_all(line, prefix, empty);

            const auto pos(line.find_first_of(equals));
            if (pos == std::string::npos) {
                BOOST_LOG_SEV(lg, error) << separator_not_found;
                BOOST_THROW_EXCEPTION(parsing_error(separator_not_found));
            }

            kvp_vector_type::value_type kvp;
            kvp.first = line.substr(0, pos);
            kvp.second = line.substr(pos + 1);
            r.second.push_back(kvp);
        } else
            documentation_stream << line << std::endl;
    }

    r.first = documentation_stream.str();
    return r;
}

} }
