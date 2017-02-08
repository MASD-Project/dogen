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
#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_SPIRIT_DEBUG

#include "dogen/yarn/types/name_tree_parser.hpp"

#include "name_tree_parser_impl.hpp"


namespace dogen {
namespace yarn {

name_tree_parser::
name_tree_parser(const std::unordered_set<std::string>& top_level_modules,
    const location& model_location, const languages language)
    : top_level_modules_(top_level_modules), model_location_(model_location),
      language_(language) {}

name_tree name_tree_parser::parse(const std::string& s) const {
    BOOST_LOG_SEV(lg, debug) << "parsing name: " << s;

    //no need for a shared_ptr, since the ownership is not shared.
    name_tree_listener<name_tree_builder> listener{ top_level_modules_, model_location_ };
    grammar<std::string::const_iterator, name_tree_builder> g(listener, language_);

    std::string::const_iterator i(s.begin());
    std::string::const_iterator end(s.end());
    const bool ok(boost::spirit::qi::phrase_parse(i, end, g, ascii::space));

    if (!ok || i != end) {
        BOOST_LOG_SEV(lg, error) << error_msg << s;
        BOOST_THROW_EXCEPTION(parsing_error(error_msg + s));
    }

    auto r(listener.ntb.build());
    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    return r;
}

} }
