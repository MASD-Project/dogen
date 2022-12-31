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
#include <sstream>
#include <string_view>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/header_guard_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("physical.helpers.header_guard_factory"));

constexpr std::string_view empty;
constexpr std::string_view dot(".");
constexpr std::string_view separator("_");

}

namespace dogen::physical::helpers {

std::string header_guard_factory::make(const boost::filesystem::path& p) {
    BOOST_LOG_SEV(lg, debug) << "Creating header guard from path: "
                             << p.generic_path();

    bool is_first(true);
    std::ostringstream ss;
    for (const auto& token : p) {
        std::string s(token.string());
        BOOST_LOG_SEV(lg, trace) << "Original token: " << s;

        boost::replace_all(s, dot, separator);
        boost::to_upper(s);
        BOOST_LOG_SEV(lg, trace) << "Processed token: " << s;

        ss << (is_first ? empty : separator) << s;
        is_first = false;
    }

    const auto r(ss.str());
    BOOST_LOG_SEV(lg, debug) << "Header guard: " << r;
    return r;
}

}
