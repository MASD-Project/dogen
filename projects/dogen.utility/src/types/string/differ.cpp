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
#include <dtl/dtl.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/differ.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("utility.string.differ"));

std::vector<std::string> split_lines(const std::string& s) {
    std::string line;
    std::istringstream ss(s);
    std::vector<std::string> r;
    while (std::getline(ss, line))
        r.push_back(line);

    return r;
}

bool compose_diff(const std::vector<std::string>& a,
    const std::vector<std::string>& e, std::ostream& s) {

    dtl::Diff<std::string> diff(a, e);
    diff.onHuge();
    diff.compose();
    diff.composeUnifiedHunks();
    diff.printUnifiedFormat(s);

    return diff.getEditDistance() != 0;
}

}

namespace dogen::utility::string {

std::string differ::diff(const std::string& a, const std::string& e) {
    std::ostringstream s;
    diff(a, e, s);

    const auto r(s.str());
    if (r.empty())
        BOOST_LOG_SEV(lg, trace) << "Diff: <empty>";
    else
        BOOST_LOG_SEV(lg, debug) << "Diff: " << std::endl << r;

    return r;
}

bool differ::diff(const std::string& a, const std::string& e, std::ostream& s) {
    BOOST_LOG_SEV(lg, trace) << "Content of a: " << std::endl << a;
    BOOST_LOG_SEV(lg, trace) << "Content of e: " << std::endl << e;

    const auto a_lines(split_lines(a));
    const auto e_lines(split_lines(e));
    return compose_diff(a_lines, e_lines, s);
}

}
