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
#include <boost/tokenizer.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string/trim.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/string/splitter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("utility.string.splitter"));

const char* comma_delimiter = ",";

}

namespace dogen {
namespace utility {
namespace string {

std::list<std::string> splitter::
split_scoped(const std::string& n, const std::string& scope_operator) {
    BOOST_LOG_SEV(lg, debug) << "parsing scoped name: " << n;

    const boost::char_separator<char> sep(scope_operator.c_str());
    boost::tokenizer<boost::char_separator<char> > tokens(n, sep);

    std::list<std::string> r;
    boost::copy(tokens, std::inserter(r, r.end()));
    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    return r;
}

std::list<std::string>
splitter::split_csv(const std::string& n) {
    BOOST_LOG_SEV(lg, debug) << "parsing csv string: " << n;

    const boost::char_separator<char> sep(comma_delimiter);
    boost::tokenizer<boost::char_separator<char> > tokens(n, sep);

    std::list<std::string> r;
    for (auto t : tokens) {
        boost::trim(t);
        r.push_back(t);
    }

    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    return r;
}

} } }
