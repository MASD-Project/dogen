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
#include <string_view>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/identifiable_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("identification.helpers.identifiable_factory"));

constexpr std::string_view empty;
constexpr std::string_view comma(",");
constexpr std::string_view dot(".");
constexpr std::string_view space(" ");
constexpr std::string_view less_than("<");
constexpr std::string_view more_than(">");
constexpr std::string_view separator("_");
constexpr std::string_view slash("/");
constexpr std::string_view scope_operator("::");

}

namespace dogen::identification::helpers {

std::string identifiable_factory::make(const std::string& s) {
    std::string r(s);
    BOOST_LOG_SEV(lg, trace) << "Input string: " << r;

    boost::replace_all(r, dot, separator);
    boost::replace_all(r, slash, separator);
    boost::replace_all(r, scope_operator, separator);
    boost::replace_all(r, less_than, separator);

    boost::replace_all(r, comma, empty);
    boost::replace_all(r, more_than, empty);
    boost::trim(r);

    boost::replace_all(r, space, separator);

    BOOST_LOG_SEV(lg, trace) << "Result: " << r;
    return r;
}

}
