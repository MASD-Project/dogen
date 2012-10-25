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
#include <boost/tokenizer.hpp>
#include <boost/range/algorithm.hpp>
#include "dogen/generator/modeling/identifier_parser.hpp"

namespace {

const char* delimiter = "::";

}

namespace dogen {
namespace generator {
namespace modeling {

sml::qualified_name
identifier_parser::parse_qualified_name(const std::string& n) {
    dogen::sml::qualified_name r;

    if (std::string::npos == n.find(delimiter)) {
        r.type_name(n);
        return r;
    }

    const boost::char_separator<char> sep(delimiter);
    boost::tokenizer<boost::char_separator<char> > tokens(n, sep);

    std::list<std::string> token_list;
    std::copy(tokens.begin(), tokens.end(), std::back_inserter(token_list));

    r.model_name(token_list.front());
    r.type_name(token_list.back());

    token_list.pop_back();
    token_list.pop_front();

    if (!token_list.empty())
        r.package_path(token_list);

    return r;
}

std::list<std::string>
identifier_parser::parse_scoped_name(const std::string& n) {
    const boost::char_separator<char> sep(delimiter);
    boost::tokenizer<boost::char_separator<char> > tokens(n, sep);

    std::list<std::string> r;
    boost::copy(tokens, std::inserter(r, r.end()));
    return r;
}

} } }
