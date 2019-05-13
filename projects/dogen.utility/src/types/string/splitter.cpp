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
#include <boost/throw_exception.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string/trim.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/string/splitter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("utility.string.splitter"));

const char* comma_delimiter = ",";
const std::string scope_delimiters(":.");

const std::string multiple_delimiters("String has more than one delimiter: ");

}

namespace dogen::utility::string {

std::list<std::string> splitter::split_scoped(const std::string& n) {
    BOOST_LOG_SEV(lg, debug) << "Parsing scoped name: " << n;

    if (n.empty())
        return std::list<std::string> {};

    const auto i(n.find_first_of("."));
    const auto k(n.find_first_of(":"));

    /*
     * If there are no delimiters we can just return the string.
     */
    if (i == std::string::npos && k == std::string::npos)
        return std::list<std::string>{ n };

    /*
     * We do not support mixing and matching delimiters.
     */
    if (i != std::string::npos && k != std::string::npos) {
        BOOST_LOG_SEV(lg, error) << multiple_delimiters << n;
        BOOST_THROW_EXCEPTION(splitting_error(multiple_delimiters + n));
    }

    return split_delimited(n, scope_delimiters);
}

std::list<std::string> splitter::
split_delimited(const std::string& n, const std::string& delimiter) {
    BOOST_LOG_SEV(lg, debug) << "Parsing scoped name: " << n;

    if (n.empty())
        return std::list<std::string> {};

    const boost::char_separator<char> sep(delimiter.c_str());
    boost::tokenizer<boost::char_separator<char> > tokens(n, sep);

    std::list<std::string> r;
    boost::copy(tokens, std::inserter(r, r.end()));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    return r;
}

std::list<std::string> splitter::split_csv(const std::string& n) {
    BOOST_LOG_SEV(lg, debug) << "Parsing csv string: '" << n << "'";

    if (n.empty())
        return std::list<std::string> {};

    const boost::char_separator<char> sep(comma_delimiter);
    boost::tokenizer<boost::char_separator<char> > tokens(n, sep);

    std::list<std::string> r;
    for (auto t : tokens) {
        boost::trim(t);
        r.push_back(t);
    }

    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    return r;
}

}
