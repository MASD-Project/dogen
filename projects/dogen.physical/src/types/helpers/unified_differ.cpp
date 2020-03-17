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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/differ.hpp"
#include "dogen.physical/types/helpers/unified_differ.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("physical.helpers.unified_differ"));

const std::string empty;

/**
 * @brief Creates the unified diff header.
 */
void compose_header(const boost::filesystem::path& base,
    const boost::filesystem::path& a_path, const std::string&  info,
    std::ostream& s) {

    auto rp(a_path.lexically_relative(base));
    const auto gs(rp.generic().generic_string());
    s << "diff -u " << gs << " " << gs << std::endl
      << info << std::endl
      << "---  " << gs << std::endl
      << "+++  " << gs << std::endl;
}

}

namespace dogen::physical::helpers {

std::string unified_differ::diff(const std::string& a, const std::string& b,
    const boost::filesystem::path& base,
    const boost::filesystem::path& a_path,
    const std::string& info) {

    BOOST_LOG_SEV(lg, debug) << "Diffing: " << a_path.generic();

    std::ostringstream s;
    compose_header(base, a_path, info, s);
    const auto has_diffs(utility::string::differ::diff(a, b, s));
    if (has_diffs) {
        const auto r(s.str());
        BOOST_LOG_SEV(lg, debug) << "Diff: " << r;
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "No diffs found.";
    return empty;
}

}
